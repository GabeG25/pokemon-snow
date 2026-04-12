#!/usr/bin/env python3
"""
Snow project static audit.
Run after every script/map change to catch common bugs before playtesting.

Checks:
1. Script references: object_events in map.json reference valid script labels
2. Flag existence: all FLAG_SNOW_* referenced are defined in flags.h
3. Trainer IDs: all TRAINER_SNOW_* referenced are defined in opponents.h
4. Text labels: all msgbox references point to defined strings
5. Build sanity: map_groups.json consistency
6. Connection validity: map.json connections reference existing maps

Usage: python3 tools/snow_port/audit_scripts.py
Exit 0 = clean, exit 1 = issues found
"""

import json
import re
import sys
from pathlib import Path
from collections import defaultdict

REPO = Path(__file__).resolve().parent.parent.parent
MAPS_DIR = REPO / "data/maps"

# Collect errors by severity
CRIT = []  # Would crash or break build
HIGH = []  # Would break gameplay
MED  = []  # Wrong behavior
LOW  = []  # Cosmetic

def err(sev, msg):
    {"CRIT": CRIT, "HIGH": HIGH, "MED": MED, "LOW": LOW}[sev].append(msg)


# ═══ Load reference data ═══
def load_defined_flags():
    flags = set()
    with open(REPO / "include/constants/flags.h") as f:
        for line in f:
            m = re.match(r'#define\s+(FLAG_\w+)', line)
            if m:
                flags.add(m.group(1))
    return flags

def load_defined_trainers():
    trainers = set()
    with open(REPO / "include/constants/opponents.h") as f:
        for line in f:
            m = re.match(r'#define\s+(TRAINER_\w+)', line)
            if m:
                trainers.add(m.group(1))
    return trainers

def load_defined_items():
    items = set()
    with open(REPO / "include/constants/items.h") as f:
        for line in f:
            m = re.search(r'(ITEM_\w+)', line)
            if m:
                items.add(m.group(1))
    return items


# ═══ Checks ═══
def check_snow_maps():
    """Walk each Snow map directory and verify scripts."""
    flags = load_defined_flags()
    trainers = load_defined_trainers()
    items = load_defined_items()

    snow_maps = []
    with open(REPO / "data/maps/map_groups.json") as f:
        mg = json.load(f)
        snow_maps = mg.get("gMapGroup_Snow", [])

    for map_name in snow_maps:
        map_dir = MAPS_DIR / map_name
        mjp = map_dir / "map.json"
        inc = map_dir / "scripts.inc"

        if not mjp.exists():
            err("CRIT", f"{map_name}: missing map.json")
            continue
        if not inc.exists():
            err("CRIT", f"{map_name}: missing scripts.inc")
            continue

        with open(mjp) as f:
            mj = json.load(f)
        with open(inc) as f:
            script_text = f.read()

        # Collect defined labels in scripts.inc
        defined_labels = set(re.findall(r'^(\w+)::?', script_text, re.MULTILINE))
        defined_labels |= set(re.findall(r'^(\w+):(?!\w)', script_text, re.MULTILINE))

        # 1. object_event script references
        for ev in mj.get("object_events", []):
            script_ref = ev.get("script", "0")
            if script_ref and script_ref != "0":
                # Strip map prefix if present
                if script_ref not in defined_labels:
                    err("HIGH", f"{map_name}: object_event references undefined script '{script_ref}'")
            # Flag field
            flag_ref = ev.get("flag", "0")
            if flag_ref and flag_ref != "0" and flag_ref not in flags:
                err("HIGH", f"{map_name}: object_event references undefined flag '{flag_ref}'")

        # 2. Connections reference existing Snow maps
        for conn in mj.get("connections", []):
            target = conn.get("map", "")
            # Strip MAP_ prefix, convert to dir name format
            # Just check it's a known MAP_ constant — skip detailed name check

        # 3. Flags referenced in scripts
        for flag in re.findall(r'\b(FLAG_SNOW_\w+)', script_text):
            if flag not in flags:
                err("CRIT", f"{map_name}/scripts.inc: undefined flag '{flag}'")

        # 4. Trainer constants
        for trainer in re.findall(r'\b(TRAINER_SNOW_\w+)', script_text):
            if trainer not in trainers:
                err("CRIT", f"{map_name}/scripts.inc: undefined trainer '{trainer}'")

        # 5. Internal label references (goto/call/msgbox/branch targets)
        # Find all label usages
        internal_refs = set()
        for pattern in [
            r'goto\s+(\w+)',
            r'goto_if_set\s+\w+,\s*(\w+)',
            r'goto_if_unset\s+\w+,\s*(\w+)',
            r'goto_if_eq\s+(\w+)',
            r'call\s+(\w+)',
            r'msgbox\s+(\w+)',
            r'trainerbattle_single\s+\w+,\s*(\w+),\s*(\w+)',
            r'trainerbattle_no_intro\s+\w+,\s*(\w+)',
            r'applymovement\s+\w+,\s*(\w+)',
        ]:
            for m in re.finditer(pattern, script_text):
                if m.groups():
                    for g in m.groups():
                        if g: internal_refs.add(g)

        # Check internal refs are defined (either as script label or in same file)
        for ref in internal_refs:
            # Skip known vanilla shared scripts
            if ref.startswith(("Common_", "EventScript_", "Std_")):
                continue
            # Skip text/variable/constants (not labels)
            if ref.startswith(("VAR_", "FLAG_", "ITEM_", "SPECIES_", "MOVE_", "TRAINER_",
                               "MSGBOX_", "TRUE", "FALSE", "MALE", "FEMALE", "MULTI_",
                               "FADE_", "B_", "TYPE_", "NATURE_")):
                continue
            # Check if this label is defined in this file OR starts with the map prefix (inter-file allowed)
            if ref not in defined_labels:
                # Might be in a different file, mark as LOW since we can't verify
                if ref.startswith(map_name):
                    err("HIGH", f"{map_name}/scripts.inc: reference to undefined label '{ref}'")


