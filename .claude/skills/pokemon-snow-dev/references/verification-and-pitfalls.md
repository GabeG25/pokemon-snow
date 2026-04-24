# Verification Checklist & Common Pitfalls

This is the pre-commit gate. Run every check before committing changes.

## Pre-Commit Verification Commands

```bash
# 1. Validate all edited map.json files
python3 -c "import json; json.load(open('data/maps/MAPNAME/map.json'))"

# 2. Build the ROM
make -j$(nproc)

# 3. Verify a constant exists before using it
grep -rn "CONSTANT_NAME" include/constants/

# 4. Verify a script label exists
grep -rn "ScriptLabelName" data/maps/ data/scripts/

# 5. Check local_id uniqueness in a map
python3 -c "
import json, sys
d = json.load(open(sys.argv[1]))
ids = [e['local_id'] for e in d.get('object_events', [])]
expected = list(range(1, len(ids)+1))
if ids != expected:
    print(f'ERROR: local_ids are {ids}, expected {expected}')
else:
    print('OK: local_ids are sequential')
" data/maps/MAPNAME/map.json

# 6. Verify warp bidirectionality
# For each warp in source, manually check destination has return warp
python3 -c "
import json, sys
src = json.load(open(sys.argv[1]))
for i, w in enumerate(src.get('warp_events', [])):
    print(f'Warp {i}: -> {w[\"dest_map\"]} warp {w[\"dest_warp_id\"]}')
" data/maps/MAPNAME/map.json

# 7. Verify all scripts referenced in map.json exist
python3 -c "
import json, re, sys, os
mj = json.load(open(sys.argv[1]))
mapdir = os.path.dirname(sys.argv[1])
scripts = set()
for f in ['scripts.pory', 'scripts.inc']:
    fp = os.path.join(mapdir, f)
    if os.path.exists(fp):
        scripts.update(re.findall(r'(?:script|text|movement)\s+(\w+)', open(fp).read()))
        scripts.update(re.findall(r'^(\w+)(?:::?)', open(fp).read(), re.MULTILINE))
for ev in mj.get('object_events', []) + mj.get('bg_events', []) + mj.get('coord_events', []):
    s = ev.get('script', '')
    if s and s not in scripts:
        # Check global scripts too
        print(f'WARNING: Script \"{s}\" not found in map scripts (may be global)')
" data/maps/MAPNAME/map.json
```

## Build-Breaking Bugs

### 1. Undefined Constants
**Symptom:** `make` fails with "undeclared identifier" or "undefined reference"
**Cause:** Using FLAG_*, VAR_*, ITEM_*, TRAINER_*, OBJ_EVENT_GFX_*, SPECIES_*, or
MOVEMENT_TYPE_* that doesn't exist in header files.
**Fix:** `grep -r "CONSTANT" include/` before using it. Add to header if new.

### 2. Invalid JSON
**Symptom:** Porymap won't open map. Build may fail with mapjson errors.
**Cause:** Trailing commas, missing commas, wrong types, unquoted strings.
**TYPE TRAP:** These fields are STRINGS (quotes required):
  - `trainer_sight_or_berry_tree_id`: `"4"` not `4`
  - `flag` on objects: `"0"` or `"FLAG_*"` not `0`
  - `var_value` on triggers: `"1"` not `1`
These fields are INTEGERS (no quotes):
  - `local_id`: `1` not `"1"`
  - `x`, `y`, `elevation`: integers
  - `dest_warp_id`: integer
  - `movement_range_x`, `movement_range_y`: integers

### 3. Poryscript Syntax Errors
**Symptom:** Build fails with poryscript compiler errors.
**Common:** Missing `}`, using `==` for assignment, `flag FLAG` instead of `flag(FLAG)`,
raw assembly commands outside `raw` blocks, `::` on Poryscript labels.

### 4. Missing step_end in Raw Movement
**Symptom:** Game freezes when movement triggers.
**Cause:** Raw assembly movement blocks must end with `step_end`.
Poryscript adds this automatically.

### 5. Missing $ in Raw Text
**Symptom:** Message shows garbage text after intended message.
**Cause:** Raw .string doesn't end with `$`. Poryscript handles this automatically.

---

