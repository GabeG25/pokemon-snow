#!/usr/bin/env python3
"""
port_boss_fights.py — Pokémon Snow boss fight port tool.

Reads Section 5 of v17 (35 finalized fight tables) and emits trainerproc
blocks into trainers.party + flag #defines into opponents.h.

Boss fights differ from route trainers:
  - Headers: ## FIGHT N — NAME #N | Location | Singles/DOUBLES | Ace LvN
  - Variant fights (Asher/Autumn): A/B/C rows → 3 trainer entries per fight
  - 8 AI flags (5 standard + SETUP_FIRST_TURN + ACE_POKEMON + OMNISCIENT)
  - 11-column tables with EVs always present (0 for F1-F16)
  - All IVs 31 (not listed per row)
  - Boss trainer classes need character→class mapping (no real sprites yet)
"""

import argparse
import hashlib
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
SPEC_PATH = REPO_ROOT / "design-archive" / "POKEMON_SNOW_RESUME_HANDOFF_v17.md"
TRAINERS_PARTY = REPO_ROOT / "src" / "data" / "trainers.party"
OPPONENTS_H = REPO_ROOT / "include" / "constants" / "opponents.h"

# 8-flag AI suite for boss trainers
AI_SUITE_BOSS = ("Check Bad Move / Try To Faint / Check Viability / "
                 "Smart Switching / Smart Mon Choices / Force Setup First Turn / "
                 "Ace Pokemon / Omniscient")

# Custom items in v17 that don't exist in pokeemerald-expansion yet.
# Map to closest available item until real items are implemented.
# Permafrost Shard shipped natively as ITEM_PERMAFROST_SHARD (874) with
# HOLD_EFFECT_PERMAFROST_SHARD — 1.5x Ice for Kyurem. Fallback no longer needed.
ITEM_FALLBACKS = {
}

# Boss character → trainer class/pic/music/gender mapping.
# Pics use vanilla Emerald characters as fallbacks until real sprites ship.
BOSS_MAP = {
    # Gym Leaders → Leader class, use vanilla leader pics as fallbacks
    "SILVAN": {"class": "Leader", "pic": "Leader Roxanne", "music": "Female", "gender": "Male"},
    "CEDAR": {"class": "Leader", "pic": "Leader Brawly", "music": "Male", "gender": "Male"},
    "COPPER": {"class": "Leader", "pic": "Leader Wattson", "music": "Male", "gender": "Male"},
    "FRAN": {"class": "Leader", "pic": "Leader Flannery", "music": "Female", "gender": "Female"},
    "MARINA": {"class": "Leader", "pic": "Leader Winona", "music": "Female", "gender": "Female"},
    "PRIYO": {"class": "Leader", "pic": "Leader Norman", "music": "Male", "gender": "Male"},
    "ERIN": {"class": "Leader", "pic": "Leader Juan", "music": "Female", "gender": "Female"},
    "SCORCH": {"class": "Leader", "pic": "Leader Flannery", "music": "Male", "gender": "Male"},
    # Rivals → Rival class
    "ASHER": {"class": "Rival", "pic": "Brendan", "music": "Male", "gender": "Male"},
    "AUTUMN": {"class": "Rival", "pic": "May", "music": "Female", "gender": "Female"},
    # Team Veil admins → Pkmn Trainer 1
    "CRASH": {"class": "Pkmn Trainer 1", "pic": "Wally", "music": "Male", "gender": "Male"},
    "MIKA": {"class": "Pkmn Trainer 1", "pic": "May", "music": "Female", "gender": "Female"},
    "XENON": {"class": "Pkmn Trainer 1", "pic": "Brendan", "music": "Male", "gender": "Male"},
    "TYRELL": {"class": "Pkmn Trainer 1", "pic": "Wally", "music": "Male", "gender": "Male"},
    # Professor
    "EVERGREEN": {"class": "Pkmn Trainer 1", "pic": "Brendan", "music": "Male", "gender": "Male"},
    # Elite Four
    "BRYNN": {"class": "Elite Four", "pic": "Elite Four Phoebe", "music": "Elite Four", "gender": "Female"},
    "VESPER": {"class": "Elite Four", "pic": "Elite Four Sidney", "music": "Elite Four", "gender": "Male"},
    "REVERIE": {"class": "Elite Four", "pic": "Elite Four Glacia", "music": "Elite Four", "gender": "Female"},
    "WYATT": {"class": "Elite Four", "pic": "Elite Four Drake", "music": "Elite Four", "gender": "Male"},
    # Champion
    "TYRIM": {"class": "Champion", "pic": "Champion Wallace", "music": "Male", "gender": "Male"},
}

