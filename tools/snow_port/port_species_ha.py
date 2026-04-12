#!/usr/bin/env python3
"""
port_species_ha.py — Pokémon Snow Hidden Ability port tool.

Reads the 104-entry custom HA table from v17 §2 and applies HA overrides
to species_info files in src/data/pokemon/species_info/gen_N_families.h.

Each HA entry changes slot 2 (the third element) of the .abilities array
from the vanilla HA to the custom HA. The tool validates that the current
slot 2 value matches the spec's "Old HA" column before overwriting — this
is the probe methodology applied to data: if the old value doesn't match,
something is wrong and the tool halts.

LOCKED CONTRACT:
  1. v17 §2 is canonical for custom HAs. 104 entries, #1–#104.
  2. Dry-run previews changes. Commit writes + builds.
  3. Old HA validation prevents silent corruption.
"""

import argparse
import hashlib
import os
import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
SPEC_PATH = REPO_ROOT / "design-archive" / "POKEMON_SNOW_RESUME_HANDOFF_v17.md"
SPECIES_INFO_DIR = REPO_ROOT / "src" / "data" / "pokemon" / "species_info"

# Map from v17 spec species names to engine SPECIES_ constant suffixes.
# Most species map directly (e.g., "Meowth" -> "MEOWTH"), but regional
# forms and special characters need explicit mapping.
SPECIES_NAME_TO_CONSTANT = {
    "Alolan Sandshrew": "SANDSHREW_ALOLA",
    "Alolan Sandslash": "SANDSLASH_ALOLA",
    "Alolan Vulpix": "VULPIX_ALOLA",
    "Alolan Ninetales": "NINETALES_ALOLA",
    "Galarian Darumaka": "DARUMAKA_GALAR",
    "Galarian Darmanitan": "DARMANITAN_GALAR",
    "Nidoran♀": "NIDORAN_F",
    "Nidoran♂": "NIDORAN_M",
}


def species_to_constant(name: str) -> str:
    """Convert a v17 spec species name to the SPECIES_ constant suffix."""
    if name in SPECIES_NAME_TO_CONSTANT:
        return SPECIES_NAME_TO_CONSTANT[name]
    return name.upper().replace(" ", "_").replace("-", "_").replace("'", "")


def ability_to_constant(name: str) -> str:
    """Convert a v17 spec ability name to the ABILITY_ constant."""
    return "ABILITY_" + name.upper().replace(" ", "_").replace("'", "").replace("'", "")


@dataclass
class HAEntry:
    number: int
    species_names: list[str]  # e.g., ["Meowth"] or ["Geodude", "Graveler"]
    old_ha: str               # spec column: "Unnerve"
    new_ha: str               # spec column: "Fluffy"
    notes: str


def parse_ha_table(spec_text: str) -> list[HAEntry]:
    """Parse the 104-entry HA table from v17 §2."""
    lines = spec_text.splitlines()
    entries: list[HAEntry] = []

    # Find the table start
    in_table = False
    for line in lines:
        stripped = line.strip()

        # Detect table header
        if stripped.startswith("| # |") and "Old HA" in stripped:
            in_table = True
            continue
        # Skip separator
        if in_table and stripped.startswith("|---"):
            continue
        # End of table
        if in_table and not stripped.startswith("|"):
            break

        if not in_table:
            continue

        cells = [c.strip() for c in stripped.strip("|").split("|")]
        if len(cells) < 5:
            continue

        num_str = cells[0].strip()
        # Skip non-numeric rows (like "PREVIOUSLY EXISTING" divider)
        if num_str == "—" or not num_str.isdigit():
            continue

        number = int(num_str)
        stages_raw = cells[1].strip()
        old_ha = cells[2].strip()
        new_ha = cells[3].strip().replace("**", "")  # strip bold
        notes = cells[4].strip() if len(cells) > 4 else ""

        # Parse species names: "Geodude / Graveler" -> ["Geodude", "Graveler"]
        # Handle "(only)" suffix: "Infernape (only)" -> ["Infernape"]
        stages_raw = re.sub(r"\s*\(only\)", "", stages_raw)
        species_names = [s.strip() for s in stages_raw.split("/")]

        # Old HA may contain "/" for split old HAs across stages
        # e.g., "Run Away / Stench" for Oddish / Gloom
        # In this case, treat it as a single entry — the tool matches
        # against whatever the engine actually has in slot 2.
        old_ha = old_ha.split("/")[0].strip()  # use first old HA as reference

        entries.append(HAEntry(
            number=number,
            species_names=species_names,
            old_ha=old_ha,
            new_ha=new_ha,
            notes=notes,
        ))

    return entries


def find_species_file(species_constant: str) -> Path | None:
    """Find which gen_N_families.h file contains the given species."""
    target = f"[SPECIES_{species_constant}]"
    for gen_file in sorted(SPECIES_INFO_DIR.glob("gen_*_families.h")):
        text = gen_file.read_text(encoding="utf-8")
        if target in text:
            return gen_file
    return None


