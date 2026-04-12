#!/usr/bin/env python3
"""
port_species_learnsets.py — Pokémon Snow custom learnset port tool.

Reads Section 4 of v17 and applies custom move additions to:
  - src/data/pokemon/level_up_learnsets/gen_9.h (level-up moves)
  - src/data/pokemon/all_learnables.json (TM/tutor teachable moves)

Level-up additions insert LEVEL_UP_MOVE(1, MOVE_X) before LEVEL_UP_END.
Teachable additions add "MOVE_X" to the species' JSON array in all_learnables.json.
"""

import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
SPEC_PATH = REPO_ROOT / "design-archive" / "POKEMON_SNOW_RESUME_HANDOFF_v17.md"
GEN9_LEARNSETS = REPO_ROOT / "src" / "data" / "pokemon" / "level_up_learnsets" / "gen_9.h"
ALL_LEARNABLES = REPO_ROOT / "src" / "data" / "pokemon" / "all_learnables.json"

# Species name → learnset array name component
SPECIES_LEARNSET_NAME = {
    "Nidoran♀": "NidoranF",
    "Nidoran♂": "NidoranM",
    "Porygon-Z": "PorygonZ",
    "Porygon2": "Porygon2",
    "Alolan Sandshrew": "SandshrewAlola",
    "Alolan Sandslash": "SandslashAlola",
    "Alolan Vulpix": "VulpixAlola",
    "Alolan Ninetales": "NinetalesAlola",
    "Galarian Darumaka": "DarumakaGalar",
    "Galarian Darmanitan": "DarmanitanGalar",
}

# Species name → all_learnables.json key
SPECIES_JSON_KEY = {
    "Nidoran♀": "NIDORAN_F",
    "Nidoran♂": "NIDORAN_M",
    "Porygon-Z": "PORYGON_Z",
    "Alolan Sandshrew": "SANDSHREW_ALOLA",
    "Alolan Sandslash": "SANDSLASH_ALOLA",
    "Alolan Vulpix": "VULPIX_ALOLA",
    "Alolan Ninetales": "NINETALES_ALOLA",
    "Galarian Darumaka": "DARUMAKA_GALAR",
    "Galarian Darmanitan": "DARMANITAN_GALAR",
}


def to_learnset_name(species: str) -> str:
    """Convert species name to learnset array name component (PascalCase)."""
    if species in SPECIES_LEARNSET_NAME:
        return SPECIES_LEARNSET_NAME[species]
    # Remove punctuation and convert to PascalCase
    cleaned = species.replace("'", "").replace("'", "").replace("-", "").replace(".", "")
    return cleaned.replace(" ", "")


def to_json_key(species: str) -> str:
    """Convert species name to all_learnables.json key (UPPER_SNAKE)."""
    if species in SPECIES_JSON_KEY:
        return SPECIES_JSON_KEY[species]
    return species.upper().replace(" ", "_").replace("-", "_").replace("'", "").replace("'", "")


def to_move_constant(move: str) -> str:
    """Convert move name to MOVE_ constant."""
    return "MOVE_" + move.upper().replace(" ", "_").replace("-", "_").replace("'", "")


@dataclass
class LearnsetEntry:
    species_names: list[str]
    move: str
    entry_type: str  # "levelup" or "teachable"
    source: str


def classify_source(source: str) -> str:
    """Classify a Source column value as 'levelup' or 'teachable'."""
    s = source.lower()
    if "tm compatibility" in s:
        return "teachable"
    if "level-up" in s or "learnset" in s:
        return "levelup"
    # Default ambiguous/custom entries to levelup
    return "levelup"