# Variant labels → starter type context (for constant naming)
VARIANT_LABELS = {"A": "A", "B": "B", "C": "C"}

# Species name remapping (same as port_trainers.py)
SPECIES_REMAP = {
    "Alolan Sandshrew": "Sandshrew-Alola",
    "Alolan Sandslash": "Sandslash-Alola",
    "Alolan Vulpix": "Vulpix-Alola",
    "Alolan Ninetales": "Ninetales-Alola",
    "Galarian Darumaka": "Darumaka-Galar",
    "Galarian Darmanitan": "Darmanitan-Galar",
}

# Boss fight header: ## FIGHT N — NAME #M | Location | Singles/DOUBLES | Ace LvN
BOSS_HEADER_RE = re.compile(
    r"^##\s+FIGHT\s+(\d+)\s+—\s+(.+?)\s+\|\s+(.+?)\s+\|\s+(Singles|DOUBLES|Doubles)\s+\|"
)


def _clean(cell: str) -> str | None:
    cell = cell.strip()
    if cell in ("", "—", "-"):
        return None
    cell = cell.replace("**", "")
    cell = re.sub(r"\s*\*?\((?:A[12]|HA[^)]*|CEO[^)]*)\)\*?", "", cell)
    cell = cell.strip()
    return cell if cell else None


@dataclass
class Mon:
    species: str
    level: int
    nature: str
    ability: str
    evs: str | None
    item: str | None
    moves: list[str]


@dataclass
class BossTrainer:
    fight_num: int
    name: str          # character name uppercase (ASHER, SILVAN, etc.)
    variant: str | None  # A/B/C for rival fights, None for non-variant
    is_double: bool
    mons: list[Mon] = field(default_factory=list)

    @property
    def constant(self) -> str:
        if self.variant:
            return f"TRAINER_SNOW_F{self.fight_num}_{self.name}_{self.variant}"
        return f"TRAINER_SNOW_F{self.fight_num}_{self.name}"

    @property
    def boss_info(self) -> dict:
        return BOSS_MAP.get(self.name, {
            "class": "Pkmn Trainer 1", "pic": "Brendan",
            "music": "Male", "gender": "Male",
        })


def parse_boss_table_row(line: str) -> list[str | None]:
    cells = [c.strip() for c in line.strip().strip("|").split("|")]
    return [_clean(c) for c in cells]


