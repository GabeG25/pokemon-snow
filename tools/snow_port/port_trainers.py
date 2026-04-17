#!/usr/bin/env python3
"""
port_trainers.py — Pokémon Snow trainer porting pipeline.

Reads Section 20 of design-archive/POKEMON_SNOW_RESUME_HANDOFF_v17.md and
emits trainerproc blocks into src/data/trainers.party plus flag #defines into
include/constants/opponents.h. Replaces the manual 3-trainers-per-session
porting workflow validated during the R1 arc.

LOCKED CONTRACT (CEO-confirmed 2026-04-11, post R1 arc):

  1. v17 §20 is canonical. The shipped trainers.party is the source of truth
     for the *current* state, but is allowed to be wrong when it contradicts
     v17. The R1 normalization commit (4a0e279864) backfilled R1-1/R1-2 AI
     lines from probing-phase 1-flag residue to the spec-mandated 5-flag
     suite. From now on, the parser hard-codes the 5-flag AI as the universal
     default — no --ai-level flag, no per-trainer override. v17 §20 line 3402
     "Smart AI on all" is the global rule. If a future v17 entry implies
     otherwise, the parser raises rather than silently degrading.

  2. Round-trip semantic: --route R1 --dry-run must produce output that is
     byte-identical to the current shipped R1 trainer blocks (HEAD 4a0e279864,
     post-normalization). The 4-commit R1 history was a probing artifact;
     the tool emits the final consolidated state in one shot. Going forward:
     one commit per route batch. Round-trip mode is auto-detected: if a route
     already has blocks in trainers.party, --dry-run runs the validator; if
     not, --dry-run runs the preview emitter.

  3. opponents.h side-effect is dormant on already-shipped routes. R1's
     4 flags are already present in opponents.h (R1 shipped green, ROM
     compiles → proof). Re-emitting them would double-insert and corrupt
     the file. Round-trip mode (--route R1 on a shipped route) skips the
     opponents.h emitter entirely and only diffs trainers.party. The
     opponents.h logic activates only with --commit on R2+.

Future-you reading this in 3 months: if you're tempted to add an --ai-level
flag, re-read decision #1. If you're tempted to make round-trip diff against
4 separate commits, re-read decision #2. If you're tempted to let the
opponents.h emitter run on R1, re-read decision #3.
"""

import argparse
import difflib
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

AI_SUITE_FULL = "Check Bad Move / Try To Faint / Check Viability / Smart Switching / Smart Mon Choices"

# v17 spec uses "Alolan Sandshrew" but trainerproc needs "Sandshrew-Alola" to
# generate SPECIES_SANDSHREW_ALOLA. This table remaps spec species names to
# engine species names. Applied in _clean_species() after general _clean().
SPECIES_REMAP = {
    "Alolan Sandshrew": "Sandshrew-Alola",
    "Alolan Sandslash": "Sandslash-Alola",
    "Alolan Vulpix": "Vulpix-Alola",
    "Alolan Ninetales": "Ninetales-Alola",
    "Galarian Darumaka": "Darumaka-Galar",
    "Galarian Darmanitan": "Darmanitan-Galar",
}

CLASS_FALLBACKS = {
    # Mountain/outdoor classes → Hiker (validated commits 592e85b064, 43ffd4cfb2)
    "Boarder": "Hiker",
    "Skier": "Hiker",
    "Miner": "Hiker",
    # FRLG variant remaps (class exists only as _FRLG in engine)
    "Scientist": "Scientist Frlg",
    "Painter": "Painter Frlg",      # probed R7 build — TRAINER_CLASS_PAINTER undeclared
    # Name remaps (same class, different string in engine)
    "Ace Trainer": "Cooltrainer",    # Gen 5+ name → Gen 3 name
    "Pokémon Ranger": "Pkmn Ranger", # full name → engine abbreviation
    "Ranger": "Pkmn Ranger",         # DI-5 Heath uses short form
    # Creative fallbacks (no engine equivalent exists)
    "Musician": "Guitarist",         # closest musical performer class
    "Special Agent": "Cooltrainer",  # elite operative → elite trainer
    "Tycoon": "Gentleman",           # wealthy trainer archetype
    "Pokémon Tycoon": "Gentleman",   # same
}

# Grunt team name → engine team name. Derives Class/Pic/Music:
#   Class: "Team {resolved}"   Pic: "{resolved} Grunt M"   Music: "{resolved}"
GRUNT_TEAM_FALLBACK = {
    "Veil": "Magma",  # Team Veil is design-archive only; pre-loaded to Magma (closest evil-team asset in pokeemerald-expansion). Revisit when real Team Veil class assets ship.
}