def parse_section4(spec_text: str) -> list[LearnsetEntry]:
    """Parse all Section 4 tables from v17."""
    lines = spec_text.splitlines()
    entries: list[LearnsetEntry] = []
    seen: set[tuple[str, str]] = set()  # (species, move) dedup

    i = 0
    n = len(lines)

    # Find Section 4
    while i < n:
        if lines[i].strip().startswith("# SECTION 4"):
            break
        i += 1

    if i >= n:
        raise ValueError("Section 4 not found in spec")

    # Parse all tables until Section 5 or next major section
    while i < n:
        line = lines[i].strip()

        # Stop at next major section
        if line.startswith("# SECTION 5") or line.startswith("# SECTION 6"):
            break

        # Skip non-table lines
        if not line.startswith("|") or line.startswith("|---") or line.startswith("| Species"):
            # Check for subsection headers to adjust classification
            if line.startswith("### TM Compatibility"):
                # Next table entries are teachable
                pass
            elif line.startswith("### Tutor Compatibility"):
                pass
            elif line.startswith("### Direct Learnset"):
                pass
            elif line.startswith("### Custom Ability"):
                break  # Stop before ability ports
            i += 1
            continue

        # Parse table row
        cells = [c.strip() for c in line.strip("|").split("|")]
        if len(cells) < 3:
            i += 1
            continue

        species_raw = cells[0].strip()
        move_raw = cells[1].strip()

        # Handle "Sceptile line" → "Treecko/Grovyle/Sceptile" shorthand
        if species_raw.endswith(" line"):
            species_raw = species_raw.replace(" line", "")

        # Handle "Chandelure line" → just the species
        if species_raw.endswith(" line"):
            species_raw = species_raw[:-5]

        # Parse species names
        species_names = [s.strip() for s in species_raw.split("/")]

        # Determine type based on source column or subsection context
        source = cells[2].strip() if len(cells) > 2 else ""

        # Direct Learnset Additions subsection → teachable
        # TM/Tutor subsections → teachable
        # Main table → classify by source text
        if "TM" in source and "compatibility" not in source.lower():
            # Direct learnset entry with TM reference → teachable
            entry_type = "teachable"
        elif "tutor" in source.lower() and "level-up" not in source.lower():
            entry_type = "teachable"
        elif source.startswith("Gen ") or source.startswith("TR") or source.startswith("TM"):
            # Direct Learnset Additions entries reference game TM/TR → teachable
            entry_type = "teachable"
        elif "Standard TM" in source:
            entry_type = "teachable"
        else:
            entry_type = classify_source(source)

        # Dedup (TM entries appear in both main table and TM subsection)
        for sp in species_names:
            key = (sp, move_raw)
            if key not in seen:
                seen.add(key)
                entries.append(LearnsetEntry(
                    species_names=[sp],
                    move=move_raw,
                    entry_type=entry_type,
                    source=source,
                ))

        i += 1

    return entries


def apply_levelup_changes(entries: list[LearnsetEntry]) -> tuple[int, int]:
    """Apply level-up move additions to gen_9.h. Returns (applied, skipped)."""
    text = GEN9_LEARNSETS.read_text(encoding="utf-8")
    applied = 0
    skipped = 0

    for entry in entries:
        if entry.entry_type != "levelup":
            continue

        for species in entry.species_names:
            array_name = f"s{to_learnset_name(species)}LevelUpLearnset"
            move_const = to_move_constant(entry.move)
            insert_line = f"    LEVEL_UP_MOVE( 1, {move_const}),"

            # Check if array exists
            if array_name not in text:
                print(f"  SKIP: {array_name} not found in gen_9.h", file=sys.stderr)
                skipped += 1
                continue

            # Check if move already present
            if move_const in text[text.index(array_name):text.index(array_name) + 2000]:
                # Already has this move
                skipped += 1
                continue

            # Find LEVEL_UP_END for this array and insert before it
            arr_start = text.index(array_name)
            end_marker = "LEVEL_UP_END"
            end_pos = text.index(end_marker, arr_start)
            text = text[:end_pos] + insert_line + "\n    " + text[end_pos:]
            applied += 1

    if applied > 0:
        GEN9_LEARNSETS.write_text(text, encoding="utf-8")

    return applied, skipped


def apply_teachable_changes(entries: list[LearnsetEntry]) -> tuple[int, int]:
    """Apply teachable move additions to all_learnables.json. Returns (applied, skipped)."""
    data = json.loads(ALL_LEARNABLES.read_text(encoding="utf-8"))
    applied = 0
    skipped = 0

    for entry in entries:
        if entry.entry_type != "teachable":
            continue

        for species in entry.species_names:
            json_key = to_json_key(species)
            move_const = to_move_constant(entry.move)

            if json_key not in data:
                print(f"  SKIP: {json_key} not found in all_learnables.json", file=sys.stderr)
                skipped += 1
                continue

            if move_const in data[json_key]:
                skipped += 1
                continue

            data[json_key].append(move_const)
            data[json_key].sort()
            applied += 1

    if applied > 0:
        ALL_LEARNABLES.write_text(
            json.dumps(data, indent=2, ensure_ascii=False) + "\n",
            encoding="utf-8"
        )

    return applied, skipped