def parse_boss_fights(spec_text: str, fight_filter: int | None = None) -> list[BossTrainer]:
    lines = spec_text.splitlines()
    trainers: list[BossTrainer] = []
    i = 0
    n = len(lines)

    while i < n:
        m = BOSS_HEADER_RE.match(lines[i])
        if not m:
            i += 1
            continue

        fight_num = int(m.group(1))
        header_label = m.group(2).strip()
        battle_type = m.group(4).strip()
        is_double = battle_type.upper() == "DOUBLES"

        # Extract character name: "ASHER #1" → "ASHER", "GYM 1 SILVAN (Ice)" → "SILVAN"
        # "GYM 7 ERIN (Ground)" → "ERIN", "CRASH" → "CRASH"
        name_match = re.search(r"(?:GYM \d+ |ELITE FOUR )?(\w+)", header_label)
        boss_name = name_match.group(1).upper() if name_match else header_label.split()[0].upper()

        if fight_filter is not None and fight_num != fight_filter:
            i += 1
            continue

        # Find the table
        j = i + 1
        while j < n and not lines[j].lstrip().startswith("|"):
            j += 1
        if j >= n:
            i += 1
            continue

        # Detect column structure from header row
        header_cells = [c.strip() for c in lines[j].strip().strip("|").split("|")]
        first_col = header_cells[0].strip().lower() if header_cells else ""
        has_variant = first_col in ("var", "slot")

        j += 1  # skip header
        if j < n and lines[j].lstrip().startswith("|---"):
            j += 1  # skip separator

        # Parse rows
        all_mons: list[Mon] = []  # mons shared across all variants (ALL rows)
        variant_mons: dict[str, list[Mon]] = {}  # variant → mons

        while j < n and lines[j].lstrip().startswith("|"):
            cells = parse_boss_table_row(lines[j])
            j += 1

            if len(cells) < 11:
                continue

            if has_variant:
                # First cell is Var/Slot indicator
                var_cell = cells[0] if cells[0] else ""
                # Handle "Slot|Var" 12-column format
                if len(cells) >= 12 and first_col == "slot":
                    var_cell = cells[1] if cells[1] else ""
                    species_idx = 2
                else:
                    species_idx = 1

                species = cells[species_idx]
                if species is None:
                    continue
                species = SPECIES_REMAP.get(species, species)

                try:
                    level = int(cells[species_idx + 1])
                except (TypeError, ValueError):
                    continue

                nature = cells[species_idx + 2] or "Hardy"
                ability = cells[species_idx + 3] or "None"
                evs_raw = cells[species_idx + 4]
                evs = evs_raw if evs_raw and evs_raw != "0" else None
                item = cells[species_idx + 5]
                moves = [c for c in cells[species_idx + 6:species_idx + 10] if c]

                mon = Mon(species=species, level=level, nature=nature,
                         ability=ability, evs=evs, item=item, moves=moves)

                if var_cell.upper() == "ALL":
                    all_mons.append(mon)
                elif var_cell.upper() in ("A", "B", "C"):
                    variant_mons.setdefault(var_cell.upper(), []).append(mon)
                else:
                    # Numbered row (#1, #2, etc.) — non-variant boss
                    all_mons.append(mon)
            else:
                # Non-variant table (standard # | Species | ...)
                species = cells[1]
                if species is None:
                    continue
                species = SPECIES_REMAP.get(species, species)

                try:
                    level = int(cells[2])
                except (TypeError, ValueError):
                    continue

                nature = cells[3] or "Hardy"
                ability = cells[4] or "None"
                evs_raw = cells[5]
                evs = evs_raw if evs_raw and evs_raw != "0" else None
                item = cells[6]
                moves = [c for c in cells[7:11] if c]

                all_mons.append(Mon(species=species, level=level, nature=nature,
                                   ability=ability, evs=evs, item=item, moves=moves))

        # Build trainer entries
        if variant_mons:
            # Variant fight: create one trainer per variant
            for var in ("A", "B", "C"):
                if var not in variant_mons:
                    continue
                trainer = BossTrainer(
                    fight_num=fight_num, name=boss_name,
                    variant=var, is_double=is_double,
                    mons=all_mons + variant_mons[var],
                )
                trainers.append(trainer)
        else:
            # Non-variant fight: single trainer
            trainers.append(BossTrainer(
                fight_num=fight_num, name=boss_name,
                variant=None, is_double=is_double,
                mons=all_mons,
            ))

        i = j

    return trainers