# Per-slot story name overrides for Team Veil grunts. v17 §20 lists grunts as
# "Team Veil Grunt" (unnamed). Story dialogue in commit 2dc698ff12 assigned
# narrative names to the Act 1 Veil first-contact set; this dict preserves
# them for byte-identical round-trip with trainers.party.
GRUNT_NAME_OVERRIDES = {
    (3, 5): "Kael",  # R3-5: first Veil contact (Pinehurst Woods)
    (5, 3): "Bran",  # R5-3: Ironfrost Cave singles grunt #1
    (5, 4): "Nyla",  # R5-4: Ironfrost Cave singles grunt #2
    (5, 5): "Orin",  # R5-5: Ironfrost Cave tag-double partner A
    (5, 6): "Lira",  # R5-6: Ironfrost Cave tag-double partner B
}

CLASS_GENDER_DEFAULTS = {
    # Spec class names (pre-fallback)
    "Youngster": "Male",
    "Lass": "Female",
    "Hiker": "Male",
    "Boarder": "Male",
    "Skier": "Female",
    "Miner": "Male",
    "Bug Catcher": "Male",
    "Scientist": "Male",
    "Fisherman": "Male",
    "Lady": "Female",
    "Collector": "Male",
    "Painter": "Female",
    "Musician": "Male",
    "Dragon Tamer": "Male",
    "Sailor": "Male",
    "Swimmer": "Female",
    "Ace Trainer": "Male",
    "Pokémon Ranger": "Male",
    "Special Agent": "Male",
    "Ranger": "Male",
    "Tycoon": "Male",
    "Pokémon Tycoon": "Male",
    # Post-fallback resolved names (needed because gender lookup uses emit_class)
    "Scientist Frlg": "Male",
    "Painter Frlg": "Female",
    "Cooltrainer": "Male",
    "Pkmn Ranger": "Male",
    "Guitarist": "Male",
    "Gentleman": "Male",
    "Swimmer M": "Male",
    "Swimmer F": "Female",
}

# Matches "R{N}-{M}", "DI-{M}", and "VR-{M}" route headers.
# Group 1: route identifier (digits for R-routes, None for DI/VR)
# Group 2: trainer index within route
# Group 3: class + name label
# Group 4: Pokémon count
VR_ROUTE_NUM = 200  # synthetic route number for Victory Road
TRAINER_HEADER_RE = re.compile(
    r"^###\s+(?:R(\d+)|(DI|VR))-(\d+)\s+—\s+(.+?)\s+\|\s+(\d+)\s+Pokémon(?:\s*\|.*)?\s*$"
)

# Matches tag-double headers. Four known variants in v17:
#   R5-5/6 — Team Veil Grunts | 3 Pokémon each | TAG DOUBLE BATTLE
#   R6-7 — Skier Ivy & Boarder Hale | TAG DOUBLE BATTLE | 3 + 3 Pokémon
#   R12-6 — Special Agent Slade & Special Agent Quinn | TAG DOUBLE BATTLE | 3 + 3 Pokémon
#   R14-8 — Sailor Marek & Sailor Halden | TAG DOUBLE BATTLE | 4 + 4 Pokémon | **R14 PEAK**
TAG_DOUBLE_HEADER_RE = re.compile(
    r"^###\s+R(\d+)-([\d/]+)\s+—\s+(.+?)\s+\|.*TAG DOUBLE BATTLE.*$"
)

# Classes where the engine uses gendered class names (e.g., "Swimmer M"/"Swimmer F").
# The spec uses the ungendered name; gender is derived from trainer name.
GENDERED_CLASS_NAMES = {
    "Swimmer": {"M": "Swimmer M", "F": "Swimmer F"},
}
# Male trainer names for gendered classes. Names not listed default to Female.
GENDERED_CLASS_MALE_NAMES = {
    "Swimmer": {"Troy", "Flynn", "Triton", "Nemo"},  # DI: Flynn; R9: Troy; R15: Triton, Nemo
}

# Classes where the Pic string differs from the Class string. Most classes use
# Pic == Class, but gendered classes and name-remap classes need overrides.
# Value is a format string with {gender} placeholder for M/F substitution.
PIC_OVERRIDE = {
    "Cooltrainer": "Cooltrainer {gender}",       # gendered pics
    "Pkmn Ranger": "Pokemon Ranger {gender}",    # class name != pic name + gendered
}

# Matches bold sub-labels within a tag-double block: **Grunt 5:** or **Skier Ivy:**
TAG_SUB_LABEL_RE = re.compile(r"^\*\*(.+?):\*\*\s*$")


