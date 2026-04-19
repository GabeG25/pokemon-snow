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
	@ Autumn is now waiting at the lab beside Evergreen for the
	@ starter ceremony — see EvergreensLab Evergreen script.
	clearflag FLAG_SNOW_HIDE_AUTUMN_LAB
	release
	end

@ Autumn at (3, 3) sprints to the stairs at (7, 1):
@ up 1 to (3, 2), right 4 to (7, 2), up 1 to (7, 1) [stairs warp].
@ walk_fast_* gives the visual of her running excitedly out.
DawnflakeTown_AutumnsHouse_2F_Movement_RunOut:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaiting:
	.string "AUTUMN: {PLAYER}! Is EVERGREEN\n"
	.string "ready for us?\p"
	.string "Okay - I'm running ahead.\n"
	.string "I'll see you at the lab!$"
