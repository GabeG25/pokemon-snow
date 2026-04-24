# Raw Assembly Scripting Reference

Use raw assembly (.inc) only when Poryscript doesn't support the construct, or when
wrapping legacy scripts. All raw assembly in a .pory file must be enclosed in `raw` blocks.

## Syntax Rules

- Labels: `LabelName::` (global) or `LabelName:` (local)
- Comments: `@ comment` (NOT `#` — that's C preprocessor)
- Text strings end with `$`
- Commands are macros defined in `asm/macros/event.inc`
- Parameters separated by commas: `command param1, param2`

## Script Structure

```
MapName_EventScript_Example::
    lock
    faceplayer
    msgbox MapName_Text_Hello, MSGBOX_DEFAULT
    release
    end

MapName_Text_Hello:
    .string "Hello, {PLAYER}!\p"
    .string "Welcome to town!$"
```

## Map Scripts (raw)

```
MapName_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, MapName_OnTransition
    map_script MAP_SCRIPT_ON_FRAME_TABLE, MapName_OnFrame
    .byte 0

MapName_OnTransition:
    setobjectxyperm 2, 10, 5
    end

MapName_OnFrame:
    map_script_2 VAR_ROUTE1_STATE, 0, MapName_Scene_Intro
    map_script_2 VAR_ROUTE1_STATE, 2, MapName_Scene_Rival
    .2byte 0
```

**Critical terminators:**
- mapscripts function: `.byte 0`
- Table map scripts (ON_FRAME_TABLE, ON_WARP_INTO_MAP_TABLE): `.2byte 0`
- Movements: `step_end`
- Text: `$`

## Constants in Raw Assembly

```
.set LOCALID_RIVAL, 2
.set LOCALID_MOM, 1
```

Use `.set` for file-local constants, `.equ` for constants referenced across files.

## Trainerbattle Types (raw)

```
@ Standard single battle
trainerbattle_single TRAINER_ROUTE1_HIKER, Route1_Text_HikerIntro, Route1_Text_HikerDefeat

@ Double battle
trainerbattle_double TRAINER_ROUTE1_TWINS, Route1_Text_TwinsIntro, Route1_Text_TwinsDefeat, Route1_Text_TwinsNeedTwo

@ Rematch single
trainerbattle_rematch TRAINER_ROUTE1_HIKER, Route1_Text_HikerRematchIntro, Route1_Text_HikerRematchDefeat

@ With continue script (runs after first defeat)
trainerbattle_single TRAINER_GYM_LEADER, Gym_Text_Intro, Gym_Text_Defeat, Gym_EventScript_AfterDefeat

@ No intro music
trainerbattle_no_intro TRAINER_EVIL, Evil_Text_Intro, Evil_Text_Defeat
```

## Movement (raw)

```
MapName_Movement_Walk::
    walk_down
    walk_down
    walk_left
    face_up
    step_end
```

In raw assembly, you MUST include `step_end`. Omitting it causes infinite movement loop.
You cannot use the `* N` repeat syntax — that's Poryscript only.

## Text (raw)

```
MapName_Text_Hello:
    .string "First line.\n"
    .string "Second line.\l"
    .string "Third line (scrolled).\p"
    .string "New paragraph.\n"
    .string "Continues here.$"
```

EVERY text block MUST end with `$`. Without it, the game reads garbage memory until it
finds a `$` byte somewhere in ROM.

## Conditional Branching (raw)

```
@ Compare and branch
compare VAR_ROUTE1_STATE, 1
goto_if_eq MapName_EventScript_State1

@ Flag checks
goto_if_set FLAG_BADGE_1, MapName_EventScript_HasBadge
goto_if_unset FLAG_BADGE_1, MapName_EventScript_NoBadge

@ Multiple comparisons
checkplayergender
compare VAR_RESULT, MALE
goto_if_eq MapName_EventScript_Male
compare VAR_RESULT, FEMALE
goto_if_eq MapName_EventScript_Female
```

## Comparison Operators (raw)

```
goto_if_eq     @ ==
goto_if_ne     @ !=
goto_if_gt     @ >
goto_if_ge     @ >=
goto_if_lt     @ <
goto_if_le     @ <=
```

## Common Raw Commands

```
@ Flow
end
return
call MapName_EventScript_Helper
goto MapName_EventScript_Other

@ Variables
setvar VAR_NAME, value
addvar VAR_NAME, value
setflag FLAG_NAME
clearflag FLAG_NAME

@ Text
msgbox TextLabel, MSGBOX_DEFAULT
waitmessage
closemessage

@ Movement
applymovement LOCAL_ID, MovementLabel
waitmovement 0

@ Objects
removeobject LOCAL_ID
addobject LOCAL_ID
setobjectxyperm LOCAL_ID, x, y

@ Items
additem ITEM_NAME, quantity
removeitem ITEM_NAME, quantity
checkitemspace ITEM_NAME, quantity

@ Sound
playse SE_PIN
waitse
playfanfare MUS_FANFA4
waitfanfare

@ Screen
fadescreen FADE_TO_BLACK
fadescreen FADE_FROM_BLACK
```