@dataclass
class Mon:
    species: str
    level: int
    nature: str
    ability: str
    item: str | None
    moves: list[str]
    evs: str | None = None


DI_ROUTE_NUM = 100  # synthetic route number for Driftrock Isle (DI) in internal logic


@dataclass
class Trainer:
    route: int
    index: int
    klass: str  # canonical class from spec (pre-fallback)
    name: str
    is_grunt: bool = False
    team: str | None = None  # e.g. "Veil" for Team Veil Grunt
    story_name: str | None = None  # narrative override for `Name:` field (grunts only). Constant ID still uses `name`.
    mons: list[Mon] = field(default_factory=list)

    @property
    def emit_class(self) -> str:
        if self.is_grunt:
            t = GRUNT_TEAM_FALLBACK.get(self.team, self.team)
            return f"Team {t}"
        resolved = CLASS_FALLBACKS.get(self.klass, self.klass)
        if resolved in GENDERED_CLASS_NAMES:
            g = "M" if self.name in GENDERED_CLASS_MALE_NAMES.get(resolved, set()) else "F"
            return GENDERED_CLASS_NAMES[resolved][g]
        return resolved

    @property
    def emit_pic(self) -> str:
        if self.is_grunt:
            t = GRUNT_TEAM_FALLBACK.get(self.team, self.team)
            return f"{t} Grunt M"
        ec = self.emit_class
        if ec in PIC_OVERRIDE:
            g = "M" if self.gender == "Male" else "F"
            return PIC_OVERRIDE[ec].format(gender=g)
        return ec

    @property
    def emit_music(self) -> str:
        if self.is_grunt:
            t = GRUNT_TEAM_FALLBACK.get(self.team, self.team)
            return t
        return self.gender

    @property
    def gender(self) -> str:
        if self.is_grunt:
            return "Male"  # CEO-approved default 2026-04-12. Spec silent on grunt gender. Revisit per-grunt when real Veil assets ship.
        ec = self.emit_class
        if ec not in CLASS_GENDER_DEFAULTS:
            raise ValueError(
                f"R{self.route}-{self.index} {self.name}: unknown class '{ec}' — "
                f"add to CLASS_GENDER_DEFAULTS before porting"
            )
        return CLASS_GENDER_DEFAULTS[ec]

    @property
    def route_label(self) -> str:
        if self.route == DI_ROUTE_NUM:
            return "DI"
        if self.route == VR_ROUTE_NUM:
            return "VR"
        return f"R{self.route}"

    @property
    def constant(self) -> str:
        return f"TRAINER_SNOW_{self.route_label}_{self.index}_{self.name.upper()}"


# Assumes trainer names are single-token. Multi-word names (e.g., "Mary Ann")
# will be misparsed — the last token will be taken as the full name and earlier
# tokens absorbed into the class. v17 has no multi-word names through R10 as of
# 2026-04-11. Revisit if a future entry breaks this.
def split_class_and_name(header_label: str) -> tuple[str, str]:
    parts = header_label.strip().split()
    return " ".join(parts[:-1]), parts[-1]


def _clean(cell: str) -> str | None:
    cell = cell.strip()
    if cell in ("", "—", "-"):
        return None
    cell = cell.replace("**", "")  # strip markdown bold markers
    cell = re.sub(r"\s*\*?\((?:A[12]|HA[^)]*|CEO[^)]*)\)\*?", "", cell)  # strip annotations
    cell = cell.strip()
    return cell if cell else None


def parse_table_row(row_line: str) -> list[str | None]:
    cells = [c.strip() for c in row_line.strip().strip("|").split("|")]
    return [_clean(c) for c in cells]


