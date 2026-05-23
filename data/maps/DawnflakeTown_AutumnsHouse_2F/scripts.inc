DawnflakeTown_AutumnsHouse_2F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn — waiting in her room before starter cutscene
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_2F_EventScript_Autumn::
	lock
	faceplayer
	msgbox DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaitingPart1, MSGBOX_DEFAULT
	closemessage
	@ Let the textbox-close animation and its SE_SELECT finish before
	@ we cue the exclamation, so SE_PIN is not stomped by the close beep.
	delay 16
	playse SE_PIN
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	@ Brief beat after the bubble so the next line doesn't snap on top.
	delay 12
	msgbox DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaitingPart2, MSGBOX_DEFAULT
	setflag FLAG_SNOW_TOLD_AUTUMN
	closemessage
	delay 12
	@ Autumn at (3,3) needs to reach the stairs at (7,1).
	@ Default path runs y=2 (up then right); right-first path runs y=3.
	@ Pick the one that avoids whichever tile the player is occupying.
	@ Player at (3,2) (directly above Autumn) blocks the default up-first
	@ path on its first step. In that case, take the right-first path
	@ which stays on y=3 until reaching column 7.
	getplayerxy VAR_TEMP_2, VAR_TEMP_3
	compare VAR_TEMP_2, 3
	goto_if_ne DawnflakeTown_AutumnsHouse_2F_EventScript_AutumnRunOutUpFirst
	compare VAR_TEMP_3, 2
	goto_if_ne DawnflakeTown_AutumnsHouse_2F_EventScript_AutumnRunOutUpFirst
	@ Player at (3,2) — use the right-first path.
	applymovement 1, DawnflakeTown_AutumnsHouse_2F_Movement_RunOutApproachRightFirst
	waitmovement 0
	playse SE_EXIT
	applymovement 1, DawnflakeTown_AutumnsHouse_2F_Movement_RunOutFinal
	waitmovement 0
	goto DawnflakeTown_AutumnsHouse_2F_EventScript_AutumnRunOutDone

DawnflakeTown_AutumnsHouse_2F_EventScript_AutumnRunOutUpFirst::
	@ Movement is split so SE_EXIT fires exactly as Autumn steps into
	@ the tile below the stair-warp — direction-independent.
	applymovement 1, DawnflakeTown_AutumnsHouse_2F_Movement_RunOutApproach
	waitmovement 0
	playse SE_EXIT
	applymovement 1, DawnflakeTown_AutumnsHouse_2F_Movement_RunOutFinal
	waitmovement 0

DawnflakeTown_AutumnsHouse_2F_EventScript_AutumnRunOutDone::
	setflag FLAG_SNOW_HIDE_AUTUMN_BEDROOM
	removeobject 1
	@ Autumn is now waiting at the lab beside Evergreen for the
	@ starter ceremony — see EvergreensLab Evergreen script.
	clearflag FLAG_SNOW_HIDE_AUTUMN_LAB
	release
	end

@ Default exit path. Autumn (3,3) sprints up then right:
@ Approach: up 1 to (3, 2), right 4 to (7, 2). SE_EXIT fires here.
@ Final: up 1 to (7, 1) [stairs warp tile].
@ walk_fast_* gives the visual of her running excitedly out.
DawnflakeTown_AutumnsHouse_2F_Movement_RunOutApproach:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

@ Alternate exit path used when the player is standing on (3,2).
@ Same step count, identical SE_EXIT timing — Autumn arrives at (7,2)
@ in 5 walk_fast_* frames either way. Right 4 to (7,3), then up 1
@ to (7,2). Final path then handles the last step up to the warp.
DawnflakeTown_AutumnsHouse_2F_Movement_RunOutApproachRightFirst:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

DawnflakeTown_AutumnsHouse_2F_Movement_RunOutFinal:
	walk_fast_up
	step_end

DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaitingPart1:
	.string "AUTUMN: {PLAYER}! Is EVERGREEN\n"
	.string "ready for us?$"

DawnflakeTown_AutumnsHouse_2F_Text_AutumnWaitingPart2:
	.string "What do you mean he's been\n"
	.string "waiting for us!?\p"
	.string "Okay - I'm running ahead.\n"
	.string "I'll see you at the LAB!$"

@ ═══════════════════════════════════════════════════════════
@ Field notebook — Autumn's messy research desk
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_2F_EventScript_Notebook::
	msgbox DawnflakeTown_AutumnsHouse_2F_Text_Notebook, MSGBOX_SIGN
	end

DawnflakeTown_AutumnsHouse_2F_Text_Notebook:
	.string "A messy desk covered in charts,\n"
	.string "graphs, research papers, and\l"
	.string "glitter.\p"
	.string "The disorganization gives you\n"
	.string "anxiety just looking at it.$"

@ ═══════════════════════════════════════════════════════════
@ Autumn's PC — partial research article on her desk
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_2F_EventScript_PC::
	msgbox DawnflakeTown_AutumnsHouse_2F_Text_PC, MSGBOX_SIGN
	end

DawnflakeTown_AutumnsHouse_2F_Text_PC:
	.string "It's AUTUMN's PC.\p"
	.string "Currently pulled up is\n"
	.string "'The interaction between\l"
	.string "SENTRET and thermal\l"
	.string "adaptation'.\p"
	.string "The article looks partially\n"
	.string "typed, but not finished yet.$"
