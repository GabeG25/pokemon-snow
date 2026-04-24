# Project Architecture Reference

## Directory Structure

```
pokeemerald-expansion/
├── asm/macros/
│   ├── event.inc               # ALL script command macros (source of truth)
│   └── movement.inc            # ALL movement action macros
├── data/
│   ├── maps/
│   │   ├── map_groups.json     # Every map must be registered here
│   │   └── <MapName>/
│   │       ├── map.json        # Map events, header, connections
│   │       └── scripts.pory    # Poryscript event scripts
│   │           (or scripts.inc)  # Raw assembly scripts
│   ├── layouts/
│   │   ├── layouts.json        # Layout definitions
│   │   └── <LayoutName>/
│   │       ├── map.bin         # Metatile grid (BINARY — never edit directly)
│   │       └── border.bin      # Border tiles (BINARY — never edit directly)
│   ├── scripts/
│   │   ├── event_scripts.s     # Global event scripts (auto-appended for new maps)
│   │   ├── field_move_scripts.inc
│   │   └── movement.inc        # Common movements (reusable across maps)
│   └── event_scripts.s         # Master include file for all script files
├── src/data/
│   ├── wild_encounters.json    # Wild Pokémon encounter tables
│   ├── heal_locations.json     # Heal/respawn locations
│   ├── trainers/               # Trainer party data
│   ├── object_events/
│   │   ├── object_event_graphics_info_pointers.h
│   │   ├── object_event_graphics_info.h
│   │   ├── object_event_pic_tables.h
│   │   └── object_event_graphics.h
│   └── tilesets/
│       ├── headers.h           # Tileset definitions
│       ├── graphics.h          # Tileset graphics paths
│       └── metatiles.h         # Metatile data paths
├── include/constants/
│   ├── flags.h                 # FLAG_* — event flags (max depends on project)
│   ├── vars.h                  # VAR_* — script variables
│   ├── items.h                 # ITEM_* — all items
│   ├── species.h               # SPECIES_* — all Pokémon species
│   ├── moves.h                 # MOVE_* — all moves
│   ├── songs.h                 # MUS_*/SE_* — music and sound effects
│   ├── event_objects.h         # OBJ_EVENT_GFX_* — sprite graphics IDs
│   ├── event_object_movement.h # MOVEMENT_TYPE_* — NPC movement types
│   ├── trainer_types.h         # TRAINER_TYPE_* — trainer type constants
│   ├── weather.h               # WEATHER_* — weather types
│   ├── map_types.h             # MAP_TYPE_*, MAP_BATTLE_SCENE_*
│   ├── event_bg.h              # BG_EVENT_PLAYER_FACING_* — sign directions
│   └── metatile_labels.h       # METATILE_* — named metatile IDs
├── tools/poryscript/           # Poryscript compiler
│   ├── poryscript              # The executable
│   ├── command_config.json     # Command definitions for Poryscript
│   └── font_config.json        # Font width config for text auto-formatting
└── Makefile                    # Build system
```

## How Files Relate

### When a map loads in-game:
1. Engine reads map.json for header data (weather, music, type, etc.)
2. Engine loads layout (map.bin + border.bin) for visual tiles
3. Engine loads tileset graphics for rendering
4. Engine places object events from map.json (NPCs, items, trainers)
5. Engine places warp/trigger/sign events from map.json
6. Engine runs map scripts (ON_TRANSITION, ON_LOAD, etc.) from scripts.pory
7. Player gains control; ON_FRAME_TABLE scripts checked each frame

### When Poryscript compiles:
1. `make` triggers: `.pory` → poryscript compiler → `.inc`
2. The `.inc` output is assembled into bytecode in the ROM
3. If `.pory` exists, `.inc` is auto-generated (do NOT manually edit the .inc)
4. If only `.inc` exists, it's used directly (legacy maps)

### When you add a new map:
1. Create folder `data/maps/NewMapName/`
2. Create `map.json` with complete schema
3. Create `scripts.pory` with at least empty mapscripts
4. Add map to appropriate group in `data/maps/map_groups.json`
5. Create or reference a layout in `data/layouts/layouts.json`
6. Layout needs `map.bin` and `border.bin` (created by Porymap or from template)

## Constant Verification Commands

Before using any constant in code, verify it exists:

```bash
# Check if a flag exists
grep -r "FLAG_MY_FLAG" include/constants/flags.h

# Check if a species exists
grep -r "SPECIES_SWINUB" include/constants/species.h

# Check if an item exists
grep -r "ITEM_POTION" include/constants/items.h

# Check if a trainer exists
grep -r "TRAINER_ROUTE1_HIKER" src/data/trainers/

# Check if a sprite graphics ID exists
grep -r "OBJ_EVENT_GFX_WOMAN_1" include/constants/event_objects.h

# Check if a movement type exists
grep -r "MOVEMENT_TYPE_FACE_DOWN" include/constants/event_object_movement.h

# Check if a music constant exists
grep -r "MUS_LITTLEROOT_TOWN" include/constants/songs.h
```

## Build Commands

```bash
make -j$(nproc)          # Full parallel build
make -j$(nproc) 2>&1 | head -50   # Build and show first errors
```

## Porymap-Managed vs Claude Code-Editable Files

| File | Porymap? | Claude Code? | Notes |
|------|----------|-------------|-------|
| map.json | Read/Write | Edit carefully | Both share this file |
| scripts.pory | Read (labels only) | Primary editor | Porymap reads for dropdown |
| map.bin | Read/Write | NEVER edit | Binary metatile data |
| border.bin | Read/Write | NEVER edit | Binary border data |
| layouts.json | Read/Write | Can edit | Layout registry |
| map_groups.json | Read/Write | Can edit | Map registry |
| wild_encounters.json | Not used | Can edit | Wild Pokémon data |
| Tileset images/palettes | Read/Write | NEVER edit | Binary graphics |
| include/constants/*.h | Not used | Can edit | Add new constants |
| src/data/trainers/ | Not used | Can edit | Trainer data |
