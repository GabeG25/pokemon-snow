DawnflakeTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DawnflakeTown_OnTransition
	.byte 0

DawnflakeTown_OnTransition::
	goto_if_set FLAG_ADVENTURE_STARTED, DawnflakeTown_OnTransition_End
	@ First time entering — trigger intro cutscene
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
	.string "...\p"
	.string "{PLAYER}!\p"
	.string "MOM (from inside): {PLAYER},\n"
	.string "are you up? Professor Evergreen\l"
	.string "is waiting for you!$"

DawnflakeTown_Text_IntroCard2:
	.string "You step out of your house into\n"
	.string "the familiar Dawnflake morning.\p"
	.string "The snow is fresh. The air is\n"
	.string "crisp. Your breath fogs in\l"
	.string "front of you.\p"
	.string "Today's the day. You're finally\n"
	.string "getting your first Pokemon.$"

DawnflakeTown_Text_IntroCard3:
	.string "MOM'S VOICE: I left the CANDY BOX\n"
	.string "on the path outside - something\l"
	.string "small to help you along the way.\p"
	.string "Now GO - Professor Evergreen's\n"
	.string "lab is the big building to the\l"
	.string "south. He's been expecting you.$"

@ ═══════════════════════════════════════════════════════════
@ Asher F1 — First rival battle, grief & armor
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
@ Candy Box — Key item under the bed
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
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_Text_AsherChallenge:
	.string "ASHER: Oh. You.\p"
	.string "The professor said you'd pick\n"
	.string "one of the outsider Pokemon today.\p"
	.string "Figures.\p"
	.string "Look - I don't do friendship\n"
	.string "speeches. You're not my friend.\p"
	.string "I battle. You battle. One of us\n"
	.string "walks away feeling stupid.\p"
	.string "My starter has the type\n"
	.string "advantage. I made sure of it.\p"
	.string "Let's go.$"

DawnflakeTown_Text_AsherDefeat:
	.string "ASHER: ...tch.$"

DawnflakeTown_Text_AsherPostBattle:
	.string "ASHER: ...\p"
	.string "Whatever. Beginner's luck.\p"
	.string "I don't know what you're\n"
	.string "smiling about. You think this\l"
	.string "is a game? That the region's\l"
	.string "just handing out adventures?\p"
	.string "It isn't.\p"
	.string "...\p"
	.string "Forget it. I'm not sticking\n"
	.string "around to hear you gloat.\p"
	.string "I've got training to do.\n"
	.string "Real training.\p"
	.string "Don't get used to winning,\n"
	.string "{PLAYER}.$"

DawnflakeTown_Text_AsherPostDefeat:
	.string "ASHER: What, you want a rematch?\p"
	.string "Come find me on the road.\n"
	.string "I'll be the one who's actually\l"
	.string "getting stronger.$"

DawnflakeTown_Text_CandyBoxFound:
	.string "{PLAYER} found the CANDY BOX!\p"
	.string "A small wooden box left by mom.\n"
	.string "It's somehow always full of\l"
	.string "Rare Candies...\p"
	.string "A note reads: 'They won't let\n"
	.string "you outpace the challenge ahead,\l"
	.string "but they'll help you keep up.\l"
	.string "- Mom'$"
