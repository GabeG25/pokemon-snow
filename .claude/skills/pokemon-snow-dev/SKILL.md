---
name: pokemon-snow-dev
description: >
  Expert-level pokeemerald-expansion ROM hack development guide for Pokémon Snow. Covers
  ALL aspects: Porymap editing, Poryscript/raw assembly scripting, map.json format, trainer
  battles, NPC events, warps, triggers, wild encounters, map connections, movements, item
  events. Trigger on: 'Pokémon Snow', 'pokemon snow', 'porymap', 'poryscript', 'map.json',
  'scripts.pory', 'scripts.inc', 'pokeemerald', 'rom hack', 'romhack', map events, NPC
  scripting, warp setup, trainer battles, wild encounters, metatiles, event flags, movement
  scripts, cutscenes, or ANY GBA Pokémon ROM hack task. Prevents bugs by requiring file
  reads before writes, constant verification, and format confirmation. NEVER assume — READ,
  VERIFY, then WRITE.
---

# Pokémon Snow / pokeemerald-expansion Development Skill

## ABSOLUTE RULES — These override everything else

1. **NEVER assume. ALWAYS verify.** Before editing any file, read it first. Before using
   any constant (FLAG_*, VAR_*, SPECIES_*, ITEM_*, TRAINER_*, OBJ_EVENT_GFX_*), grep the
   project to confirm it exists. Before referencing a script label, confirm it exists in
   the target file.

2. **NEVER rewrite entire files.** Make surgical, targeted edits. Read the file, identify
   the exact section to change, modify only that section.

3. **NEVER guess at JSON field types.** Consult `references/map-json-format.md` before
   editing any map.json. Getting string vs integer wrong corrupts the map.

4. **ALWAYS build-test after changes.** Run `make -j$(nproc)` after editing. If it fails,
   fix the error before making more changes.

5. **NEVER chain git commit behind make with `&&`.** Build first, verify success, then
   commit separately.

6. **If confidence is below 100%, stop and say so.** Tell the user exactly what you're
   unsure about and what you need to verify. This is always better than introducing a bug.

## How Porymap and Claude Code Interact

Porymap is a GUI map editor. Claude Code edits the same raw source files Porymap
reads/writes. Claude Code does NOT run Porymap — it edits the underlying files directly:

- `data/maps/<MapName>/map.json` — Map metadata, events, connections (Porymap reads/writes)
- `data/maps/<MapName>/scripts.pory` — Poryscript event scripts (Porymap reads for labels)
- `data/layouts/<Layout>/map.bin` — Binary metatile data (Porymap reads/writes; do NOT touch)
- `data/layouts/<Layout>/border.bin` — Binary border data (do NOT touch)

**Files Claude Code should edit:** map.json, scripts.pory/scripts.inc, wild_encounters.json,
trainer data files, header constant files.

**Files Claude Code must NEVER directly edit:** map.bin, border.bin, tileset graphics,
palette files. These are binary formats managed by Porymap's GUI.

## Project File Architecture

**Read the full architecture:** `references/project-architecture.md`

Key paths:
```
data/maps/                          Map data (one folder per map)
data/maps/map_groups.json           Map group registry (must register new maps here)
data/layouts/layouts.json           Layout registry
src/data/wild_encounters.json       Wild encounter tables
src/data/heal_locations.json        Heal/respawn points
src/data/trainers/                  Trainer definitions
include/constants/flags.h           FLAG_* defines
include/constants/vars.h            VAR_* defines
include/constants/items.h           ITEM_* defines
include/constants/event_objects.h   OBJ_EVENT_GFX_* defines
asm/macros/event.inc                All scripting macro definitions
asm/macros/movement.inc             All movement macro definitions
```

## Before Editing Any File — Mandatory Workflow

### Editing map.json
1. `cat data/maps/MapName/map.json` — read the entire current file
2. Consult `references/map-json-format.md` for the exact schema
3. Identify the specific array/field to modify
4. Make the minimal change needed
5. Validate: `python3 -c "import json; json.load(open('data/maps/MapName/map.json'))"`

### Editing scripts.pory
1. `cat data/maps/MapName/scripts.pory` — read current scripts
2. Consult `references/poryscript-complete.md` for syntax
3. Verify all constants you'll use: `grep -r "CONSTANT_NAME" include/`
4. Write the script following verified patterns
5. Build: `make -j$(nproc)` and check for errors

### Adding a New Map
1. Create the map folder under `data/maps/`
2. Create map.json with ALL required fields (see `references/map-json-format.md`)
3. Create scripts.pory with at minimum an empty mapscripts block
4. Register in `data/maps/map_groups.json`
5. Create or assign a layout in `data/layouts/layouts.json`
6. Build and test

### Setting Up Warps
1. Read BOTH source and destination map.json files
2. Count existing warps in both (0-indexed)
3. Add warp to source pointing to correct dest_warp_id
4. Add return warp to destination pointing back
5. Cross-verify: source.dest_warp_id == index of return warp in destination array
6. Cross-verify: return.dest_warp_id == index of source warp in source array

## Reference Files — Read BEFORE Editing

| Task | Reference File |
|------|---------------|
| Editing map.json (any event type) | `references/map-json-format.md` |
| Writing Poryscript (.pory) | `references/poryscript-complete.md` |
| Writing raw assembly (.inc) | `references/raw-assembly-reference.md` |
| Understanding project structure | `references/project-architecture.md` |
| Debugging / pre-commit checks | `references/verification-and-pitfalls.md` |
| Editing trainers.party | `references/trainers-party-format.md` |
| Editing wild_encounters.json | `references/wild-encounters.md` |
| Any multi-step task (add NPC, trainer, warp, item, cutscene, map connection) | `references/end-to-end-workflows.md` |

**Mandatory routing:** When given a task, identify which workflow from
`references/end-to-end-workflows.md` applies and follow it step by step.
If no workflow matches, build one by composing the relevant reference files.

## Pokémon Snow-Specific Conventions

- **Git identity:** GabeG25 / gabeg25@users.noreply.github.com
- **Starters:** Treecko/Torchic/Mudkip (locked, intentional, never revisit)
- **Trainerproc format:** Blank lines between blocks, omit empty fields, `- Move` format,
  UPPERCASE trainer names, no trailing newline, 5-space padding on count line
- **Flag ceiling:** 867/1024 used, 157 free. Check before allocating new flags.
- **Trainer class fallbacks:** Probe pattern (Boarder/Skier/Miner→Hiker) for missing classes
- **ROM is source of truth**, not markdown design docs
- **WSL clipboard strips blank lines** — use `printf` single-line for multi-line content
- **OneDrive Desktop path:** `/mnt/c/Users/gabeg/OneDrive/Desktop/`
- **317-species dex** for the Boralyss region