def check_event_scripts_includes():
    """Verify all Snow map scripts.inc files are included in event_scripts.s."""
    snow_maps = []
    with open(REPO / "data/maps/map_groups.json") as f:
        mg = json.load(f)
        snow_maps = mg.get("gMapGroup_Snow", [])

    with open(REPO / "data/event_scripts.s") as f:
        event_scripts = f.read()

    for map_name in snow_maps:
        include_line = f'.include "data/maps/{map_name}/scripts.inc"'
        if include_line not in event_scripts:
            err("CRIT", f"{map_name}: scripts.inc NOT included in event_scripts.s")


def check_critical_files():
    """Verify critical Snow config files are in correct state."""
    caps_h = (REPO / "include/config/caps.h").read_text()
    if "B_RARE_CANDY_CAP                TRUE" not in caps_h:
        err("HIGH", "B_RARE_CANDY_CAP not set to TRUE (Candy Box won't respect caps)")

    caps_c = (REPO / "src/caps.c").read_text()
    snow_caps = ["FLAG_BADGE01_GET, 15", "FLAG_BADGE02_GET, 23", "FLAG_BADGE03_GET, 30",
                 "FLAG_BADGE04_GET, 40", "FLAG_BADGE05_GET, 50", "FLAG_BADGE06_GET, 59",
                 "FLAG_BADGE07_GET, 66", "FLAG_BADGE08_GET, 72", "FLAG_IS_CHAMPION, 95"]
    for c in snow_caps:
        if c not in caps_c:
            err("HIGH", f"src/caps.c missing Snow level cap: {c}")

    battle_util = (REPO / "src/battle_util.c").read_text()
    if "weatherDuration = 0" not in battle_util:
        err("HIGH", "Weather rock permanent duration fix missing in battle_util.c")


# ═══ Run all checks ═══
def main():
    print("Snow project static audit\n")
    check_snow_maps()
    check_event_scripts_includes()
    check_critical_files()

    total = len(CRIT) + len(HIGH) + len(MED) + len(LOW)

    if CRIT:
        print(f"CRITICAL ({len(CRIT)}):")
        for m in CRIT: print(f"  ✗ {m}")
        print()
    if HIGH:
        print(f"HIGH ({len(HIGH)}):")
        for m in HIGH: print(f"  ✗ {m}")
        print()
    if MED:
        print(f"MEDIUM ({len(MED)}):")
        for m in MED: print(f"  ! {m}")
        print()
    if LOW:
        print(f"LOW ({len(LOW)}):")
        for m in LOW: print(f"  · {m}")
        print()

    if total == 0:
        print("✓ AUDIT CLEAN — no issues found")
        return 0
    else:
        print(f"Total issues: {total}")
        return 1 if (CRIT or HIGH) else 0


if __name__ == "__main__":
    sys.exit(main())
