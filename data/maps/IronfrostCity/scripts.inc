IronfrostCity_MapScripts::
	.byte 0

@ ===== Gym 3 Copper (Steel type) =====

IronfrostCity_EventScript_GymLeaderCopper::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F9_COPPER, IronfrostCity_EventScript_CopperDefeated
	goto_if_unset FLAG_BADGE02_GET, IronfrostCity_EventScript_CopperNeedBadge2
	msgbox IronfrostCity_Text_CopperIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F9_COPPER, IronfrostCity_Text_CopperDefeat
	setflag FLAG_SNOW_BEAT_F9_COPPER
	setflag FLAG_BADGE03_GET
	msgbox IronfrostCity_Text_CopperPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM10, 1
	msgbox IronfrostCity_Text_CopperGiveTM, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_CopperDefeated::
	msgbox IronfrostCity_Text_CopperPostBattle, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_CopperNeedBadge2::
	msgbox IronfrostCity_Text_CopperLocked, MSGBOX_DEFAULT
	release
	end

@ ===== Fossil Revival NPC =====

IronfrostCity_EventScript_FossilRevivalNPC::
	lock
	faceplayer
	msgbox IronfrostCity_Text_FossilRevivalIntro, MSGBOX_DEFAULT
	release
	end

@ ===== Fossil Gift NPC (gives player's first fossil) =====

IronfrostCity_EventScript_FossilGiftNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_FOSSIL, IronfrostCity_EventScript_FossilGiftDone
	msgbox IronfrostCity_Text_FossilGiftIntro, MSGBOX_DEFAULT
	giveitem ITEM_ROOT_FOSSIL, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_FOSSIL
	msgbox IronfrostCity_Text_FossilGiftGiven, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_FossilGiftDone::
	msgbox IronfrostCity_Text_FossilGiftPost, MSGBOX_DEFAULT
	release
	end

@ ===== Geologist Move Tutor (Post-Gym 3) =====

IronfrostCity_EventScript_GeologistTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, IronfrostCity_EventScript_GeologistLocked
	msgbox IronfrostCity_Text_GeologistIntro, MSGBOX_DEFAULT
	msgbox IronfrostCity_Text_GeologistOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq IronfrostCity_EventScript_GeologistTeach
	msgbox IronfrostCity_Text_GeologistDecline, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_GeologistTeach::
	checkmoney 3000
	compare VAR_RESULT, FALSE
	goto_if_eq IronfrostCity_EventScript_GeologistNoMoney
	removemoney 3000
	setvar VAR_0x8005, MOVE_DIG
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq IronfrostCity_EventScript_GeologistCancel
	msgbox IronfrostCity_Text_GeologistTaught, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_GeologistCancel::
	msgbox IronfrostCity_Text_GeologistDecline, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_GeologistNoMoney::
	msgbox IronfrostCity_Text_GeologistNoMoney, MSGBOX_DEFAULT
	release
	end

IronfrostCity_EventScript_GeologistLocked::
	msgbox IronfrostCity_Text_GeologistLocked, MSGBOX_DEFAULT
	release
	end

@ ===== Text =====

IronfrostCity_Text_CopperIntro:
	.string "COPPER: Ah, another challenger.\p"
	.string "The iron and the frost - both\n"
	.string "unyielding. My POKEMON embody\l"
	.string "that same stubborn strength.\p"
	.string "Show me what metal you're made of.$"

IronfrostCity_Text_CopperDefeat:
	.string "COPPER: ...Steel bends, after all.$"

IronfrostCity_Text_CopperPostBattle:
	.string "COPPER: You've earned the\n"
	.string "IRONSHIELD BADGE.\p"
	.string "{PLAYER} received the\n"
	.string "IRONSHIELD BADGE!$"

IronfrostCity_Text_CopperGiveTM:
	.string "COPPER: And take this.\p"
	.string "TM10 contains FLASH CANNON.\n"
	.string "A blast of focused steel energy.\p"
	.string "It should serve you well.$"

IronfrostCity_Text_CopperLocked:
	.string "COPPER: You need the second badge\n"
	.string "before you can challenge me.$"

IronfrostCity_Text_FossilRevivalIntro:
	.string "LAB ASSISTANT: Welcome to the\n"
	.string "IRONFROST FOSSIL LAB.\p"
	.string "Bring us any fossils you find and\n"
	.string "we'll revive them into POKEMON.\p"
	.string "(Fossil revival coming soon.)$"

IronfrostCity_Text_FossilGiftIntro:
	.string "FOSSIL COLLECTOR: Hello, young\n"
	.string "trainer!\p"
	.string "I found too many fossils on my\n"
	.string "last dig. Would you take one?\p"
	.string "Here, have this ROOT FOSSIL.\n"
	.string "Take it to the lab to revive it!$"

IronfrostCity_Text_FossilGiftGiven:
	.string "{PLAYER} received the ROOT FOSSIL!$"

IronfrostCity_Text_FossilGiftPost:
	.string "FOSSIL COLLECTOR: Have you revived\n"
	.string "that fossil yet?$"

IronfrostCity_Text_GeologistIntro:
	.string "GEOLOGIST: I've studied the minerals\n"
	.string "of this cave for decades.\p"
	.string "The earth teaches patience -\n"
	.string "and power.$"

IronfrostCity_Text_GeologistOffer:
	.string "GEOLOGIST: I can teach DIG.\n"
	.string "Costs 3000 yen. Interested?$"

IronfrostCity_Text_GeologistDecline:
	.string "GEOLOGIST: As you wish.$"

IronfrostCity_Text_GeologistNoMoney:
	.string "GEOLOGIST: Not enough yen.$"

IronfrostCity_Text_GeologistLocked:
	.string "GEOLOGIST: Come back when you have\n"
	.string "three badges to your name.$"

IronfrostCity_Text_GeologistTaught:
	.string "GEOLOGIST: Done. DIG taught.$"
