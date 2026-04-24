# End-to-End Workflows

Step-by-step procedures for common tasks. Follow EXACTLY — skipping steps causes bugs.

## Workflow 1: Add an NPC to an Existing Map

### Step 1: Read current map state
```bash
cat data/maps/MapName/map.json
cat data/maps/MapName/scripts.pory
```

### Step 2: Determine next local_id
Count existing object_events. Next ID = highest + 1. Must be sequential.

### Step 3: Verify the sprite exists
```bash
grep -r "OBJ_EVENT_GFX_WOMAN_1" include/constants/event_objects.h
```

### Step 4: Write the script in scripts.pory
```
script MapName_EventScript_NewNpc {
    lock
    faceplayer
    msgbox("Your dialog here.")
    release
    end
}
```

### Step 5: Add object event to map.json
Add to the `object_events` array with correct local_id, coordinates, and script reference.
Verify the script label EXACTLY matches what you wrote in Step 4.

### Step 6: Validate and build
```bash
python3 -c "import json; json.load(open('data/maps/MapName/map.json'))"
make -j$(nproc)
```

---

## Workflow 2: Add a Trainer to an Existing Map

### Step 1: Read current state
```bash
cat data/maps/MapName/map.json
cat data/maps/MapName/scripts.pory
cat src/data/trainers/opponents.h | tail -20     # find last trainer constant
```

### Step 2: Add trainer constant to opponents.h
Add `TRAINER_MAPNAME_CLASS` to the opponents.h enum/defines.

### Step 3: Add trainer data to trainers.party
Follow the format in `references/trainers-party-format.md` exactly.
Verify all species and moves exist in the project.

### Step 4: Write trainer script in scripts.pory
```
script MapName_EventScript_TrainerHiker {
    trainerbattle_single(TRAINER_ROUTE1_HIKER,
        "You look like a strong trainer!",
        "Wow, you beat me!")
    msgbox("That was a great battle.", MSGBOX_AUTOCLOSE)
    end
}
```

### Step 5: Add trainer object event to map.json
```json
{
    "graphics_id": "OBJ_EVENT_GFX_HIKER",
    "local_id": NEXT_ID,
    "x": X, "y": Y,
    "elevation": 3,
    "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
    "movement_range_x": 0, "movement_range_y": 0,
    "trainer_type": "TRAINER_TYPE_NORMAL",
    "trainer_sight_or_berry_tree_id": "4",
    "script": "MapName_EventScript_TrainerHiker",
    "flag": "0"
}
```

Checklist:
- [ ] `trainer_type` is `"TRAINER_TYPE_NORMAL"` (STRING, not NONE)
- [ ] `trainer_sight_or_berry_tree_id` is a STRING with value >= "1"
- [ ] `script` exactly matches the script label
- [ ] `flag` is `"0"` (trainers use auto-managed flags via TRAINER_FLAGS_START)

### Step 6: Build and test
```bash
make -j$(nproc)
```

---

## Workflow 3: Create Warps Between Two Maps

### Step 1: Read BOTH map.json files
```bash
cat data/maps/MapA/map.json | python3 -c "import json,sys; d=json.load(sys.stdin); print(f'MapA has {len(d[\"warp_events\"])} warps')"
cat data/maps/MapB/map.json | python3 -c "import json,sys; d=json.load(sys.stdin); print(f'MapB has {len(d[\"warp_events\"])} warps')"
```

### Step 2: Determine warp indices
MapA's new warp index = current warp count (0-indexed)
MapB's new warp index = current warp count (0-indexed)

### Step 3: Add warp to MapA
```json
{"x": 10, "y": 5, "elevation": 0, "dest_map": "MAP_B", "dest_warp_id": NEW_INDEX_IN_B}
```

### Step 4: Add return warp to MapB
```json
{"x": 4, "y": 8, "elevation": 0, "dest_map": "MAP_A", "dest_warp_id": NEW_INDEX_IN_A}
```

### Step 5: Cross-verify
- MapA warp's `dest_warp_id` == position of return warp in MapB's array
- MapB warp's `dest_warp_id` == position of source warp in MapA's array

### Step 6: Validate both
```bash
python3 -c "import json; json.load(open('data/maps/MapA/map.json'))"
python3 -c "import json; json.load(open('data/maps/MapB/map.json'))"
make -j$(nproc)
```

