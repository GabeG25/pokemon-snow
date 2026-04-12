IceharborCity_MapScripts::
	.byte 0

IceharborCity_EventScript_GymLeaderMarina::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F13_MARINA, IceharborCity_EventScript_MarinaDefeated
	goto_if_unset FLAG_BADGE04_GET, IceharborCity_EventScript_MarinaNeedBadge
	msgbox IceharborCity_Text_MarinaIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F13_MARINA, IceharborCity_Text_MarinaDefeat
	setflag FLAG_SNOW_BEAT_F13_MARINA
	setflag FLAG_BADGE05_GET
	msgbox IceharborCity_Text_MarinaPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM20, 1
	msgbox IceharborCity_Text_MarinaGiveTM, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_MarinaDefeated::
	msgbox IceharborCity_Text_MarinaPostBattle, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_MarinaNeedBadge::
	msgbox IceharborCity_Text_MarinaLocked, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_BlackSludgeNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_BLACK_SLUDGE, IceharborCity_EventScript_BlackSludgeDone
	msgbox IceharborCity_Text_BlackSludgeIntro, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_SLUDGE, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_BLACK_SLUDGE
	msgbox IceharborCity_Text_BlackSludgeGiven, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_BlackSludgeDone::
	msgbox IceharborCity_Text_BlackSludgePost, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_SailorTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, IceharborCity_EventScript_SailorLocked
	msgbox IceharborCity_Text_SailorIntro, MSGBOX_DEFAULT
	msgbox IceharborCity_Text_SailorOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq IceharborCity_EventScript_SailorTeach
	msgbox IceharborCity_Text_SailorDecline, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_SailorTeach::
	checkmoney 4000
	compare VAR_RESULT, FALSE
	goto_if_eq IceharborCity_EventScript_SailorNoMoney
	removemoney 4000
	setvar VAR_0x8005, MOVE_ICE_PUNCH
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq IceharborCity_EventScript_SailorCancel
	msgbox IceharborCity_Text_SailorTaught, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_SailorCancel::
	msgbox IceharborCity_Text_SailorDecline, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_SailorNoMoney::
	msgbox IceharborCity_Text_SailorNoMoney, MSGBOX_DEFAULT
	release
	end

IceharborCity_EventScript_SailorLocked::
	msgbox IceharborCity_Text_SailorLocked, MSGBOX_DEFAULT
	release
	end

IceharborCity_Text_MarinaIntro:
	.string "MARINA: The half-frozen harbor\n"
	.string "doesn't stop me - and neither\l"
	.string "will you!\p"
	.string "Let's see what you've got.$"

IceharborCity_Text_MarinaDefeat:
	.string "MARINA: A strong current runs\n"
	.string "through you.$"

IceharborCity_Text_MarinaPostBattle:
	.string "MARINA: You've earned the\n"
	.string "GLACIER BADGE.$"

IceharborCity_Text_MarinaGiveTM:
	.string "MARINA: TM20 contains SCALD.\n"
	.string "Hot water in an icy world.$"

IceharborCity_Text_MarinaLocked:
	.string "MARINA: Four badges first, trainer.$"

IceharborCity_Text_BlackSludgeIntro:
	.string "FISHERMAN: This washed up on the\n"
	.string "shore last tide.\p"
	.string "Nasty stuff - most POKEMON can't\n"
	.string "stand it. But I've seen Poison-types\l"
	.string "that can't get enough.\p"
	.string "Take it off my hands, will you?$"

IceharborCity_Text_BlackSludgeGiven:
	.string "{PLAYER} received the BLACK SLUDGE!$"

IceharborCity_Text_BlackSludgePost:
	.string "FISHERMAN: Catch anything good?$"

IceharborCity_Text_SailorIntro:
	.string "SAILOR: I've sailed every ocean\n"
	.string "and fought in every port.\p"
	.string "My POKEMON learned moves you\n"
	.string "won't find in any textbook.$"

IceharborCity_Text_SailorOffer:
	.string "SAILOR: I can teach ICE PUNCH.\n"
	.string "Costs 4000 yen. Interested?$"

IceharborCity_Text_SailorDecline:
	.string "SAILOR: Your loss, matey.$"

IceharborCity_Text_SailorNoMoney:
	.string "SAILOR: Not enough coin.$"

IceharborCity_Text_SailorLocked:
	.string "SAILOR: Come back with five badges.$"

IceharborCity_Text_SailorTaught:
	.string "SAILOR: ICE PUNCH taught. Sail safe!$"