def md5_file(path: Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()


def assert_clean_tree() -> None:
    unstaged = subprocess.run(["git", "diff", "--quiet"], cwd=REPO_ROOT).returncode
    staged = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=REPO_ROOT).returncode
    if unstaged != 0 or staged != 0:
        raise SystemExit("FATAL: uncommitted changes. Commit or stash before --commit.")


def main() -> int:
    ap = argparse.ArgumentParser(description="Port custom learnsets from v17 §4.")
    ap.add_argument("--dry-run", action="store_true", default=True,
                    help="Preview changes (default)")
    ap.add_argument("--commit", action="store_true",
                    help="Write changes and build")
    args = ap.parse_args()

    if not SPEC_PATH.exists():
        print(f"FATAL: spec not found at {SPEC_PATH}", file=sys.stderr)
        return 2

    print("Parsing v17 §4 learnset tables...")
    spec_text = SPEC_PATH.read_text(encoding="utf-8")
    entries = parse_section4(spec_text)

    levelup = [e for e in entries if e.entry_type == "levelup"]
    teachable = [e for e in entries if e.entry_type == "teachable"]

    print(f"Parsed {len(entries)} entries: {len(levelup)} level-up, {len(teachable)} teachable")

    # Preview
    print(f"\n{'='*60}")
    print("LEVEL-UP ADDITIONS (→ gen_9.h):")
    print(f"{'='*60}")
    for e in levelup:
        sp = e.species_names[0]
        print(f"  {to_learnset_name(sp):30s} + LEVEL_UP_MOVE(1, {to_move_constant(e.move)})")

    print(f"\n{'='*60}")
    print("TEACHABLE ADDITIONS (→ all_learnables.json):")
    print(f"{'='*60}")
    for e in teachable:
        sp = e.species_names[0]
        print(f"  {to_json_key(sp):30s} + {to_move_constant(e.move)}")

    if not args.commit:
        print(f"\nDry-run complete. {len(levelup)} level-up + {len(teachable)} teachable.")
        print("Use --commit to write changes and build.")
        return 0

    # Commit mode
    assert_clean_tree()
    print("\n[1/5] clean-tree check: PASS")

    pre_gen9 = md5_file(GEN9_LEARNSETS)
    pre_json = md5_file(ALL_LEARNABLES)
    print(f"[2/5] pre-write MD5:")
    print(f"      gen_9.h:            {pre_gen9}")
    print(f"      all_learnables.json: {pre_json}")

    lu_applied, lu_skipped = apply_levelup_changes(entries)
    print(f"[3/5] level-up: {lu_applied} applied, {lu_skipped} skipped")

    tc_applied, tc_skipped = apply_teachable_changes(entries)
    print(f"[4/5] teachable: {tc_applied} applied, {tc_skipped} skipped")

    post_gen9 = md5_file(GEN9_LEARNSETS)
    post_json = md5_file(ALL_LEARNABLES)
    print(f"      gen_9.h:            {pre_gen9} → {post_gen9}")
    print(f"      all_learnables.json: {pre_json} → {post_json}")

    ncpu = os.cpu_count() or 1
    print(f"[5/5] running make -j{ncpu} ...")
    build = subprocess.run(
        ["make", f"-j{ncpu}"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    if build.returncode != 0:
        print("[5/5] BUILD FAILED — last 30 lines of stderr:", file=sys.stderr)
        for line in build.stderr.splitlines()[-30:]:
            print(line, file=sys.stderr)
        print("\nWrites NOT rolled back.", file=sys.stderr)
        return 1
    print("[5/5] build: PASS")

    rom_md5 = md5_file(REPO_ROOT / "pokeemerald.gba")
    print(f"\npokeemerald.gba MD5: {rom_md5}")
    print(f"\nTotal: {lu_applied} level-up + {tc_applied} teachable = {lu_applied + tc_applied} moves added")
    return 0


if __name__ == "__main__":
    sys.exit(main())
