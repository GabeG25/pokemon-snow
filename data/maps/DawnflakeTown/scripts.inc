DawnflakeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DawnflakeTown_OnTransition
	.byte 0

DawnflakeTown_OnTransition::
	goto_if_set FLAG_ADVENTURE_STARTED, DawnflakeTown_OnTransition_End
	call DawnflakeTown_EventScript_IntroCutscene
DawnflakeTown_OnTransition_End::
	end

@ ═══════════════════════════════════════════════════════════
@ First-time intro cutscene
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_IntroCutscene::
	lockall
	msgbox DawnflakeTown_Text_IntroCard1, MSGBOX_DEFAULT
	msgbox DawnflakeTown_Text_IntroCard2, MSGBOX_DEFAULT
	msgbox DawnflakeTown_Text_IntroCard3, MSGBOX_DEFAULT
	releaseall
	return

DawnflakeTown_Text_IntroCard1:
	.string "MOM (calling from inside):\n"
	.string "{PLAYER}! You're awake?\p"
	.string "Professor Evergreen's been\n"
	.string "asking after you since sunrise.$"

DawnflakeTown_Text_IntroCard2:
	.string "The snow is fresh on the path.\p"
	.string "Your breath fogs in the morning\n"
	.string "air. Dawnflake Town is quiet\l"
	.string "the way only a small town can be.\p"
	.string "Today is the day you get your\n"
	.string "first Pokemon.$"

DawnflakeTown_Text_IntroCard3:
	.string "MOM'S VOICE: I left the CANDY BOX\n"
	.string "on the path - something small\l"
	.string "to help you keep up.\p"
	.string "Evergreen's lab is the big\n"
	.string "building to the south.\p"
	.string "Go on. He's waiting.$"

@ ═══════════════════════════════════════════════════════════
@ Asher F1 — First rival battle, grief and armor
@ ═══════════════════════════════════════════════════════════

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
	msgbox DawnflakeTown_Text_AsherPostDefeat, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Candy Box — gift from mom
@ ═══════════════════════════════════════════════════════════

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

@ ═══════════════════════════════════════════════════════════
@ Ambient villager
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_Villager::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EventScript_VillagerPostRival
	msgbox DawnflakeTown_Text_Villager, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_VillagerPostRival::
	msgbox DawnflakeTown_Text_VillagerPostRival, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_Text_AsherChallenge:
	.string "ASHER: Oh. You.\p"
	.string "Evergreen gave you one of the\n"
	.string "outsider Pokemon. Figures.\p"
	.string "I don't do friendship speeches.\n"
	.string "You're not my friend.\p"
	.string "I battle. You battle. One of us\n"
	.string "walks away feeling stupid.\p"
	.string "My starter beats yours. I made\n"
	.string "sure of it.\p"
	.string "Let's go.$"

DawnflakeTown_Text_AsherDefeat:
	.string "ASHER: ...tch.$"

DawnflakeTown_Text_AsherPostBattle:
	.string "ASHER: ...\p"
	.string "Whatever. Beginner's luck.\p"
	.string "You think this is a game?\n"
	.string "You think the region's just\l"
	.string "handing out adventures?\p"
	.string "It isn't. Not this one.\p"
	.string "I've got training to do.\n"
	.string "Real training.\p"
	.string "Don't get used to winning,\n"
	.string "{PLAYER}.$"

DawnflakeTown_Text_AsherPostDefeat:
	.string "ASHER: You want a rematch?\p"
	.string "Come find me on the road.\n"
	.string "I'll be the one actually getting\l"
	.string "stronger.$"

DawnflakeTown_Text_CandyBoxFound:
	.string "{PLAYER} found the CANDY BOX!\p"
	.string "A small wooden box, somehow\n"
	.string "always full of Rare Candies.\p"
	.string "A note tucked inside reads:\n"
	.string "'They won't let you outpace\l"
	.string "what's coming - but they'll\l"
	.string "help you keep up. - Mom'$"

DawnflakeTown_Text_Villager:
	.string "VILLAGER: Morning, dear.\p"
	.string "First Pokemon today? Oh, how\n"
	.string "exciting. Mind the snow - it's\l"
	.string "been coming down strange lately.\p"
	.string "Strange, and early.$"

DawnflakeTown_Text_VillagerPostRival:
	.string "VILLAGER: Poor Asher.\p"
	.string "He used to laugh, that boy.\n"
	.string "Back before the mountain went\l"
	.string "quiet.$"
