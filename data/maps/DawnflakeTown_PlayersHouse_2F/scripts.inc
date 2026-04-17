DawnflakeTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DawnflakeTown_PlayersHouse_2F_OnFrame
	.byte 0

DawnflakeTown_PlayersHouse_2F_OnFrame:
	map_script_2 VAR_SNOW_INTRO_STATE, 0, DawnflakeTown_PlayersHouse_2F_EventScript_WakeUp
	.2byte 0

@ ═══════════════════════════════════════════════════════════
@ New-game wake-up — seeds all Snow intro flags and plays a
@ brief establishing beat.  Fires once (VAR_SNOW_INTRO_STATE
@ advances from 0→1, so the frame-table entry never matches
@ again).  Replaces the truck-based flag seeding.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_WakeUp::
	lockall
	@ ── Suppress vanilla Littleroot intro state machine ──
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_LITTLEROOT_INTRO_STATE, 8
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 4
	@ ── Snow-specific hide flags for cutscene NPCs ──
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	setflag FLAG_SNOW_HIDE_AUTUMN_RUN_OUT_LAB
	setflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	setflag FLAG_SNOW_HIDE_ASHER_LAB
	@ ── Whiteout respawn → Player's House ──
	setrespawn HEAL_LOCATION_DAWNFLAKE_TOWN_PLAYERS_HOUSE_2F
	@ ── Mark intro done so this never fires again ──
	setvar VAR_SNOW_INTRO_STATE, 1
	@ ── Wake-up beat ──
	msgbox DawnflakeTown_PlayersHouse_2F_Text_WakeUp, MSGBOX_DEFAULT
	releaseall
	end

@ ═══════════════════════════════════════════════════════════
@ Bedroom PC — uses vanilla BedroomPC special so the starting
@ Potion seeded via NewGameInitPCItems is visible.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_PC::
	lockall
	setvar VAR_0x8004, PC_LOCATION_MAYS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

@ ═══════════════════════════════════════════════════════════
@ Candy Box — hidden item-style trigger at bed foot
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_CandyBoxTrigger::
	lockall
	goto_if_set FLAG_SNOW_GOT_CANDY_BOX, DawnflakeTown_PlayersHouse_2F_EventScript_CandyBoxEnd
	playse SE_PIN
	msgbox DawnflakeTown_PlayersHouse_2F_Text_CandyBoxFound, MSGBOX_DEFAULT
	setflag FLAG_SNOW_GOT_CANDY_BOX
DawnflakeTown_PlayersHouse_2F_EventScript_CandyBoxEnd::
	releaseall
	end

@ ═══════════════════════════════════════════════════════════
@ Wall clock sign
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_WallClock::
	msgbox DawnflakeTown_PlayersHouse_2F_Text_WallClock, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_Text_CandyBoxFound:
	.string "A half-empty box of candy is\n"
	.string "tucked under the bed.\p"
	.string "Mom must have left it as a\n"
	.string "moving-day treat.$"

DawnflakeTown_PlayersHouse_2F_Text_WallClock:
	.string "A wooden wall clock.\p"
	.string "Quarter past eight.\n"
	.string "The morning's already moving\l"
	.string "without you.$"

DawnflakeTown_PlayersHouse_2F_Text_WakeUp:
	.string "...\p"
	.string "You open your eyes.\p"
	.string "The new room still smells like\n"
	.string "cardboard and pine.\p"
	.string "MOM's voice drifts up from\n"
	.string "downstairs.$"
