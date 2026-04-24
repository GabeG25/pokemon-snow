# map.json Format Specification

Porymap reads and writes this file. Corruption prevents Porymap from opening the map
and may cause build failures. Every field type documented here is verified from Porymap's
official documentation and source code.

## Top-Level Fields

```json
{
    "id": "MAP_DAWNFLAKE_TOWN",
    "name": "DawnflakeTown",
    "layout": "LAYOUT_DAWNFLAKE_TOWN",
    "music": "MUS_LITTLEROOT_TOWN",
    "region_map_section": "MAPSEC_DAWNFLAKE_TOWN",
    "requires_flash": false,
    "weather": "WEATHER_NONE",
    "map_type": "MAP_TYPE_TOWN",
    "allow_cycling": true,
    "allow_escaping": false,
    "allow_running": true,
    "show_map_name": true,
    "floor_number": 0,
    "battle_scene": "MAP_BATTLE_SCENE_NORMAL",
    "connections": [],
    "object_events": [],
    "warp_events": [],
    "coord_events": [],
    "bg_events": []
}
```

### Field Type Rules

| Field | JSON Type | Valid Values |
|-------|-----------|-------------|
| `id` | string | `MAP_*` constant, must be registered in map_groups.json |
| `name` | string | PascalCase, no spaces/underscores |
| `layout` | string | `LAYOUT_*` constant, must exist in layouts.json |
| `music` | string | `MUS_*` or `SE_*` from include/constants/songs.h |
| `region_map_section` | string | `MAPSEC_*` constant |
| `requires_flash` | boolean | `true` or `false` (JSON boolean) |
| `weather` | string | `WEATHER_*` constant |
| `map_type` | string | `MAP_TYPE_*` constant |
| `allow_cycling` | boolean | JSON boolean |
| `allow_escaping` | boolean | JSON boolean |
| `allow_running` | boolean | JSON boolean |
| `show_map_name` | boolean | JSON boolean |
| `floor_number` | integer | 0 = no floor number shown |
| `battle_scene` | string | `MAP_BATTLE_SCENE_*` constant |

## Object Events

```json
{
    "graphics_id": "OBJ_EVENT_GFX_WOMAN_1",
    "local_id": 1,
    "x": 10,
    "y": 8,
    "elevation": 3,
    "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
    "movement_range_x": 0,
    "movement_range_y": 0,
    "trainer_type": "TRAINER_TYPE_NONE",
    "trainer_sight_or_berry_tree_id": "0",
    "script": "MapName_EventScript_Npc1",
    "flag": "0"
}
```

| Field | Type | Notes |
|-------|------|-------|
| `graphics_id` | **string** | `OBJ_EVENT_GFX_*` constant. Must exist in project. |
| `local_id` | **integer** | Sequential from 1, no gaps, no duplicates within map. |
| `x`, `y` | **integer** | Metatile coords, 0-indexed from top-left. |
| `elevation` | **integer** | 3=ground, 0=all elevations. Range 0-15. |
| `movement_type` | **string** | `MOVEMENT_TYPE_*` constant. |
| `movement_range_x` | **integer** | Horizontal walk radius. 0=stationary. |
| `movement_range_y` | **integer** | Vertical walk radius. 0=stationary. |
| `trainer_type` | **string** | `TRAINER_TYPE_NONE` or `TRAINER_TYPE_NORMAL`. |
| `trainer_sight_or_berry_tree_id` | **STRING** | Sight radius as STRING. `"0"` for non-trainers. |
| `script` | **string** | Script label. Must exist in scripts file. `""` for none. |
| `flag` | **STRING** | `"0"` = always visible. `"FLAG_*"` = hidden when flag is set. |

**TYPE TRAPS:** `trainer_sight_or_berry_tree_id`, `flag` are STRINGS, not integers.
`local_id`, `x`, `y`, `elevation`, `movement_range_*` are INTEGERS.

### Trainer NPC Checklist
All four must be correct or the trainer breaks:
1. `trainer_type`: `"TRAINER_TYPE_NORMAL"` (not NONE)
2. `trainer_sight_or_berry_tree_id`: `"4"` (or desired sight radius, as STRING)
3. `script`: Points to script with `trainerbattle_*` command
4. TRAINER_* constant must exist in trainer data files

### Item Ball Setup
```json
{
    "graphics_id": "OBJ_EVENT_GFX_ITEM_BALL",
    "local_id": 5,
    "elevation": 3,
    "movement_type": "MOVEMENT_TYPE_NONE",
    "movement_range_x": 0, "movement_range_y": 0,
    "trainer_type": "TRAINER_TYPE_NONE",
    "trainer_sight_or_berry_tree_id": "0",
    "script": "MapName_EventScript_ItemPotion",
    "flag": "FLAG_ITEM_MAPNAME_POTION"
}
```

## Warp Events

```json
{
    "x": 7, "y": 0,
    "elevation": 0,
    "dest_map": "MAP_DESTINATION",
    "dest_warp_id": 0
}
```

| Field | Type | Notes |
|-------|------|-------|
| `x`, `y` | **integer** | Position of warp tile |
| `elevation` | **integer** | Usually 0 (all elevations) |
| `dest_map` | **string** | `MAP_*` constant of destination |
| `dest_warp_id` | **integer** | **0-INDEXED** position in destination's warp_events array |

### Bidirectional Warp Setup

If MapA warp index 2 → MapB:
```json
// MapA warp_events[2]:
{"x":10, "y":5, "elevation":0, "dest_map":"MAP_B", "dest_warp_id": 0}

// MapB warp_events[0]:
{"x":4, "y":8, "elevation":0, "dest_map":"MAP_A", "dest_warp_id": 2}
```

## Coord Events (Triggers)

```json
{
    "type": "trigger",
    "x": 15, "y": 20,
    "elevation": 0,
    "var": "VAR_ROUTE1_STATE",
    "var_value": "1",
    "script": "Route1_EventScript_Cutscene"
}
```

| Field | Type | Notes |
|-------|------|-------|
| `type` | **string** | `"trigger"` or `"weather"` |
| `var` | **string** | `VAR_*` constant |
| `var_value` | **STRING** | Value var must equal. **STRING, not integer.** |
| `script` | **string** | Script label to execute |

Weather trigger:
```json
{"type":"weather", "x":0, "y":25, "elevation":0, "weather":"WEATHER_SNOW"}
```

## BG Events (Signs, Hidden Items, Secret Bases)

### Sign
```json
{
    "type": "sign",
    "x": 8, "y": 6, "elevation": 0,
    "player_facing_dir": "BG_EVENT_PLAYER_FACING_ANY",
    "script": "MapName_EventScript_Sign1"
}
```

### Hidden Item
```json
{
    "type": "hidden_item",
    "x": 12, "y": 4, "elevation": 0,
    "item": "ITEM_POTION",
    "flag": "FLAG_HIDDEN_ITEM_MAPNAME_1"
}
```

Hidden items MUST have a valid FLAG_* — unlike object events, `"0"` won't work properly.

### Secret Base
```json
{
    "type": "secret_base",
    "x": 3, "y": 7, "elevation": 0,
    "secret_base_id": "SECRET_BASE_RED_CAVE4_1"
}
```

## Connections

```json
"connections": [
    {"direction": "south", "map": "MAP_ROUTE2", "offset": 0},
    {"direction": "east", "map": "MAP_ROUTE3", "offset": -2}
]
```

Valid directions: `"north"`, `"south"`, `"east"`, `"west"`, `"dive"`, `"emerge"`

Connections MUST be mirrored. If A→B has offset N, B→A has offset -N (for reversed direction).
