DawnflakeTown_MapScripts::
	.byte 0

DawnflakeTown_EventScript_Evergreen::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_EventScript_EvergreenAfterStarter
	msgbox DawnflakeTown_Text_EvergreenIntro, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	msgbox DawnflakeTown_Text_EvergreenGotStarter, MSGBOX_DEFAULT
	clearflag FLAG_SNOW_HIDE_DAWNFLAKE_ASHER
	release
	end

DawnflakeTown_EventScript_EvergreenAfterStarter::
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EventScript_EvergreenPostRival
	msgbox DawnflakeTown_Text_EvergreenWaitForRival, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_EvergreenPostRival::
	msgbox DawnflakeTown_Text_EvergreenHeadSouth, MSGBOX_DEFAULT
	release
	end

@ Asher F1: his ace has TYPE ADVANTAGE over player's starter
@ Player Treecko(0) -> Asher Torchic (A) [Fire beats Grass]
@ Player Torchic(1) -> Asher Mudkip  (B) [Water beats Fire]
@ Player Mudkip (2) -> Asher Treecko (C) [Grass beats Water]

DawnflakeTown_EventScript_Asher::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EventScript_AsherDefeated
	msgbox DawnflakeTown_Text_AsherChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq DawnflakeTown_EventScript_AsherVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq DawnflakeTown_EventScript_AsherVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq DawnflakeTown_EventScript_AsherVariantC
	end

DawnflakeTown_EventScript_AsherVariantA::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_A, DawnflakeTown_Text_AsherDefeat
	goto DawnflakeTown_EventScript_AsherAfterBattle
	end

DawnflakeTown_EventScript_AsherVariantB::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_B, DawnflakeTown_Text_AsherDefeat
	goto DawnflakeTown_EventScript_AsherAfterBattle
	end

DawnflakeTown_EventScript_AsherVariantC::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_C, DawnflakeTown_Text_AsherDefeat
	goto DawnflakeTown_EventScript_AsherAfterBattle
	end

DawnflakeTown_EventScript_AsherAfterBattle::
	setflag FLAG_SNOW_BEAT_F1_ASHER
	msgbox DawnflakeTown_Text_AsherPostBattle, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_AsherDefeated::
	msgbox DawnflakeTown_Text_AsherPostBattle, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_CandyBox::
	lock
	faceplayer
	giveitem ITEM_RARE_CANDY, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_CANDY_BOX
	msgbox DawnflakeTown_Text_CandyBoxFound, MSGBOX_DEFAULT
	removeobject VAR_LAST_TALKED
	release
	end

DawnflakeTown_Text_EvergreenIntro:
	.string "PROF. EVERGREEN: Ah, {PLAYER}!\n"
	.string "Right on time.\p"
	.string "Today is about YOU. I have three\n"
	.string "POKEMON from warmer regions here.\p"
	.string "Any of them would make a fine\n"
	.string "partner for your journey.\p"
	.string "Go on - take a look!$"

DawnflakeTown_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Excellent choice!\p"
	.string "Take good care of it.\p"
	.string "Asher is waiting outside to test\n"
	.string "your new partner.$"

DawnflakeTown_Text_EvergreenWaitForRival:
	.string "PROF. EVERGREEN: Asher is waiting\n"
	.string "for you outside.$"

DawnflakeTown_Text_EvergreenHeadSouth:
	.string "PROF. EVERGREEN: Head south to\n"
	.string "Route 1 when you're ready.\p"
	.string "Autumn is out there too - she'll\n"
	.string "teach you about catching POKEMON.$"

DawnflakeTown_Text_AsherChallenge:
	.string "ASHER: So Evergreen gave you one\n"
	.string "of his outsider POKEMON, huh?\p"
	.string "I picked one too - and mine has\n"
	.string "the TYPE ADVANTAGE over yours!\p"
	.string "Let's see if you can handle a REAL\n"
	.string "Boralyss trainer!$"

DawnflakeTown_Text_AsherDefeat:
	.string "ASHER: What?! How did I lose?!$"

DawnflakeTown_Text_AsherPostBattle:
	.string "ASHER: Tch... beginner's luck.\p"
	.string "I'll be training all the way up\n"
	.string "to the League. See you out there!$"

DawnflakeTown_Text_CandyBoxFound:
	.string "{PLAYER} found a CANDY BOX!\p"
	.string "A strange box always full of\n"
	.string "Rare Candies - capped by challenge.$"