def emit_boss(t: BossTrainer) -> str:
    info = t.boss_info
    header = [
        f"=== {t.constant} ===",
        f"Name: {t.name}",
        f"Class: {info['class']}",
        f"Pic: {info['pic']}",
        f"Gender: {info['gender']}",
        f"Music: {info['music']}",
        f"Double Battle: {'Yes' if t.is_double else 'No'}",
        f"AI: {AI_SUITE_BOSS}",
    ]
    mon_blocks: list[str] = []
    for mon in t.mons:
        species_line = mon.species
        if mon.item:
            item = ITEM_FALLBACKS.get(mon.item, mon.item)
            species_line += f" @ {item}"
        block = [
            species_line,
            f"Level: {mon.level}",
        ]
        if mon.evs:
            block.append(f"EVs: {mon.evs}")
        block.extend([
            f"Ability: {mon.ability}",
            f"Nature: {mon.nature}",
        ])
        block.extend(f"- {mv}" for mv in mon.moves)
        mon_blocks.append("\n".join(block))
    return "\n".join(header) + "\n\n" + "\n\n".join(mon_blocks)


# ─── opponents.h manipulation (shared logic from port_trainers.py) ──────────

DEFINE_SLOT_COLUMN = 44
COUNT_LINE_RE = re.compile(r"^(#define TRAINERS_COUNT_EMERALD\s+)(\d+)\s*$", re.MULTILINE)
MAX_LINE_RE = re.compile(r"^#define MAX_TRAINERS_COUNT_EMERALD\s+(\d+)\s*$", re.MULTILINE)
WARNING_COMMENT_RE = re.compile(r"(there is only space for )(\d+)( additional trainers)")
LAST_TRAINER_DEFINE_RE = re.compile(
    r"^#define (TRAINER_[A-Z0-9_]+)(\s+)(\d+)[ \t]*$", re.MULTILINE
)


def format_define_line(name: str, slot: int) -> str:
    prefix = f"#define {name}"
    padding = max(1, DEFINE_SLOT_COLUMN - len(prefix))
    return f"{prefix}{' ' * padding}{slot}"


