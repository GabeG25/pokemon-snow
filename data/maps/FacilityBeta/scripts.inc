FacilityBeta_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ FACILITY BETA — F22 TYRELL #1 (FIRST CONFRONTATION)
@ ═══════════════════════════════════════════════════════════════
@ Per CEO: F22 Tyrell is his "educating" battle. He explains the
@ error of the player's ways — dismissive, superior. Post-battle
@ he retreats, shaken but composed, setting up the F27 desperate
@ rematch.
@
@ STUB: Facility Beta is a single-room map reusing Devon Corp 2F
@ layout. Full v17 §18 Beta design calls for 2 floors + roof, 22
@ grunts, F19 Mika / F20 Xenon / F21 Asher #5 gating F22. Those
@ are CEO-creative (DECISIONS.md grunt locks). This stub gives
@ the story a working first-confrontation beat.

FacilityBeta_EventScript_Tyrell::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox FacilityBeta_Text_TyrellEducates, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SNOW_F22_TYRELL, FacilityBeta_Text_TyrellDefeat
	msgbox FacilityBeta_Text_TyrellRetreats, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SNOW_BEAT_F22_TYRELL
	@ Remove Tyrell's object — he has left the roof
	removeobject 1
	fadescreenspeed FADE_TO_BLACK, 8
	delay 30
	fadescreenspeed FADE_FROM_BLACK, 8
	msgbox FacilityBeta_Text_Aftermath, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

FacilityBeta_Text_TyrellEducates:
	.string "TYRELL: Ah.\n"
	.string "The trainer from DAWNFLAKE.\p"
	.string "PRIYO mentioned you. EVERGREEN\n"
	.string "mentioned you. Your rival won't\l"
	.string "shut up about you.\p"
	.string "Let me educate you on a\n"
	.string "mistake you're making.\p"
	.string "BORALYSS was SOFT, {PLAYER}.\n"
	.string "Comfortable. Complacent.\p"
	.string "I am giving this region a\n"
	.string "winter it will remember. I am\l"
	.string "giving it STRENGTH.\p"
	.string "You are stopping that.\p"
	.string "Allow me to show you the error\n"
	.string "of that choice.$"

FacilityBeta_Text_TyrellDefeat:
	.string "TYRELL: ...Interesting.$"

FacilityBeta_Text_TyrellRetreats:
	.string "TYRELL: A setback. Nothing more.\p"
	.string "You'll find that persistence\n"
	.string "is not the same as being right,\l"
	.string "trainer.\p"
	.string "KYUREM and I have work to\n"
	.string "complete. Facility ALPHA\l"
	.string "awaits.\p"
	.string "Don't come further than you\n"
	.string "can return from.$"

FacilityBeta_Text_Aftermath:
	.string "TYRELL has left the chamber.\p"
	.string "The machines hum on, colder\n"
	.string "than the cave outside.$"
