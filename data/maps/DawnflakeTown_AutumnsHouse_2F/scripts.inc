DawnflakeTown_AutumnsHouse_2F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn — waiting in her room before starter cutscene
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_2F_EventScript_Autumn::
	lock
	faceplayer
	msgbox DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaiting, MSGBOX_DEFAULT
	setflag FLAG_SNOW_TOLD_AUTUMN
	closemessage
	applymovement 1, DawnflakeTown_AutumnsHouse_2F_Movement_RunOut
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_BEDROOM
	removeobject 1
	release
	end

DawnflakeTown_AutumnsHouse_2F_Movement_RunOut:
	walk_in_place_faster_down
	walk_in_place_faster_right
	step_end

DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaiting:
	.string "AUTUMN: {PLAYER}! Is EVERGREEN\n"
	.string "ready for us?\p"
	.string "Oh my gosh - I'm going right\n"
	.string "now. Meet me at the lab!$"
