DawnflakeTown_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Prof. Evergreen starter gift (talk to NPC in town)
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_Evergreen::
	lock
	faceplayer
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_EventScript_EvergreenAlreadyGotStarter
	msgbox DawnflakeTown_Text_EvergreenIntro, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	msgbox DawnflakeTown_Text_EvergreenGotStarter, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_EvergreenAlreadyGotStarter::
	msgbox DawnflakeTown_Text_EvergreenAlready, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_Text_EvergreenIntro:
	.string "PROF. EVERGREEN: Ah, {PLAYER}!\n"
	.string "Right on time.\p"
	.string "I've been studying how Pokémon adapt\n"
	.string "to this endless winter…\p"
	.string "But today is about YOU.\n"
	.string "I have three Pokémon here -\l"
	.string "they were brought in from warmer\l"
	.string "regions for a research program.\p"
	.string "Any of them would make a fine\n"
	.string "partner for your journey.\p"
	.string "Go on - take a look!$"

DawnflakeTown_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Excellent choice!\p"
	.string "That Pokémon is now yours.\n"
	.string "Take good care of it.\p"
	.string "Oh - and your rivals Asher and Autumn\n"
	.string "are eager to meet you outside.\p"
	.string "Head out when you're ready!$"

DawnflakeTown_Text_EvergreenAlready:
	.string "PROF. EVERGREEN: How is your\n"
	.string "Pokémon treating you?\p"
	.string "Head south to Route 1 when you're\n"
	.string "ready to begin your journey.$"