---

## Workflow 4: Add Item Ball Pickup

### Step 1: Allocate a flag
Check current flag usage. Pick an unused FLAG_ITEM_* flag.
```bash
grep -c "FLAG_ITEM_" include/constants/flags.h
```

### Step 2: Add flag to flags.h (if new)
```c
#define FLAG_ITEM_MAPNAME_POTION (FLAG_ITEM_ROUTE_101_POTION + N)
```
Or use an available slot.

### Step 3: Write pickup script
```
script MapName_EventScript_ItemPotion {
    finditem(ITEM_POTION, 1)
    end
}
```

### Step 4: Add object event to map.json
```json
{
    "graphics_id": "OBJ_EVENT_GFX_ITEM_BALL",
    "local_id": NEXT_ID,
    "x": X, "y": Y,
    "elevation": 3,
    "movement_type": "MOVEMENT_TYPE_NONE",
    "movement_range_x": 0, "movement_range_y": 0,
    "trainer_type": "TRAINER_TYPE_NONE",
    "trainer_sight_or_berry_tree_id": "0",
    "script": "MapName_EventScript_ItemPotion",
    "flag": "FLAG_ITEM_MAPNAME_POTION"
}
```

The flag makes the ball disappear after pickup.

---

## Workflow 5: Add a Cutscene Trigger

### Step 1: Choose a variable
Pick a VAR_* for this map's story state. Verify it's not already used elsewhere.
```bash
grep -r "VAR_ROUTE1_STATE" data/maps/ data/scripts/
```

### Step 2: Write the cutscene script
```
script MapName_EventScript_Cutscene {
    lockall
    // Cutscene actions here
    applymovement(LOCALID_RIVAL, MapName_Movement_RivalApproach)
    waitmovement(0)
    msgbox("Hey! Wait up!")
    // ... more actions ...
    setvar(VAR_ROUTE1_STATE, 1)    // CRITICAL: prevent re-trigger
    releaseall
    end
}

movement MapName_Movement_RivalApproach {
    walk_down * 3
    face_player
}
```

### Step 3: Add coord_event (trigger) to map.json
```json
{
    "type": "trigger",
    "x": 15, "y": 20,
    "elevation": 0,
    "var": "VAR_ROUTE1_STATE",
    "var_value": "0",
    "script": "MapName_EventScript_Cutscene"
}
```

### Step 4: Verify
- Script ends with `releaseall` + `end` (used `lockall`)
- Script changes var to a value != var_value (prevents re-trigger)
- var_value is a STRING in JSON

---

## Workflow 6: Add Map Connection (Adjacent Outdoor Maps)

### Step 1: Read both map.json connection arrays
```bash
cat data/maps/MapA/map.json | python3 -c "import json,sys; print(json.dumps(json.load(sys.stdin)['connections'], indent=2))"
cat data/maps/MapB/map.json | python3 -c "import json,sys; print(json.dumps(json.load(sys.stdin)['connections'], indent=2))"
```

### Step 2: Add connection to MapA
```json
{"direction": "south", "map": "MAP_B", "offset": 0}
```

### Step 3: Add mirror connection to MapB
```json
{"direction": "north", "map": "MAP_A", "offset": 0}
```

If MapA's offset is N, MapB's offset is -N.

### Step 4: Build and verify visual alignment in-game
```bash
make -j$(nproc)
```

---

## Workflow 7: Add Heal Location (Pokémon Center)

### Step 1: Read heal_locations.json
```bash
cat src/data/heal_locations.json
```

### Step 2: Add heal location constant
Add to the heal locations header (check project for exact location):
```c
#define HEAL_LOCATION_DAWNFLAKE_TOWN 1
```

### Step 3: Add entry to heal_locations.json
```json
{
    "id": "HEAL_LOCATION_DAWNFLAKE_TOWN",
    "map": "MAP_DAWNFLAKE_TOWN",
    "x": 10,
    "y": 5
}
```

### Step 4: Add heal location event in Porymap
The heal location event in map.json tells the game where the player respawns.
This is placed at the Pokémon Center's outdoor entrance.

### Step 5: Set respawn in Pokémon Center script
In the Pokémon Center nurse's script (or heal machine interaction):
```
setrespawn(HEAL_LOCATION_DAWNFLAKE_TOWN)
```
