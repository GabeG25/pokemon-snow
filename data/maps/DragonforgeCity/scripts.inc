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