def _parse_mon_table(lines: list[str], start: int, n: int,
                     route: int, index: int, name: str) -> tuple[list[Mon], int]:
    """Parse a markdown table of Pokémon starting at line `start`.
    Returns (list of Mon, next line index after table).
    Handles both 10-column (no EVs) and 11-column (with EVs) tables."""
    j = start
    # Skip blank lines and non-table text (e.g., italic annotations like
    # "*Accessible only after obtaining Surf*") until we find a | table row.
    while j < n and not lines[j].lstrip().startswith("|"):
        j += 1
    if j >= n:
        raise ValueError(f"R{route}-{index} {name}: no table found")
    # Detect column count from header row
    header_cells = [c.strip() for c in lines[j].strip().strip("|").split("|")]
    has_evs = any(c.strip().lower() == "evs" for c in header_cells)
    j += 1  # skip header row
    if j >= n or not lines[j].lstrip().startswith("|"):
        raise ValueError(f"R{route}-{index} {name}: no separator row")
    j += 1  # skip separator row
    mons: list[Mon] = []
    while j < n and lines[j].lstrip().startswith("|"):
        cells = parse_table_row(lines[j])
        min_cols = 11 if has_evs else 10
        if len(cells) < min_cols:
            raise ValueError(
                f"R{route}-{index} {name}: row has {len(cells)} cells, expected {min_cols}"
            )
        species = cells[1]
        if species is None:
            raise ValueError(f"R{route}-{index} {name}: species is empty in row")
        species = SPECIES_REMAP.get(species, species)
        try:
            level = int(cells[2])
        except (TypeError, ValueError):
            raise ValueError(
                f"R{route}-{index} {name}: invalid level '{cells[2]}' — "
                f"expected integer"
            )
        nature = cells[3]
        if nature is None:
            raise ValueError(f"R{route}-{index} {name}: nature is empty in row")
        ability = cells[4]
        if has_evs:
            evs = cells[5]
            item = cells[6]
            moves = [c for c in cells[7:11] if c is not None]
        else:
            evs = None
            item = cells[5]
            moves = [c for c in cells[6:10] if c is not None]
        if not moves:
            raise ValueError(f"R{route}-{index} {name}: zero moves parsed")
        mons.append(
            Mon(species=species, level=level, nature=nature,
                ability=ability, item=item, moves=moves, evs=evs)
        )
        j += 1
    return mons, j


def _parse_tag_double(lines: list[str], start: int, n: int,
                      route: int, index_str: str, label: str,
                      ) -> tuple[list[Trainer], int]:
    """Parse a tag-double block (two sub-labeled trainers under one ### header).
    Returns (list of 2 Trainers, next line index after block)."""
    # Determine if grunt variant (R5-5/6) or named variant (R6-7)
    is_grunt_double = "&" not in label

    if is_grunt_double:
        # Indices explicit in header: "5/6"
        indices = [int(x) for x in index_str.split("/")]
        if len(indices) != 2:
            raise ValueError(f"R{route}-{index_str}: expected 2 indices in grunt tag-double")
        header_pairs = None
    else:
        # Named variant: single index in header, second trainer is index+1
        base_idx = int(index_str)
        indices = [base_idx, base_idx + 1]
        # Extract class+name from HEADER (not sub-labels, which may abbreviate)
        # Header label is like "Skier Ivy & Boarder Hale" or "Special Agent Slade & Special Agent Quinn"
        pair_strs = [p.strip() for p in label.split("&")]
        if len(pair_strs) != 2:
            raise ValueError(f"R{route}-{index_str}: expected 2 trainers in header, got {len(pair_strs)}")
        header_pairs = [split_class_and_name(p) for p in pair_strs]

    # Find the two sub-label sections
    j = start + 1
    sub_trainers: list[Trainer] = []
    found_labels = 0

    while j < n and found_labels < 2:
        sub_m = TAG_SUB_LABEL_RE.match(lines[j].strip())
        if sub_m:
            idx = indices[found_labels]

            if is_grunt_double:
                # Sub-label like "Grunt 5" — these are Team Veil grunts
                klass = "Team Veil"
                trainer_name = "Grunt"
                is_grunt = True
                team = "Veil"
                story_name = GRUNT_NAME_OVERRIDES.get((route, idx))
            else:
                # Use header-derived class+name (sub-labels may abbreviate)
                klass, trainer_name = header_pairs[found_labels]
                is_grunt = False
                team = None

            mons, j = _parse_mon_table(lines, j + 1, n, route, idx, trainer_name)
            sub_trainers.append(
                Trainer(route=route, index=idx, klass=klass, name=trainer_name,
                        is_grunt=is_grunt, team=team,
                        story_name=story_name if is_grunt_double else None,
                        mons=mons)
            )
            found_labels += 1
        else:
            j += 1
            # Safety: don't scan past the next ### header
            if j < n and lines[j].startswith("### "):
                break

    if found_labels != 2:
        raise ValueError(
            f"R{route}-{index_str}: expected 2 sub-labels in tag-double block, "
            f"found {found_labels}"
        )
    return sub_trainers, j