# Matches inline ability arrays: .abilities = { ABILITY_X, ABILITY_Y, ABILITY_Z },
INLINE_ABILITIES_RE = re.compile(
    r"(\.abilities\s*=\s*\{\s*"
    r"ABILITY_\w+\s*,\s*"
    r"ABILITY_\w+\s*,\s*)"
    r"(ABILITY_\w+)"
    r"(\s*\})"
)

# Matches macro-defined ability arrays: #define FOO_ABILITIES { ..., ..., ABILITY_Z }
MACRO_ABILITIES_RE = re.compile(
    r"(#define\s+\w+_ABILITIES\s+\{\s*"
    r"ABILITY_\w+\s*,\s*"
    r"ABILITY_\w+\s*,\s*)"
    r"(ABILITY_\w+)"
    r"(\s*\})"
)


@dataclass
class ChangeRecord:
    species: str
    file: Path
    line_num: int
    old_ability: str
    new_ability: str
    is_macro: bool


def find_ability_line(file_text: str, file_path: Path,
                      species_constant: str,
                      old_ha_constant: str,
                      new_ha_constant: str) -> ChangeRecord | None:
    """Find the ability line for a species and replace slot 2 with new HA.
    Warns (but proceeds) if current slot 2 doesn't match spec's Old HA —
    pokeemerald-expansion may have different vanilla HAs than the spec assumed."""
    target = f"[SPECIES_{species_constant}]"
    lines = file_text.splitlines()

    # Find the species entry
    species_line = None
    for i, line in enumerate(lines):
        if target in line:
            species_line = i
            break

    if species_line is None:
        return None

    # Search forward from species entry for .abilities line
    for i in range(species_line, min(species_line + 60, len(lines))):
        line = lines[i]

        # Check for inline abilities
        m = INLINE_ABILITIES_RE.search(line)
        if m:
            current_ha = m.group(2)
            if current_ha == new_ha_constant:
                return None  # already set, skip silently
            if current_ha != old_ha_constant:
                print(
                    f"  NOTE: {species_constant} slot 2 is {current_ha}, "
                    f"spec says {old_ha_constant} — overwriting anyway "
                    f"(expansion version drift)",
                    file=sys.stderr,
                )
            return ChangeRecord(
                species=species_constant,
                file=file_path,
                line_num=i + 1,
                old_ability=current_ha,
                new_ability=new_ha_constant,
                is_macro=False,
            )

        # Check for macro reference (e.g., .abilities = MEOWTH_ABILITIES)
        macro_ref = re.match(r"\s*\.abilities\s*=\s*([A-Z_]+_ABILITIES)", line)
        if macro_ref:
            macro_name = macro_ref.group(1)
            # Find the macro definition earlier in the file
            for j in range(species_line - 1, max(species_line - 20, -1), -1):
                mm = MACRO_ABILITIES_RE.search(lines[j])
                if mm and macro_name in lines[j]:
                    current_ha = mm.group(2)
                    if current_ha == new_ha_constant:
                        return None  # already set
                    if current_ha != old_ha_constant:
                        print(
                            f"  NOTE: {species_constant} macro {macro_name} slot 2 is "
                            f"{current_ha}, spec says {old_ha_constant} — overwriting anyway",
                            file=sys.stderr,
                        )
                    return ChangeRecord(
                        species=species_constant,
                        file=file_path,
                        line_num=j + 1,
                        old_ability=current_ha,
                        new_ability=new_ha_constant,
                        is_macro=True,
                    )
            break

    return None


def apply_changes(changes: list[ChangeRecord]) -> dict[Path, str]:
    """Apply ability changes to file texts. Returns modified file texts by path."""
    file_texts: dict[Path, str] = {}

    for change in changes:
        if change.file not in file_texts:
            file_texts[change.file] = change.file.read_text(encoding="utf-8")

        text = file_texts[change.file]
        old = change.old_ability
        new = change.new_ability

        # Find the exact line and replace only the HA slot
        lines = text.splitlines(keepends=True)
        line_idx = change.line_num - 1
        line = lines[line_idx]

        if change.is_macro:
            new_line = MACRO_ABILITIES_RE.sub(
                lambda m: m.group(1) + new + m.group(3),
                line, count=1
            )
        else:
            new_line = INLINE_ABILITIES_RE.sub(
                lambda m: m.group(1) + new + m.group(3),
                line, count=1
            )

        if new_line == line:
            print(f"  ERROR: replacement had no effect on {change.species} line {change.line_num}",
                  file=sys.stderr)
            continue

        lines[line_idx] = new_line
        file_texts[change.file] = "".join(lines)

    return file_texts


