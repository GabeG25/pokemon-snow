DawnflakeTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DawnflakeTown_PlayersHouse_2F_OnFrame
	.byte 0

DawnflakeTown_PlayersHouse_2F_OnFrame:
	map_script_2 VAR_SNOW_INTRO_STATE, 0, DawnflakeTown_PlayersHouse_2F_EventScript_WakeUp
	.2byte 0

@ ═══════════════════════════════════════════════════════════
@ New-game silent seed — fires once on first bedroom entry to
@ initialize Snow intro flags / vars and the heal respawn.  No
@ visible beat: player is dropped cold into the room and the Mom
@ cutscene downstairs supplies all narrative context (per CEO
@ design 2026-04-18).  VAR_SNOW_INTRO_STATE 0→1 prevents the
@ frame-table entry from matching again.
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
@ TV sign — bedroom flavor
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_TV::
	msgbox DawnflakeTown_PlayersHouse_2F_Text_TV, MSGBOX_SIGN
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

DawnflakeTown_PlayersHouse_2F_Text_WallClock:
	.string "A wooden wall clock.\p"
	.string "Quarter past eight.\n"
	.string "The morning's already moving\l"
	.string "without you.$"

DawnflakeTown_PlayersHouse_2F_Text_TV:
	.string "The TV is tuned to the\n"
	.string "BORALYSS WEATHER CHANNEL.\p"
	.string "'...third week of early-onset\n"
	.string "winter advisories. Route 1\l"
	.string "trainers are advised to pack\l"
	.string "extra layers.'\p"
	.string "You turn it off.$"