## Gameplay Bugs (builds but game breaks)

### 6. Missing lock/release
**Symptom:** Player walks away during dialog, or is permanently stuck.
**Rules:**
  - `lock` → `faceplayer` → logic → `release` → `end`
  - `lockall` → logic → `releaseall` → `end`
  - NEVER mix: `lock`+`releaseall` or `lockall`+`release`
  - Every code path must hit release+end

### 7. Double-Lock from MSGBOX_NPC
**Symptom:** Player stuck after NPC dialog.
**Cause:** Manual `lock` + `msgbox("text", MSGBOX_NPC)`. MSGBOX_NPC already does lock/release.
**Fix:** Use MSGBOX_DEFAULT with manual lock/release, OR MSGBOX_NPC without manual lock/release.

### 8. Missing end Command
**Symptom:** Random behavior, crashes, corruption after script runs.
**Cause:** Script executes past its intended end into adjacent memory.
**Fix:** Every script must terminate with `end` (or `return` if called via `call`).

### 9. Off-by-One Warp IDs
**Symptom:** Door leads to wrong destination or black screen.
**Cause:** `dest_warp_id` is 0-indexed. First warp = 0, second = 1.
**Fix:** Count warps in destination map starting from 0.

### 10. Missing Return Warp
**Symptom:** Player enters building but can't leave.
**Fix:** Every warp must have a bidirectional counterpart.

### 11. Trainer Won't Battle
**Cause (any of):**
  - `trainer_type` is `"TRAINER_TYPE_NONE"` (must be `"TRAINER_TYPE_NORMAL"`)
  - `trainer_sight_or_berry_tree_id` is `"0"` (must be >= `"1"`)
  - Script doesn't use `trainerbattle_*` command
  - TRAINER_* constant doesn't exist in trainer data

### 12. NPC on Wrong Elevation
**Symptom:** NPC visible but can't interact / player walks through.
**Fix:** NPC elevation must match collision layer at that tile. Use 3 for ground, 0 for all.

### 13. Duplicate local_ids
**Symptom:** Wrong NPC responds to applymovement, shared behaviors.
**Fix:** Every object event must have unique sequential local_id starting from 1.

### 14. Infinite Item Gift
**Symptom:** Player gets unlimited items from NPC.
**Fix:** Always gate with `if (!flag(FLAG_RECEIVED_*))` + `setflag`.

### 15. Trigger Fires Repeatedly
**Symptom:** Cutscene replays on every step.
**Fix:** Script must `setvar(VAR, different_value)` to prevent re-triggering.

### 16. Map Connection Offset Mismatch
**Symptom:** Adjacent maps don't visually align.
**Fix:** If A→B offset=N, B→A offset=-N. Set both simultaneously.

### 17. Script Label Name Mismatch
**Symptom:** NPC does nothing, or build warning.
**Fix:** Copy-paste labels between map.json and scripts. Never manually type both.

---

## File Corruption Bugs

### 18. Full File Rewrite
**Symptom:** Map loses all existing events/scripts.
**Cause:** AI writes entire new file instead of surgical edit.
**Prevention:** ALWAYS read file first, modify only the target section.

### 19. Broken JSON Array Structure
**Symptom:** Porymap can't parse map.json.
**Common:** Wrong array for event type, missing comma before new element,
trailing comma after last element, wrong nesting.

### 20. Unregistered New Map
**Symptom:** Map doesn't appear in game or Porymap.
**Fix:** Add to `data/maps/map_groups.json` and verify layout exists.

---

## The Zero-Assumption Checklist

Before writing ANY code, confirm:

- [ ] I have READ the current file(s) I'm about to edit
- [ ] Every constant I use has been VERIFIED with grep
- [ ] Every script label I reference ACTUALLY EXISTS
- [ ] JSON field types match the specification (strings vs integers)
- [ ] Warps are bidirectional with correct 0-indexed dest_warp_id
- [ ] local_ids are sequential from 1 with no gaps
- [ ] Every script ends with `end` (or `return`)
- [ ] Every lock has a matching release (and they're the correct pair)
- [ ] Item/Pokémon gifts are gated behind flags
- [ ] Trigger scripts change their var to prevent re-fire
- [ ] The ROM builds successfully after my changes
