DawnflakeTown_EvergreensLab_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Prof. Evergreen (inside lab) — Starter gift
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_Evergreen::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_EvergreensLab_EventScript_EvergreenAfterStarter
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenIntro, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter, MSGBOX_DEFAULT
	clearflag FLAG_SNOW_HIDE_DAWNFLAKE_ASHER
	release
	end

DawnflakeTown_EvergreensLab_EventScript_EvergreenAfterStarter::
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EvergreensLab_EventScript_EvergreenPostRival
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenWaitForRival, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_EvergreenPostRival::
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenHeadSouth, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_Aide::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_Aide, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_Text_EvergreenIntro:
	.string "PROF. EVERGREEN: {PLAYER}!\n"
	.string "You're finally here.\p"
	.string "Welcome to my lab. I've been\n"
	.string "studying how Pokemon adapt to\l"
	.string "Boralyss's endless winter.\p"
	.string "Fascinating work, really.\p"
	.string "But today is about YOU.\p"
	.string "Three Pokemon were shipped to\n"
	.string "me from a warmer region in the\l"
	.string "south. They've never felt cold\l"
	.string "like ours.\p"
	.string "They need a trainer who can help\n"
	.string "them adapt. I think you might\l"
	.string "be that trainer.\p"
	.string "Go on - take a look.$"

DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Good choice.\p"
	.string "That one suits you.\p"
	.string "Now, a word of warning.\p"
	.string "Asher was here earlier - he\n"
	.string "picked one too. He's been waiting\l"
	.string "outside to challenge you.\p"
	.string "Be gentle with him, {PLAYER}.\n"
	.string "He's been through a lot.$"

DawnflakeTown_EvergreensLab_Text_EvergreenWaitForRival:
	.string "PROF. EVERGREEN: Asher is outside.\p"
	.string "Please - talk to him before you\n"
	.string "leave town. He won't admit it,\l"
	.string "but he needs this.$"

DawnflakeTown_EvergreensLab_Text_EvergreenHeadSouth:
	.string "PROF. EVERGREEN: Route 1 is south\n"
	.string "of town. That's where your journey\l"
	.string "really begins.\p"
	.string "Autumn was out there this morning\n"
	.string "studying wildlife.\p"
	.string "Take care of yourself out there.\n"
	.string "Boralyss isn't as gentle as it\l"
	.string "looks - no matter what the\l"
	.string "citizens tell you.$"

DawnflakeTown_EvergreensLab_Text_Aide:
	.string "AIDE: Professor Evergreen has\n"
	.string "been working nonstop lately.\p"
	.string "Ever since the weather changed,\n"
	.string "he's been obsessed with\l"
	.string "documenting the adaptations.\p"
	.string "Between you and me - I think he\n"
	.string "knows more than he lets on.$"
