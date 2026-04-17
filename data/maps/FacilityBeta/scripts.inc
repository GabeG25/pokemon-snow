FacilityBeta_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ FACILITY BETA — F21 ASHER #5 + F22 TYRELL #1 back-to-back no-heal
@ ═══════════════════════════════════════════════════════════════
@ Per v17 §20: Asher gates the path to Tyrell on Beta Roof. After
@ Asher's loss his working-for-Veil mask cracks — he moves aside
@ without apology but the player can feel the shift. Tyrell's own
@ "educating" battle follows with NO HEAL between them. F21 is the
@ first fight where Asher's starter uses its custom HA (Speed Boost
@ Blaziken / Sheer Force Swampert / Protean Sceptile).
@
@ STUB: Facility Beta is a single-room map reusing Devon Corp 2F
@ layout. Full v17 §18 Beta design calls for 2 floors + roof, 22
@ grunts, F19 Mika / F20 Xenon preceding F21. Those are CEO-creative.

@ F21 Asher — starter-keyed A/B/C. LOCALID 2.

FacilityBeta_EventScript_Asher::
	lock
	faceplayer
	msgbox FacilityBeta_Text_AsherIntro, MSGBOX_DEFAULT
	closemessage
	compare VAR_STARTER_MON, 0
	goto_if_eq FacilityBeta_EventScript_AsherVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq FacilityBeta_EventScript_AsherVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq FacilityBeta_EventScript_AsherVariantC
	release
	end

FacilityBeta_EventScript_AsherVariantA::
	trainerbattle_no_intro TRAINER_SNOW_F21_ASHER_A, FacilityBeta_Text_AsherDefeat
	goto FacilityBeta_EventScript_AsherAfterBattle

FacilityBeta_EventScript_AsherVariantB::
	trainerbattle_no_intro TRAINER_SNOW_F21_ASHER_B, FacilityBeta_Text_AsherDefeat
	goto FacilityBeta_EventScript_AsherAfterBattle

FacilityBeta_EventScript_AsherVariantC::
	trainerbattle_no_intro TRAINER_SNOW_F21_ASHER_C, FacilityBeta_Text_AsherDefeat
	goto FacilityBeta_EventScript_AsherAfterBattle

FacilityBeta_EventScript_AsherAfterBattle::
	setflag FLAG_SNOW_BEAT_F21_ASHER
	msgbox FacilityBeta_Text_AsherRetreats, MSGBOX_DEFAULT
	closemessage
	applymovement 2, FacilityBeta_Movement_AsherStepsAside
	waitmovement 0
	release
	end

FacilityBeta_Movement_AsherStepsAside:
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

@ F22 Tyrell — blocked until F21 Asher is defeated.

FacilityBeta_EventScript_Tyrell::
	lockall
	goto_if_unset FLAG_SNOW_BEAT_F21_ASHER, FacilityBeta_EventScript_TyrellAsherBlocking
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

FacilityBeta_EventScript_TyrellAsherBlocking::
	msgbox FacilityBeta_Text_TyrellAsherFirst, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

FacilityBeta_Text_AsherIntro:
	.string "ASHER: Stop right there.\p"
	.string "{PLAYER}. I knew you'd come.\n"
	.string "I told TYRELL you would.\p"
	.string "He didn't believe me.\p"
	.string "Said you'd give up after\n"
	.string "DRAGONFORGE. Said you were\l"
	.string "like PRIYO. Safe.\p"
	.string "You're not safe.\p"
	.string "That's the one thing I've\n"
	.string "had right about you since\l"
	.string "DAWNFLAKE.\p"
	.string "If you want TYRELL? Through\n"
	.string "me first.\p"
	.string "Full team. This isn't a\n"
	.string "friendly check-in anymore.$"

FacilityBeta_Text_AsherDefeat:
	.string "ASHER: ...Figures.$"

FacilityBeta_Text_AsherRetreats:
	.string "ASHER: Go.\p"
	.string "I'm not going to stop you.\n"
	.string "I don't even know why I\l"
	.string "thought I could.\p"
	.string "TYRELL's back there. He's\n"
	.string "waiting for you.\p"
	.string "Just... finish it, {PLAYER}.$"

FacilityBeta_Text_TyrellAsherFirst:
	.string "ASHER stands between you and\n"
	.string "TYRELL's chamber.\p"
	.string "Deal with him first.$"

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