def parse_spec(spec_text: str, route_filter: int | None = None) -> list[Trainer]:
    lines = spec_text.splitlines()
    trainers: list[Trainer] = []
    i = 0
    n = len(lines)
    while i < n:
        # Try tag-double header first (more specific match)
        td_m = TAG_DOUBLE_HEADER_RE.match(lines[i])
        if td_m:
            route = int(td_m.group(1))
            index_str = td_m.group(2)
            label = td_m.group(3)
            if route_filter is not None and route != route_filter:
                i += 1
                continue
            pair, i = _parse_tag_double(lines, i, n, route, index_str, label)
            trainers.extend(pair)
            continue

        # Try single-trainer header
        m = TRAINER_HEADER_RE.match(lines[i])
        if not m:
            i += 1
            continue
        if m.group(1):
            route = int(m.group(1))
        elif m.group(2) == "VR":
            route = VR_ROUTE_NUM
        else:
            route = DI_ROUTE_NUM
        index = int(m.group(3))
        label = m.group(4)
        expected_count = int(m.group(5))
        klass, name = split_class_and_name(label)
        is_grunt = name == "Grunt" and klass.startswith("Team ")
        team = klass.split(" ", 1)[1] if is_grunt else None
        story_name = GRUNT_NAME_OVERRIDES.get((route, index)) if is_grunt else None

        if route_filter is not None and route != route_filter:
            i += 1
            continue

        mons, i = _parse_mon_table(lines, i + 1, n, route, index, name)
        if len(mons) != expected_count:
            raise ValueError(
                f"R{route}-{index} {name}: header says {expected_count} mons, "
                f"parsed {len(mons)}"
            )
        trainers.append(
            Trainer(route=route, index=index, klass=klass, name=name,
                    is_grunt=is_grunt, team=team, story_name=story_name, mons=mons)
        )
    return trainers


# Parses the tag-double list at v17 §20 lines 459-463. Handles the "R5-5/6"
# syntax that fans out to (5,5) and (5,6). Dormant for R1/R2/R3 (no doubles).
DOUBLE_LINE_RE = re.compile(r"^-\s+\*\*R(\d+)-([\d/]+)\b", re.MULTILINE)


def parse_double_battles(spec_text: str) -> set[tuple[int, int]]:
    start = spec_text.find("### Tag double battles")
    if start == -1:
        return set()
    end = spec_text.find("\n### ", start + 1)
    if end == -1:
        end = len(spec_text)
    section = spec_text[start:end]
    out: set[tuple[int, int]] = set()
    for m in DOUBLE_LINE_RE.finditer(section):
        route = int(m.group(1))
        idx_parts = m.group(2).split("/")
        if len(idx_parts) == 2:
            # Explicit pair like "5/6" — both indices listed
            for idx_str in idx_parts:
                out.add((route, int(idx_str)))
        else:
            # Single index like "7" — named pair, implicit N and N+1
            base = int(idx_parts[0])
            out.add((route, base))
            out.add((route, base + 1))
    return out


def assert_spec_compliance(trainers: list[Trainer]) -> None:
    """Per locked decision #1: every parsed trainer must be eligible for the
    universal 5-flag AI suite. There is currently no spec carve-out, so this
    is a placeholder that exists to fail loudly if a future v17 entry
    introduces per-trainer AI variation that the parser does not handle."""
    for _t in trainers:
        pass


# ─── Emitter ──────────────────────────────────────────────────────────────────


def emit_trainer(t: Trainer, double_battles: set[tuple[int, int]]) -> str:
    is_double = (t.route, t.index) in double_battles
    display_name = (t.story_name or t.name).upper()
    header = [
        f"=== {t.constant} ===",
        f"Name: {display_name}",
        f"Class: {t.emit_class}",
        f"Pic: {t.emit_pic}",
        f"Gender: {t.gender}",
        f"Music: {t.emit_music}",
        f"Double Battle: {'Yes' if is_double else 'No'}",
        f"AI: {AI_SUITE_FULL}",
    ]
    mon_blocks: list[str] = []
    for mon in t.mons:
        species_line = mon.species
        if mon.item:
            species_line += f" @ {mon.item}"
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


# ─── Round-trip validator ────────────────────────────────────────────────────


# Anchored to column 0, line-bounded. Terminates at next ^=== header or EOF.
def _shipped_block_re(route: int) -> re.Pattern:
    label = "DI" if route == DI_ROUTE_NUM else f"R{route}"
    return re.compile(
        rf"^=== TRAINER_SNOW_{label}_(\d+)_[A-Z0-9_]+ ===.*?(?=^=== |\Z)",
        re.MULTILINE | re.DOTALL,
    )


def extract_shipped_blocks(route: int, party_text: str) -> dict[int, str]:
    out: dict[int, str] = {}
    for m in _shipped_block_re(route).finditer(party_text):
        idx = int(m.group(1))
        out[idx] = m.group(0).rstrip()
    return out


