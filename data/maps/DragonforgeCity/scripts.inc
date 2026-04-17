DragonforgeCity_MapScripts::
	.byte 0

DragonforgeCity_EventScript_GymLeaderPriyo::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F16_PRIYO, DragonforgeCity_EventScript_PriyoDefeated
	goto_if_unset FLAG_BADGE05_GET, DragonforgeCity_EventScript_PriyoNeedBadge
	msgbox DragonforgeCity_Text_PriyoIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F16_PRIYO, DragonforgeCity_Text_PriyoDefeat
	setflag FLAG_SNOW_BEAT_F16_PRIYO
	setflag FLAG_BADGE06_GET
	msgbox DragonforgeCity_Text_PriyoPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM27, 1
	msgbox DragonforgeCity_Text_PriyoGiveTM, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_PriyoDefeated::
	msgbox DragonforgeCity_Text_PriyoPostBattle, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_PriyoNeedBadge::
	msgbox DragonforgeCity_Text_PriyoLocked, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_ProfessorsAideTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE06_GET, DragonforgeCity_EventScript_AideLocked
	msgbox DragonforgeCity_Text_AideIntro, MSGBOX_DEFAULT
	msgbox DragonforgeCity_Text_AideOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq DragonforgeCity_EventScript_AideTeach
	msgbox DragonforgeCity_Text_AideDecline, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_AideTeach::
	checkmoney 5000
	compare VAR_RESULT, FALSE
	goto_if_eq DragonforgeCity_EventScript_AideNoMoney
	removemoney 5000
	setvar VAR_0x8005, MOVE_KNOCK_OFF
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq DragonforgeCity_EventScript_AideCancel
	msgbox DragonforgeCity_Text_AideTaught, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_AideCancel::
	msgbox DragonforgeCity_Text_AideDecline, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_AideNoMoney::
	msgbox DragonforgeCity_Text_AideNoMoney, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_EventScript_AideLocked::
	msgbox DragonforgeCity_Text_AideLocked, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_Text_PriyoIntro:
	.string "PRIYO: Welcome to DRAGONFORGE.\p"
	.string "Dragons forge themselves in fire\n"
	.string "and frost alike.\p"
	.string "My POKEMON are no exception.$"

DragonforgeCity_Text_PriyoDefeat:
	.string "PRIYO: Well fought. Well won.$"

DragonforgeCity_Text_PriyoPostBattle:
	.string "PRIYO: You've earned the\n"
	.string "DRAGONHEART BADGE.$"

DragonforgeCity_Text_PriyoGiveTM:
	.string "PRIYO: TM27 contains DRAGON CLAW.\n"
	.string "Use it wisely.$"

DragonforgeCity_Text_PriyoLocked:
	.string "PRIYO: Five badges first.$"

DragonforgeCity_Text_AideIntro:
	.string "PROFESSOR'S AIDE: Professor Evergreen\n"
	.string "asked me to share some of his\l"
	.string "research findings.\p"
	.string "These techniques are cutting-edge.$"

DragonforgeCity_Text_AideOffer:
	.string "AIDE: I can teach KNOCK OFF.\n"
	.string "Costs 5000 yen. Interested?$"

DragonforgeCity_Text_AideDecline:
	.string "AIDE: Perhaps another time.$"

DragonforgeCity_Text_AideNoMoney:
	.string "AIDE: Insufficient funds.$"

DragonforgeCity_Text_AideLocked:
	.string "AIDE: I can only share these moves\n"
	.string "with champions - come back when\l"
	.string "you have six badges.$"

DragonforgeCity_Text_AideTaught:
	.string "AIDE: KNOCK OFF taught successfully.$"

@ ===== F15 Autumn — post Gym 5 Dragonforge, Lv57 team (v17 §20) =====
@ LOCALID 3. After F10 on R7 she said she was stepping back. She
@ didn't fully. Still wanting one more fight. Voice: warmer than F10,
@ less giddy than F5, more reflective.

DragonforgeCity_EventScript_AutumnF15::
	lock
	faceplayer
	msgbox DragonforgeCity_Text_AutumnF15Intro, MSGBOX_DEFAULT
	closemessage
	compare VAR_STARTER_MON, 0
	goto_if_eq DragonforgeCity_EventScript_AutumnF15VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq DragonforgeCity_EventScript_AutumnF15VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq DragonforgeCity_EventScript_AutumnF15VariantC
	release
	end

DragonforgeCity_EventScript_AutumnF15VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F15_AUTUMN_A, DragonforgeCity_Text_AutumnF15Defeat
	goto DragonforgeCity_EventScript_AutumnF15AfterBattle

DragonforgeCity_EventScript_AutumnF15VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F15_AUTUMN_B, DragonforgeCity_Text_AutumnF15Defeat
	goto DragonforgeCity_EventScript_AutumnF15AfterBattle

DragonforgeCity_EventScript_AutumnF15VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F15_AUTUMN_C, DragonforgeCity_Text_AutumnF15Defeat
	goto DragonforgeCity_EventScript_AutumnF15AfterBattle

DragonforgeCity_EventScript_AutumnF15AfterBattle::
	setflag FLAG_SNOW_BEAT_F15_AUTUMN
	msgbox DragonforgeCity_Text_AutumnF15PostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 3, DragonforgeCity_Movement_AutumnF15Depart
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_DRAGONFORGE
	removeobject 3
	release
	end

DragonforgeCity_Movement_AutumnF15Depart:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

DragonforgeCity_Text_AutumnF15Intro:
	.string "AUTUMN: Hey.\p"
	.string "Don't look at me like that.\n"
	.string "I know. I said GALETOP was\l"
	.string "the last one.\p"
	.string "I lied. Apparently.\p"
	.string "{PLAYER}, I've been reading\n"
	.string "everything EVERGREEN sends.\l"
	.string "ASHER's in the VEIL CREST\l"
	.string "now. Did you know?\p"
	.string "I saw him on R11.\n"
	.string "I didn't say anything.\p"
	.string "You should know, though.\p"
	.string "One more fight. Really this\n"
	.string "time, probably.$"

DragonforgeCity_Text_AutumnF15Defeat:
	.string "AUTUMN: ...Yeah.$"

DragonforgeCity_Text_AutumnF15PostBattle:
	.string "AUTUMN: PYRESPIRE is south.\n"
	.string "R15's past that.\p"
	.string "If you see me there, it's\n"
	.string "the real last one.\p"
	.string "Be careful with ASHER,\n"
	.string "{PLAYER}. He'll be at BETA.\p"
	.string "He listens to you. He won't\n"
	.string "say it but he does.$"
