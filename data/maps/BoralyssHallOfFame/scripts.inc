BoralyssHallOfFame_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BoralyssHallOfFame_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BoralyssHallOfFame_OnWarp
	.byte 0

BoralyssHallOfFame_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BoralyssHallOfFame_EventScript_TurnPlayerNorth
	.2byte 0

BoralyssHallOfFame_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BoralyssHallOfFame_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BoralyssHallOfFame_EventScript_EnterHoF
	.2byte 0

@ ═══════════════════════════════════════════════════════════════
@ HALL OF FAME CUTSCENE
@ ═══════════════════════════════════════════════════════════════
@ Triggered on first entry (VAR_TEMP_1 == 0). Sequence:
@   1. Tyrim + Player walk up together from south
@   2. Tyrim's "this is where we honor champions" beat
@   3. Prof. Evergreen enters from north, congratulates the Player
@   4. Evergreen initiates Player into the Hall of Fame
@   5. Snow-specific title card: "Made solely by Gabe Gibson"
@   6. Set FLAG_IS_CHAMPION, respawn to Dawnflake bedroom
@
@ Skips vanilla `special GameClear` to avoid the vanilla Hoenn
@ credits roll — replaced with a single bespoke title card per
@ CEO direction. Loses vanilla HoF PC entry-save as a tradeoff;
@ populating that is a CEO-follow-up engine task if desired.

BoralyssHallOfFame_EventScript_EnterHoF::
	lockall
	applymovement 1, BoralyssHallOfFame_Movement_WalkUp6
	applymovement LOCALID_PLAYER, BoralyssHallOfFame_Movement_WalkUp6
	waitmovement 0
	applymovement 1, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BoralyssHallOfFame_Text_TyrimHoFIntro, MSGBOX_DEFAULT
	closemessage
	applymovement 1, BoralyssHallOfFame_Movement_WalkUp5
	applymovement LOCALID_PLAYER, BoralyssHallOfFame_Movement_WalkUp5
	waitmovement 0
	delay 20
	@ Evergreen enters from north (unhide + face down already set by flag clear)
	clearflag FLAG_SNOW_HIDE_HOF_EVERGREEN
	addobject 2
	applymovement 2, BoralyssHallOfFame_Movement_EvergreenEnter
	waitmovement 0
	applymovement 1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BoralyssHallOfFame_Text_EvergreenCongrats, MSGBOX_DEFAULT
	closemessage
	applymovement 2, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox BoralyssHallOfFame_Text_EvergreenInitiates, MSGBOX_DEFAULT
	closemessage
	@ Fade to title card
	fadescreenspeed FADE_TO_BLACK, 12
	delay 30
	msgbox BoralyssHallOfFame_Text_TitleCard, MSGBOX_DEFAULT
	closemessage
	delay 60
	@ Set champion state and respawn
	setvar VAR_TEMP_1, 1
	setflag FLAG_IS_CHAMPION
	setrespawn HEAL_LOCATION_DAWNFLAKE_TOWN_PLAYERS_HOUSE_2F
	@ Warp to Dawnflake bedroom — player wakes up as Champion
	warp MAP_DAWNFLAKE_TOWN_PLAYERS_HOUSE_2F, 255, 5, 3
	waitstate
	releaseall
	end

BoralyssHallOfFame_Movement_WalkUp6:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BoralyssHallOfFame_Movement_WalkUp5:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BoralyssHallOfFame_Movement_EvergreenEnter:
	walk_down
	walk_down
	walk_down
	face_down
	step_end

BoralyssHallOfFame_Text_TyrimHoFIntro:
	.string "TYRIM: This room keeps record\n"
	.string "of every trainer who has held\l"
	.string "the BORALYSS throne.\p"
	.string "Today that list adds your name.$"

BoralyssHallOfFame_Text_EvergreenCongrats:
	.string "EVERGREEN: {PLAYER}!\p"
	.string "I came as soon as I heard.\n"
	.string "I couldn't miss this.\p"
	.string "You walked into my lab months\n"
	.string "ago not knowing which starter\l"
	.string "to pick.\p"
	.string "Now you're the CHAMPION of\n"
	.string "BORALYSS.$"

BoralyssHallOfFame_Text_EvergreenInitiates:
	.string "EVERGREEN: TYRIM. If I may.\p"
	.string "{PLAYER}, by the authority of\n"
	.string "the BORALYSS POKEMON LEAGUE,\l"
	.string "I welcome you to the HALL OF\l"
	.string "FAME.\p"
	.string "You and your POKEMON. Together.\p"
	.string "Just as it should be.$"

BoralyssHallOfFame_Text_TitleCard:
	.string "POKEMON SNOW\p"
	.string "Made solely by\n"
	.string "GABE GIBSON$"