def round_trip_validate(route: int, parsed: list[Trainer],
                        double_battles: set[tuple[int, int]],
                        party_text: str) -> int:
    shipped = extract_shipped_blocks(route, party_text)
    if len(parsed) != len(shipped):
        print(
            f"R{route} round-trip: COUNT MISMATCH — parsed {len(parsed)} trainers, "
            f"extracted {len(shipped)} shipped blocks. Round-trip is meaningless.",
            file=sys.stderr,
        )
        print(f"  parsed indices:    {sorted(t.index for t in parsed)}", file=sys.stderr)
        print(f"  shipped indices:   {sorted(shipped.keys())}", file=sys.stderr)
        return 2

    mismatches: list[tuple[Trainer, str, str]] = []
    for t in parsed:
        emitted = emit_trainer(t, double_battles).rstrip()
        ship = shipped.get(t.index)
        if ship is None:
            mismatches.append((t, "<MISSING from shipped file>", emitted))
            continue
        if emitted != ship:
            mismatches.append((t, ship, emitted))

    if not mismatches:
        print(f"R{route} round-trip: PASS ({len(parsed)} trainers byte-identical)")
        return 0

    print(
        f"R{route} round-trip: FAIL ({len(mismatches)}/{len(parsed)} trainers diverge)",
        file=sys.stderr,
    )
    first_t, first_ship, first_emit = mismatches[0]
    diff_lines = list(
        difflib.unified_diff(
            first_ship.splitlines(),
            first_emit.splitlines(),
            fromfile=f"shipped/R{first_t.route}-{first_t.index}_{first_t.name}",
            tofile=f"emitted/R{first_t.route}-{first_t.index}_{first_t.name}",
            n=3,
            lineterm="",
        )
    )
    for line in diff_lines:
        print(line, file=sys.stderr)
    if len(diff_lines) > 50:
        for i, (s, e) in enumerate(
            zip(first_ship.splitlines(), first_emit.splitlines()), 1
        ):
            if s != e:
                print(
                    f"\nFirst mismatch in R{first_t.route}-{first_t.index} "
                    f"{first_t.name} block, line {i}:\n"
                    f"  shipped: {s!r}\n  emitted: {e!r}",
                    file=sys.stderr,
                )
                break
    if len(mismatches) > 1:
        print(
            f"\n(+{len(mismatches) - 1} more diverging trainer(s); "
            f"fix the first and re-run)",
            file=sys.stderr,
        )
    return 1


# ─── Commit mode ─────────────────────────────────────────────────────────────

# opponents.h column-aligned define style. Slot column is 44 (matches NOEL,
# MARIELA, and the rest of the file). Set by the c0fd8e830c normalization
# commit. If a name is too long to fit before column 44, fall back to one space.
DEFINE_SLOT_COLUMN = 44

COUNT_LINE_RE = re.compile(
    r"^(#define TRAINERS_COUNT_EMERALD\s+)(\d+)\s*$", re.MULTILINE
)
MAX_LINE_RE = re.compile(
    r"^#define MAX_TRAINERS_COUNT_EMERALD\s+(\d+)\s*$", re.MULTILINE
)
WARNING_COMMENT_RE = re.compile(
    r"(there is only space for )(\d+)( additional trainers)"
)
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
    unstaged = subprocess.run(
        ["git", "diff", "--quiet"], cwd=REPO_ROOT
    ).returncode
    staged = subprocess.run(
        ["git", "diff", "--cached", "--quiet"], cwd=REPO_ROOT
    ).returncode
    if unstaged != 0 or staged != 0:
        raise SystemExit(
            "FATAL: working tree has uncommitted changes to tracked files. "
            "Commit or stash before running --commit."
        )


def read_current_count(opponents_text: str) -> int:
    m = COUNT_LINE_RE.search(opponents_text)
    if not m:
        raise SystemExit("FATAL: could not locate TRAINERS_COUNT_EMERALD line")
    return int(m.group(2))


def read_max_count(opponents_text: str) -> int:
    m = MAX_LINE_RE.search(opponents_text)
    if not m:
        raise SystemExit("FATAL: could not locate MAX_TRAINERS_COUNT_EMERALD line")
    return int(m.group(1))


def read_warning_remaining(opponents_text: str) -> int:
    m = WARNING_COMMENT_RE.search(opponents_text)
    if not m:
        raise SystemExit("FATAL: could not locate ceiling warning comment")
    return int(m.group(2))


def append_trainer_blocks(parsed: list[Trainer],
                          double_battles: set[tuple[int, int]]) -> None:
    party_text = TRAINERS_PARTY.read_text(encoding="utf-8")
    body = party_text.rstrip("\n")  # preserve no-trailing-newline rule
    new_blocks = "\n\n".join(emit_trainer(t, double_battles) for t in parsed)
    new_text = body + "\n\n" + new_blocks
    TRAINERS_PARTY.write_text(new_text, encoding="utf-8")


