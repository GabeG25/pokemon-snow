# Poryscript Complete Reference

Poryscript is a higher-level scripting language that compiles to pokeemerald's bytecode
assembly. It is the primary scripting format for Pokémon Snow. The compiler lives at
`tools/poryscript/`. Source files are `.pory`, compiled output is `.inc`.

## Table of Contents

1. [Top-Level Statements](#top-level)
2. [script Blocks](#script-blocks)
3. [mapscripts Blocks](#mapscripts-blocks)
4. [text Blocks](#text-blocks)
5. [movement Blocks](#movement-blocks)
6. [mart Blocks](#mart-blocks)
7. [raw Blocks](#raw-blocks)
8. [Constants](#constants)
9. [Control Flow](#control-flow)
10. [Boolean Expressions](#boolean-expressions)
11. [Common Commands](#common-commands)
12. [MSGBOX Types](#msgbox-types)
13. [Trainer Battle Commands](#trainer-battles)
14. [Object/NPC Commands](#object-commands)
15. [Sound Commands](#sound-commands)
16. [Screen Effects](#screen-effects)
17. [Item Commands](#item-commands)
18. [Pokémon Commands](#pokemon-commands)
19. [Scope Modifiers](#scope-modifiers)
20. [Inline Features](#inline-features)
21. [Naming Conventions](#naming-conventions)

---

## 1. Top-Level Statements <a name="top-level"></a>

A .pory file can contain these top-level statement types:
- `script` — Event script with commands and control flow
- `mapscripts` — Map-level script triggers
- `text` — Standalone text label
- `movement` — Movement sequence
- `mart` — Shop item list
- `raw` — Raw assembly passthrough

Order does not matter. All are global by default (accessible from other files).

---

## 2. script Blocks <a name="script-blocks"></a>

```
script MapName_EventScript_Name {
    lock
    faceplayer
    msgbox("Hello!")
    release
    end
}
```

Every script MUST end with `end` (or `return` if called via `call`).
Missing `end` causes the game to execute garbage memory — guaranteed crash or softlock.

---

## 3. mapscripts Blocks <a name="mapscripts-blocks"></a>

Every map needs exactly one mapscripts block. Even if empty:

```
mapscripts MapName_MapScripts {
}
```

### Map Script Types (in execution priority order)

| Type | When | Use For |
|------|------|---------|
| `MAP_SCRIPT_ON_DIVE_WARP` | After player dives/emerges | Sealed Chamber check |
| `MAP_SCRIPT_ON_TRANSITION` | During transition (before drawn) | Set flags/vars, update object positions, set weather |
| `MAP_SCRIPT_ON_LOAD` | After layout loaded (before drawn) | Set metatiles before first draw |
| `MAP_SCRIPT_ON_RESUME` | End of map load + every return from battle/menu | Hide defeated static Pokémon, maintain state |
| `MAP_SCRIPT_ON_RETURN_TO_FIELD` | Only on return to field (not initial load) | Post-battle cleanup |
| `MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE` | After objects loaded (conditional table) | Add/position objects based on vars |
| `MAP_SCRIPT_ON_FRAME_TABLE` | Every frame after fade-in (conditional table) | Trigger cutscenes, announcements |

### Standard (non-table) map scripts

```
mapscripts MapName_MapScripts {
    MAP_SCRIPT_ON_TRANSITION: MapName_OnTransition
    MAP_SCRIPT_ON_RESUME: MapName_OnResume
}

script MapName_OnTransition {
    setobjectxyperm(2, 10, 5)
    end
}
```

### Table-based map scripts (ON_FRAME_TABLE, ON_WARP_INTO_MAP_TABLE)

These run ONLY the FIRST matching condition:

```
mapscripts MapName_MapScripts {
    MAP_SCRIPT_ON_FRAME_TABLE [
        VAR_ROUTE1_STATE, 0: MapName_Scene_Intro
        VAR_ROUTE1_STATE, 2: MapName_Scene_Rival
    ]
    MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE [
        VAR_BIRCH_LAB_STATE, 2: MapName_SetPositions
    ]
}
```

The game checks each row top-to-bottom. First match runs, rest are skipped.

---

## 4. text Blocks <a name="text-blocks"></a>

Standalone text accessible from C code or other files:

```
text MapName_Text_Sign {
    "Dawnflake Town\p"
    "A village where snowflakes never melt."
}
```

Poryscript auto-appends `$` terminator. Auto-formats line breaks if `format()` is used.

### Text Control Characters

| Char | Effect |
|------|--------|
| `\n` | Newline to second line of message box (use when second line is empty) |
| `\l` | Scroll: shifts text up one line (use when both lines are filled) |
| `\p` | New paragraph: clears box, starts fresh (player presses A) |
| `{PLAYER}` | Replaced with player's name |
| `{RIVAL}` | Replaced with rival's name |
| `{STR_VAR_1}` | Replaced with buffered string variable 1 |
| `{STR_VAR_2}` | Replaced with buffered string variable 2 |
| `{STR_VAR_3}` | Replaced with buffered string variable 3 |

### Inline text in scripts

```
msgbox("Short text here.")

msgbox("Multi-line text\p"
       "Second paragraph here.")
```

### format() for auto-wrapping

```
msgbox(format("This is a long string that Poryscript will automatically
    break into lines that fit the game's text box."))
```

`format()` uses font_config.json character widths to insert `\n`, `\l`, `\p` correctly.

---

## 5. movement Blocks <a name="movement-blocks"></a>

```
movement MapName_Movement_WalkToPlayer {
    walk_down * 3
    walk_left * 2
    face_player
}
```

Poryscript auto-appends `step_end`. In raw assembly, you MUST add it manually.

### Repeat syntax
`walk_right * 5` repeats 5 times. Only works in Poryscript (not raw assembly).

### Inline movements (Poryscript 4.0+)
```
applymovement(OBJ_EVENT_ID_PLAYER, moves(
    walk_left * 4
    face_down
))
```

### Common Movement Actions
```
walk_up, walk_down, walk_left, walk_right
walk_fast_up, walk_fast_down, walk_fast_left, walk_fast_right
face_up, face_down, face_left, face_right
face_player, face_original_direction
walk_in_place_up, walk_in_place_down, walk_in_place_left, walk_in_place_right
lock_facing_direction, unlock_facing_direction
delay_4, delay_8, delay_16
emote_exclamation_mark, emote_question_mark, emote_heart
jump_in_place_up, jump_in_place_down, jump_in_place_left, jump_in_place_right
step_end    (ONLY needed in raw assembly — Poryscript adds automatically)
```

Full list: `asm/macros/movement.inc`

---

## 6. mart Blocks <a name="mart-blocks"></a>

```
mart MapName_Mart {
    ITEM_POTION
    ITEM_ANTIDOTE
    ITEM_POKE_BALL
}
```

---

## 7. raw Blocks <a name="raw-blocks"></a>

Passes content directly to the assembler without Poryscript processing:

```
raw `
MapName_MapScripts::
    map_script_2 MAP_SCRIPT_ON_TRANSITION, MapName_OnTransition
    .byte 0
`
```

**Critical raw assembly rules:**
- Labels end with `::` (global) or `:` (local)
- Text strings MUST end with `$`
- mapscripts functions end with `.byte 0`
- Table map scripts (ON_FRAME_TABLE, ON_WARP_INTO_MAP_TABLE) end with `.2byte 0`
- Movements MUST end with `step_end`
- Comments use `@` (not `#` — `#` is a preprocessor directive)

---

## 8. Constants <a name="constants"></a>

```
const LOCALID_RIVAL = 2
const LOCALID_NURSE = 1
```

Constants work in script/text/movement/mapscripts blocks, but NOT inside `raw` blocks.
For raw blocks, use `.set`:

```
raw `
.set LOCALID_RIVAL, 2
`
```

You can define both to use interchangeably:
```
const LOCALID_RIVAL = 2
raw `
.set LOCALID_RIVAL, 2
`
```

---

## 9. Control Flow <a name="control-flow"></a>

### if / elif / else

```
if (flag(FLAG_BADGE_1)) {
    msgbox("You have the first badge!")
} elif (var(VAR_STORY_STATE) >= 5) {
    msgbox("You're making progress.")
} else {
    msgbox("You're just starting out.")
}
```

### while loops

```
while (var(VAR_TEMP_1) < 5) {
    addvar(VAR_TEMP_1, 1)
}
```

### do...while loops

```
do {
    // body
} while (var(VAR_TEMP_1) != 0)
```

### switch

```
switch (var(VAR_STARTER_CHOICE)) {
    case 0:
        msgbox("Treecko!")
    case 1:
        msgbox("Torchic!")
    case 2:
        msgbox("Mudkip!")
    default:
        msgbox("Unknown!")
}
```

### Early exit

```
script MapName_EventScript_Example {
    lock
    faceplayer
    if (flag(FLAG_DONE)) {
        msgbox("Already done.")
        release
        end
    }
    // ... rest of script
    release
    end
}
```

Every code path MUST reach `release` and `end`.

---

## 10. Boolean Expressions <a name="boolean-expressions"></a>

| Expression | Meaning |
|-----------|---------|
| `flag(FLAG_NAME)` | Flag is SET (== 1) |
| `!flag(FLAG_NAME)` | Flag is NOT set (== 0) |
| `var(VAR_NAME) == N` | Variable equals N |
| `var(VAR_NAME) != N` | Variable does not equal N |
| `var(VAR_NAME) > N` | Variable greater than N |
| `var(VAR_NAME) >= N` | Variable greater or equal N |
| `var(VAR_NAME) < N` | Variable less than N |
| `var(VAR_NAME) <= N` | Variable less or equal N |
| `defeated(TRAINER_NAME)` | Trainer has been defeated |

---

## 11. Common Commands <a name="common-commands"></a>

### Script flow
```
end                                     // End script execution
return                                  // Return to calling script (used with call)
call(ScriptLabel)                       // Call another script, can return
goto(ScriptLabel)                       // Jump to another script, no return
```

### Player interaction
```
lock                                    // Freeze player + selected object
lockall                                 // Freeze all objects
faceplayer                              // NPC faces the player
release                                 // Unfreeze (counterpart of lock)
releaseall                              // Unfreeze all (counterpart of lockall)
```

**CRITICAL:** `lock` pairs with `release`. `lockall` pairs with `releaseall`.
NEVER mix them. `lock`+`releaseall` or `lockall`+`release` causes unpredictable behavior.

### Variables and flags
```
setvar(VAR_NAME, value)                 // Set variable to value
addvar(VAR_NAME, value)                 // Add to variable
setflag(FLAG_NAME)                      // Set flag to 1 (true)
clearflag(FLAG_NAME)                    // Set flag to 0 (false)
checkplayergender                       // Sets VAR_RESULT to MALE or FEMALE
getplayerxy(VAR_X, VAR_Y)              // Gets player map coordinates
```

### Text
```
msgbox("text")                          // Show message (MSGBOX_DEFAULT)
msgbox("text", MSGBOX_NPC)             // Auto lock/faceplayer/release
msgbox("text", MSGBOX_SIGN)            // Auto lockall/releaseall
msgbox("text", MSGBOX_YESNO)           // Yes/No prompt -> VAR_RESULT
closemessage                            // Close current message box
waitmessage                             // Wait for text to finish printing
```

### String buffers
```
bufferspeciesname(STR_VAR_1, SPECIES_PIKACHU)
bufferitemname(STR_VAR_1, ITEM_POTION)
buffermovename(STR_VAR_1, MOVE_TACKLE)
buffernumberstring(STR_VAR_1, VAR_TEMP_1)
bufferstring(STR_VAR_1, MyTextLabel)
```

---

## 12. MSGBOX Types <a name="msgbox-types"></a>

| Type | Behavior |
|------|----------|
| `MSGBOX_DEFAULT` | Show text, wait for A press. Does NOT auto lock/release. |
| `MSGBOX_NPC` | Auto `lock` + `faceplayer` before, auto `release` after. For simple single-message NPCs. |
| `MSGBOX_SIGN` | Auto `lockall` before, auto `releaseall` after. For sign posts. |
| `MSGBOX_YESNO` | Show text + Yes/No prompt. Result in `VAR_RESULT` (YES or NO). |
| `MSGBOX_AUTOCLOSE` | Same as DEFAULT but auto-closes message box + `release` after. |
| `MSGBOX_GETPOINTS` | Plays BP jingle. Battle Frontier only. |

**CRITICAL BUG SOURCE:** If you use `MSGBOX_NPC`, do NOT wrap it in manual `lock`/`release`.
It already does that automatically. Double-locking causes the player to get stuck.

**When to use MSGBOX_NPC:** Only for the simplest NPCs with a single message and no
conditionals. For anything with if/else, multiple messages, movements, or flag checks,
use manual `lock`/`faceplayer`/`release` with `MSGBOX_DEFAULT`.

---

## 13. Trainer Battle Commands <a name="trainer-battles"></a>

### trainerbattle_single
```
script MapName_EventScript_Trainer1 {
    trainerbattle_single(TRAINER_CONSTANT,
        "Intro dialog before battle",
        "Defeat dialog after losing")
    msgbox("Post-battle dialog when re-talked.", MSGBOX_AUTOCLOSE)
    end
}
```

Commands after `trainerbattle_*` only execute AFTER the trainer is defeated.
Before first defeat, the battle system handles everything.

### trainerbattle_double
```
trainerbattle_double(TRAINER_CONSTANT,
    "Intro dialog",
    "Defeat dialog",
    "You need two Pokémon for a double battle.")
```

Fourth string shows if player has < 2 usable Pokémon.

### trainerbattle with continue script
```
trainerbattle_single(TRAINER_CONSTANT,
    "Intro", "Defeat",
    MapName_EventScript_AfterBattle)

script MapName_EventScript_AfterBattle {
    // Runs immediately after first defeat
    msgbox("You earned a badge!")
    setflag(FLAG_BADGE_1)
    release
    end
}
```

### Object event requirements for trainers

The map.json object event MUST have:
- `"trainer_type": "TRAINER_TYPE_NORMAL"` (STRING)
- `"trainer_sight_or_berry_tree_id": "4"` (STRING — sight radius in tiles)
- `"script": "MapName_EventScript_TrainerName"` (must exist in scripts file)
- Appropriate `movement_type` for facing direction

---

## 14. Object/NPC Commands <a name="object-commands"></a>

```
removeobject(LOCAL_ID)                  // Hide object on current map
addobject(LOCAL_ID)                     // Show previously hidden object
showobjectat(LOCAL_ID, MAP_CONSTANT)    // Show object on specific map
hideobjectat(LOCAL_ID, MAP_CONSTANT)    // Hide object on specific map
setobjectxyperm(LOCAL_ID, x, y)         // Permanently reposition object
setobjectxy(LOCAL_ID, x, y)             // Temporarily reposition object
setobjectmovementtype(LOCAL_ID, MOVEMENT_TYPE_*)
applymovement(LOCAL_ID, MovementLabel)  // Apply movement to object
waitmovement(0)                         // Wait for ALL movements to complete
```

`OBJ_EVENT_ID_PLAYER` is the special ID for the player character.

When using `applymovement` for multiple objects simultaneously:
```
applymovement(LOCALID_NPC1, Movement_A)
applymovement(LOCALID_NPC2, Movement_B)
applymovement(OBJ_EVENT_ID_PLAYER, Movement_C)
waitmovement(0)    // Waits for ALL to finish
```

---

## 15. Sound Commands <a name="sound-commands"></a>

```
playse(SE_PIN)                          // Play sound effect
waitse                                  // Wait for SE to finish
playfanfare(MUS_OBTAIN_ITEM)            // Play fanfare jingle
waitfanfare                             // Wait for fanfare to finish
playbgm(MUS_LITTLEROOT_TOWN, FALSE)     // Play background music
fadedefaultbgm                          // Restore map's default BGM
playmoncry(SPECIES_PIKACHU, 0)          // Play Pokémon cry
waitmoncry                              // Wait for cry to finish
```

Sound/music constants are in `include/constants/songs.h`.

---

## 16. Screen Effects <a name="screen-effects"></a>

```
fadescreen(FADE_TO_BLACK)               // Fade to black
fadescreen(FADE_FROM_BLACK)             // Fade from black
fadescreen(FADE_TO_WHITE)               // Fade to white
fadescreen(FADE_FROM_WHITE)             // Fade from white
special(HealPlayerParty)                // Fully heal player's party
warp(MAP_DESTINATION, warp_id, x, y)    // Warp player to location
```

---

## 17. Item Commands <a name="item-commands"></a>

### Item ball pickup (object event on ground)
```
script MapName_EventScript_ItemPotion {
    finditem(ITEM_POTION, 1)
    end
}
```
`finditem` auto-handles message, bag check, and flag. The object event's `flag` field
controls visibility after pickup.

### NPC gives item (one-time gift)
```
script MapName_EventScript_Gift {
    lock
    faceplayer
    if (!flag(FLAG_RECEIVED_ITEM)) {
        additem(ITEM_POTION, 1)
        setflag(FLAG_RECEIVED_ITEM)
        msgbox("Here, take this!")
    } else {
        msgbox("I hope that helped!")
    }
    release
    end
}
```

**ALWAYS gate gifts behind a flag.** Without a flag check, the player gets infinite items.

### Check bag space
```
checkitemspace(ITEM_POTION, 1)
if (var(VAR_RESULT) == TRUE) {
    additem(ITEM_POTION, 1)
} else {
    msgbox("Your bag is full!")
}
```

---

## 18. Pokémon Commands <a name="pokemon-commands"></a>

### givemon (pokeemerald-expansion enhanced)
```
givemon(SPECIES_TREECKO, 5, ITEM_NONE)
```
VAR_RESULT is set to: MON_GIVEN_TO_PARTY, MON_GIVEN_TO_PC, or MON_CANT_GIVE

### Party checks
```
getpartysize                            // Party count -> VAR_RESULT
checkpartymove(MOVE_CUT)               // Check if party knows move
```

---

## 19. Scope Modifiers <a name="scope-modifiers"></a>

```
script(local) MapName_Helper { ... }    // Only accessible within this file
script(global) MapName_Public { ... }   // Accessible from any file (default)
```

Works for script, text, movement, and mapscripts.

---

## 20. Inline Features <a name="inline-features"></a>

### Inline movement (Poryscript 4.0+)
```
applymovement(2, moves(
    walk_down * 3
    face_left
))
```

### poryswitch (compile-time switch)
```
script Example {
    poryswitch(GAME_VERSION) {
        RUBY: msgbox("Ruby version")
        SAPPHIRE: msgbox("Sapphire version")
    }
}
```

---

## 21. Naming Conventions <a name="naming-conventions"></a>

Follow the project's established convention: `MapName_Type_Identifier`

| Type | Pattern | Example |
|------|---------|---------|
| Event Script | `MapName_EventScript_Desc` | `DawnflakeTown_EventScript_Nurse` |
| Text | `MapName_Text_Desc` | `DawnflakeTown_Text_WelcomeSign` |
| Movement | `MapName_Movement_Desc` | `Route1_Movement_RivalWalks` |
| Map Scripts | `MapName_MapScripts` | `DawnflakeTown_MapScripts` |
| On Transition | `MapName_OnTransition` | `Route1_OnTransition` |
| Scene | `MapName_Scene_Desc` | `Route1_Scene_RivalBattle` |
| Local ID const | `LOCALID_DESC` | `LOCALID_RIVAL` |

**Every script name MUST be globally unique across the entire project**, not just within
the file. Use the map name prefix to ensure uniqueness.