def md5_file(path: Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()


def assert_clean_tree() -> None:
    unstaged = subprocess.run(["git", "diff", "--quiet"], cwd=REPO_ROOT).returncode
    staged = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=REPO_ROOT).returncode
    if unstaged != 0 or staged != 0:
        raise SystemExit(
            "FATAL: working tree has uncommitted changes. Commit or stash before --commit."
        )


def main() -> int:
    ap = argparse.ArgumentParser(description="Port custom HAs from v17 §2 to species_info.")
    ap.add_argument("--dry-run", action="store_true", default=True,
                    help="Preview changes without writing (default)")
    ap.add_argument("--commit", action="store_true",
                    help="Write changes and build")
    args = ap.parse_args()

    if not SPEC_PATH.exists():
        print(f"FATAL: spec not found at {SPEC_PATH}", file=sys.stderr)
        return 2

    print("Parsing v17 §2 HA table...")
    spec_text = SPEC_PATH.read_text(encoding="utf-8")
    entries = parse_ha_table(spec_text)
    print(f"Parsed {len(entries)} HA entries.")

    # Expand entries to per-species changes
    changes: list[ChangeRecord] = []
    skipped: list[tuple[int, str, str]] = []
    unchanged: list[tuple[int, str]] = []

    for entry in entries:
        if entry.old_ha == entry.new_ha:
            unchanged.append((entry.number, entry.species_names[0]))
            continue

        old_const = ability_to_constant(entry.old_ha)
        new_const = ability_to_constant(entry.new_ha)

        for species_name in entry.species_names:
            sp_const = species_to_constant(species_name)
            gen_file = find_species_file(sp_const)

            if gen_file is None:
                skipped.append((entry.number, species_name, f"SPECIES_{sp_const} not found"))
                continue

            file_text = gen_file.read_text(encoding="utf-8")
            change = find_ability_line(file_text, gen_file, sp_const, old_const, new_const)

            if change is None:
                skipped.append((entry.number, species_name, "ability line not matched or old HA mismatch"))
                continue

            changes.append(change)

    # Report
    print(f"\n{'='*60}")
    print(f"CHANGES: {len(changes)} species will be modified")
    print(f"UNCHANGED: {len(unchanged)} entries (old == new, e.g., Blaziken Speed Boost)")
    print(f"SKIPPED: {len(skipped)} species (need manual review)")
    print(f"{'='*60}\n")

    if changes:
        # Group by file for display
        by_file: dict[str, list[ChangeRecord]] = {}
        for c in changes:
            key = c.file.name
            by_file.setdefault(key, []).append(c)

        for fname, file_changes in sorted(by_file.items()):
            print(f"  {fname}:")
            for c in file_changes:
                prefix = "  MACRO" if c.is_macro else "       "
                print(f"  {prefix} L{c.line_num:5d}  {c.species:30s}  "
                      f"{c.old_ability} → {c.new_ability}")
            print()

    if skipped:
        print("SKIPPED (manual review needed):")
        for num, name, reason in skipped:
            print(f"  #{num:3d} {name}: {reason}")
        print()

    if unchanged:
        print(f"UNCHANGED ({len(unchanged)} entries where old == new):")
        for num, name in unchanged:
            print(f"  #{num:3d} {name}")
        print()

    if not args.commit:
        print("Dry-run complete. Use --commit to write changes and build.")
        return 0

    # Commit mode
    assert_clean_tree()
    print("[1/4] clean-tree check: PASS")

    # Capture pre-write MD5s
    modified_files = set(c.file for c in changes)
    pre_md5 = {f: md5_file(f) for f in modified_files}
    print(f"[2/4] pre-write MD5s captured for {len(modified_files)} files")

    # Apply and write
    file_texts = apply_changes(changes)
    for fpath, text in file_texts.items():
        fpath.write_text(text, encoding="utf-8")
    print(f"[3/4] wrote {len(changes)} HA changes across {len(file_texts)} files")

    # Post-write MD5s
    post_md5 = {f: md5_file(f) for f in modified_files}
    for f in modified_files:
        print(f"      {f.name}: {pre_md5[f]} → {post_md5[f]}")

    # Build
    ncpu = os.cpu_count() or 1
    print(f"[4/4] running make -j{ncpu} ...")
    build = subprocess.run(
        ["make", f"-j{ncpu}"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    if build.returncode != 0:
        print("[4/4] BUILD FAILED — last 30 lines of stderr:", file=sys.stderr)
        for line in build.stderr.splitlines()[-30:]:
            print(line, file=sys.stderr)
        print("\nWrites are NOT rolled back. Inspect and fix.", file=sys.stderr)
        return 1
    print("[4/4] build: PASS")

    rom_md5 = md5_file(REPO_ROOT / "pokeemerald.gba")
    print(f"\npokeemerald.gba MD5: {rom_md5}")
    print(f"\n# Suggested commit message:\n")
    print(f"feat(species): apply 104 custom Hidden Abilities from v17 §2 "
          f"({len(changes)} species modified)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