def update_opponents_h(parsed: list[Trainer], current_count: int,
                       max_count: int) -> tuple[int, int]:
    text = OPPONENTS_H.read_text(encoding="utf-8")

    # Find the LAST existing trainer-region #define (above the warning comment).
    # The warning comment splits the file: trainer defines above, count line
    # below. We insert immediately after the last trainer define above the
    # comment, preserving the file's region structure (locked by c0fd8e830c).
    warning_start = text.find("// NOTE: Because each Trainer uses a flag")
    if warning_start == -1:
        raise SystemExit("FATAL: could not locate ceiling warning comment block")
    region_above = text[:warning_start]
    last_match = None
    for m in LAST_TRAINER_DEFINE_RE.finditer(region_above):
        last_match = m
    if last_match is None:
        raise SystemExit("FATAL: no existing trainer #define lines above warning")

    new_lines = [
        format_define_line(t.constant, current_count + i)
        for i, t in enumerate(parsed)
    ]
    insertion = "\n" + "\n".join(new_lines)
    insert_at = last_match.end()  # end of last existing trainer define line
    text = text[:insert_at] + insertion + text[insert_at:]

    new_count = current_count + len(parsed)
    new_remaining = max_count - new_count

    # Update count line — preserve exact prefix whitespace (5 spaces).
    text, n_count = COUNT_LINE_RE.subn(
        lambda m: f"{m.group(1)}{new_count}", text, count=1
    )
    if n_count != 1:
        raise SystemExit("FATAL: count-line substitution did not match exactly once")

    # Update warning comment number.
    text, n_warn = WARNING_COMMENT_RE.subn(
        lambda m: f"{m.group(1)}{new_remaining}{m.group(3)}", text, count=1
    )
    if n_warn != 1:
        raise SystemExit("FATAL: warning-comment substitution did not match exactly once")

    OPPONENTS_H.write_text(text, encoding="utf-8")

    # Verify post-write by re-reading and grepping the new values.
    verify = OPPONENTS_H.read_text(encoding="utf-8")
    if read_current_count(verify) != new_count:
        raise SystemExit(
            f"FATAL: post-write count verification failed "
            f"(expected {new_count}, got {read_current_count(verify)})"
        )
    if read_warning_remaining(verify) != new_remaining:
        raise SystemExit(
            f"FATAL: post-write warning verification failed "
            f"(expected {new_remaining}, got {read_warning_remaining(verify)})"
        )
    return new_count, new_remaining