def md5_file(path: Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()


def assert_clean_tree() -> None:
    unstaged = subprocess.run(["git", "diff", "--quiet"], cwd=REPO_ROOT).returncode
    staged = subprocess.run(["git", "diff", "--cached", "--quiet"], cwd=REPO_ROOT).returncode
    if unstaged != 0 or staged != 0:
        raise SystemExit("FATAL: uncommitted changes. Commit or stash before --commit.")


def read_current_count(text: str) -> int:
    m = COUNT_LINE_RE.search(text)
    if not m:
        raise SystemExit("FATAL: TRAINERS_COUNT_EMERALD not found")
    return int(m.group(2))


def read_max_count(text: str) -> int:
    m = MAX_LINE_RE.search(text)
    if not m:
        raise SystemExit("FATAL: MAX_TRAINERS_COUNT_EMERALD not found")
    return int(m.group(1))


def append_trainer_blocks(parsed: list[BossTrainer]) -> None:
    party_text = TRAINERS_PARTY.read_text(encoding="utf-8")
    body = party_text.rstrip("\n")
    new_blocks = "\n\n".join(emit_boss(t) for t in parsed)
    TRAINERS_PARTY.write_text(body + "\n\n" + new_blocks, encoding="utf-8")


def update_opponents_h(parsed: list[BossTrainer], current_count: int,
                       max_count: int) -> tuple[int, int]:
    text = OPPONENTS_H.read_text(encoding="utf-8")
    warning_start = text.find("// NOTE: Because each Trainer uses a flag")
    if warning_start == -1:
        raise SystemExit("FATAL: warning comment not found")
    region_above = text[:warning_start]
    last_match = None
    for m in LAST_TRAINER_DEFINE_RE.finditer(region_above):
        last_match = m
    if last_match is None:
        raise SystemExit("FATAL: no trainer defines above warning")

    new_lines = [
        format_define_line(t.constant, current_count + i)
        for i, t in enumerate(parsed)
    ]
    insertion = "\n" + "\n".join(new_lines)
    insert_at = last_match.end()
    text = text[:insert_at] + insertion + text[insert_at:]

    new_count = current_count + len(parsed)
    new_remaining = max_count - new_count

    text, n_count = COUNT_LINE_RE.subn(lambda m: f"{m.group(1)}{new_count}", text, count=1)
    if n_count != 1:
        raise SystemExit("FATAL: count-line sub failed")
    text, n_warn = WARNING_COMMENT_RE.subn(
        lambda m: f"{m.group(1)}{new_remaining}{m.group(3)}", text, count=1)
    if n_warn != 1:
        raise SystemExit("FATAL: warning-comment sub failed")

    OPPONENTS_H.write_text(text, encoding="utf-8")

    verify = OPPONENTS_H.read_text(encoding="utf-8")
    if read_current_count(verify) != new_count:
        raise SystemExit("FATAL: post-write count verification failed")
    return new_count, new_remaining


def main() -> int:
    ap = argparse.ArgumentParser(description="Port boss fights from v17 §5.")
    ap.add_argument("--fight", type=int, help="Port only this fight number")
    ap.add_argument("--all", action="store_true", help="Port all 35 fights")
    ap.add_argument("--dry-run", action="store_true", default=True)
    ap.add_argument("--commit", action="store_true")
    args = ap.parse_args()

    if not SPEC_PATH.exists():
        print(f"FATAL: spec not found", file=sys.stderr)
        return 2
    if args.fight is None and not args.all:
        print("FATAL: pass --fight N or --all", file=sys.stderr)
        return 2

    spec_text = SPEC_PATH.read_text(encoding="utf-8")
    trainers = parse_boss_fights(spec_text, fight_filter=args.fight)

    print(f"Parsed {len(trainers)} trainer entries from "
          f"{'F' + str(args.fight) if args.fight else 'all'} boss fights")

    if not args.commit:
        for t in trainers:
            print(emit_boss(t))
            print()
        print(f"# {len(trainers)} trainer entries, "
              f"{sum(len(t.mons) for t in trainers)} Pokémon total")
        return 0

    # Commit mode
    assert_clean_tree()
    print("[1/5] clean-tree check: PASS")

    opp_text = OPPONENTS_H.read_text(encoding="utf-8")
    current_count = read_current_count(opp_text)
    max_count = read_max_count(opp_text)
    print(f"[2/5] count={current_count}, MAX={max_count}")

    if current_count + len(trainers) > max_count:
        raise SystemExit(f"FATAL: ceiling exceeded ({current_count} + {len(trainers)} > {max_count})")
    print(f"[3/5] ceiling check: PASS ({current_count} + {len(trainers)} = {current_count + len(trainers)})")

    pre_party = md5_file(TRAINERS_PARTY)
    pre_opp = md5_file(OPPONENTS_H)

    append_trainer_blocks(trainers)
    new_count, new_remaining = update_opponents_h(trainers, current_count, max_count)
    print(f"[4/5] wrote {len(trainers)} boss trainers, count {current_count}→{new_count}, "
          f"{new_remaining} slots remaining")

    ncpu = os.cpu_count() or 1
    print(f"[5/5] running make -j{ncpu} ...")
    build = subprocess.run(["make", f"-j{ncpu}"], cwd=REPO_ROOT,
                          capture_output=True, text=True)
    if build.returncode != 0:
        print("[5/5] BUILD FAILED:", file=sys.stderr)
        for line in build.stderr.splitlines()[-30:]:
            print(line, file=sys.stderr)
        return 1
    print("[5/5] build: PASS")

    rom_md5 = md5_file(REPO_ROOT / "pokeemerald.gba")
    print(f"\npokeemerald.gba MD5: {rom_md5}")
    print(f"\n{len(trainers)} boss trainer entries shipped")
    return 0


if __name__ == "__main__":
    sys.exit(main())