def commit_batch(route: int, parsed: list[Trainer],
                 double_battles: set[tuple[int, int]]) -> int:
    print("# COMMIT MODE — performing writes")
    print(f"# Route: R{route}, batch size: {len(parsed)} trainers, "
          f"{sum(len(t.mons) for t in parsed)} Pokémon\n")

    assert_clean_tree()
    print("[1/9] clean-tree check: PASS")

    opponents_text = OPPONENTS_H.read_text(encoding="utf-8")
    current_count = read_current_count(opponents_text)
    max_count = read_max_count(opponents_text)
    print(f"[2/9] read opponents.h: count={current_count}, MAX={max_count}")

    if current_count + len(parsed) > max_count:
        remaining = max_count - current_count
        raise SystemExit(
            f"FATAL: ceiling exceeded. {len(parsed)} trainers requested, "
            f"only {remaining} slots remain ({current_count}/{max_count}). "
            f"Expand flag space before continuing."
        )
    print(f"[3/9] ceiling check: PASS "
          f"({current_count} + {len(parsed)} = {current_count + len(parsed)} ≤ {max_count})")

    pre_party_md5 = md5_file(TRAINERS_PARTY)
    pre_opp_md5 = md5_file(OPPONENTS_H)
    print(f"[4/9] pre-write MD5:")
    print(f"      trainers.party  {pre_party_md5}")
    print(f"      opponents.h     {pre_opp_md5}")

    append_trainer_blocks(parsed, double_battles)
    print(f"[5/9] appended {len(parsed)} trainer blocks to trainers.party")

    new_count, new_remaining = update_opponents_h(parsed, current_count, max_count)
    print(f"[6/9] updated opponents.h: "
          f"count {current_count}→{new_count}, warning {new_remaining} slots remaining")

    post_party_md5 = md5_file(TRAINERS_PARTY)
    post_opp_md5 = md5_file(OPPONENTS_H)
    print(f"[7/9] post-write MD5:")
    print(f"      trainers.party  {post_party_md5}")
    print(f"      opponents.h     {post_opp_md5}")

    ncpu = os.cpu_count() or 1
    print(f"[8/9] running make -j{ncpu} ...")
    build = subprocess.run(
        ["make", f"-j{ncpu}"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    if build.returncode != 0:
        print("[8/9] BUILD FAILED — last 30 lines of stderr:", file=sys.stderr)
        for line in build.stderr.splitlines()[-30:]:
            print(line, file=sys.stderr)
        print("\nWrites are NOT rolled back. Inspect, fix, and re-run as needed.",
              file=sys.stderr)
        return 1
    print("[8/9] build: PASS")

    rom_md5 = md5_file(REPO_ROOT / "pokeemerald.gba")
    names_csv = ", ".join(t.name.title() for t in parsed)
    n_mons = sum(len(t.mons) for t in parsed)
    print(f"\n[9/9] pokeemerald.gba MD5: {rom_md5}")
    print(f"\n# Suggested commit message (CEO confirms separately, no auto-commit):\n")
    print(f"R{route} batch port: {names_csv} "
          f"({len(parsed)} trainers, {n_mons} Pokémon) - via port_trainers.py")
    print()
    return 0


# ─── CLI ─────────────────────────────────────────────────────────────────────


def main() -> int:
    ap = argparse.ArgumentParser(description="Port Snow trainers from v17 spec.")
    ap.add_argument("--route", type=str, help="Port only this route (e.g. 2, 15, DI)")
    ap.add_argument("--all", action="store_true",
                    help="Port all routes from start-flag")
    ap.add_argument("--start-flag", type=int, default=None,
                    help="Override flag start (default: current TRAINERS_COUNT_EMERALD)")
    ap.add_argument("--dry-run", action="store_true", default=True,
                    help="Print only, no writes (default)")
    ap.add_argument("--commit", action="store_true",
                    help="Required to actually modify files")
    ap.add_argument("--dump-parsed", action="store_true",
                    help="Dump parsed trainer dict and exit (parser-only mode)")
    args = ap.parse_args()

    if not SPEC_PATH.exists():
        print(f"FATAL: spec not found at {SPEC_PATH}", file=sys.stderr)
        return 2
    if args.route is None and not args.all:
        print("FATAL: pass --route N or --all", file=sys.stderr)
        return 2

    # Convert route string to internal int (DI → DI_ROUTE_NUM)
    route_num: int | None = None
    if args.route is not None:
        if args.route.upper() == "DI":
            route_num = DI_ROUTE_NUM
        elif args.route.upper() == "VR":
            route_num = VR_ROUTE_NUM
        else:
            try:
                route_num = int(args.route)
            except ValueError:
                print(f"FATAL: invalid route '{args.route}' — use a number or 'DI'", file=sys.stderr)
                return 2

    spec_text = SPEC_PATH.read_text(encoding="utf-8")
    trainers = parse_spec(spec_text, route_filter=route_num)
    assert_spec_compliance(trainers)
    double_battles = parse_double_battles(spec_text)

    if args.dump_parsed:
        for t in trainers:
            doubled = (t.route, t.index) in double_battles
            print(f"=== R{t.route}-{t.index} {t.klass} {t.name} "
                  f"(emit_class={t.emit_class}, gender={t.gender}, "
                  f"double={doubled}, constant={t.constant}) ===")
            for k, mon in enumerate(t.mons, 1):
                print(f"  [{k}] {mon.species} Lv{mon.level} {mon.nature} "
                      f"{mon.ability} item={mon.item} moves={mon.moves}")
        print(f"\nParsed {len(trainers)} trainers, "
              f"{sum(len(t.mons) for t in trainers)} Pokémon.")
        return 0

    route_label = "DI" if route_num == DI_ROUTE_NUM else f"R{route_num}" if route_num else "all"
    party_text = TRAINERS_PARTY.read_text(encoding="utf-8")
    shipped_blocks = extract_shipped_blocks(route_num, party_text) if route_num else {}
    route_already_shipped = bool(shipped_blocks)

    if args.commit:
        if route_already_shipped:
            print(
                f"FATAL: --commit refused — {route_label} already shipped "
                f"({len(shipped_blocks)} blocks present in trainers.party). "
                f"Re-emitting would double-insert.",
                file=sys.stderr,
            )
            return 2
        return commit_batch(route_num, trainers, double_battles)

    # Dry-run mode. Auto-detect: shipped route → round-trip; new route → preview.
    if route_already_shipped:
        return round_trip_validate(route_num, trainers, double_battles, party_text)

    # Preview emit for a not-yet-shipped route.
    print(f"# Preview emit for {route_label} ({len(trainers)} trainers, "
          f"{sum(len(t.mons) for t in trainers)} Pokémon)\n")
    for t in trainers:
        print(emit_trainer(t, double_battles))
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main())
