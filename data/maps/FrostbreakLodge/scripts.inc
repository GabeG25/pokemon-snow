FrostbreakLodge_MapScripts::
	.byte 0

FrostbreakLodge_EventScript_ShellBellNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_SHELL_BELL, FrostbreakLodge_EventScript_ShellBellDone
	msgbox FrostbreakLodge_Text_ShellBellIntro, MSGBOX_DEFAULT
	giveitem ITEM_SHELL_BELL, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_SHELL_BELL
	msgbox FrostbreakLodge_Text_ShellBellGiven, MSGBOX_DEFAULT
	release
	end

FrostbreakLodge_EventScript_ShellBellDone::
	msgbox FrostbreakLodge_Text_ShellBellPost, MSGBOX_DEFAULT
	release
	end

@ Frostbreak Lodge specialty shop (v17 §16, 8 items) — mid-game pivot
@ away from standard Poke Mart ceiling. Prices use item defaults
@ (spec-prescribed prices documented in v17 §16 for future migration
@ to a custom pricing script if needed).
FrostbreakLodge_EventScript_Shopkeeper::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FrostbreakLodge_Shop_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FrostbreakLodge_Shop_Items:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_LUM_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_POKE_DOLL
	pokemartlistend

FrostbreakLodge_EventScript_TM18NPC::
	lock
	faceplayer
	msgbox FrostbreakLodge_Text_TM18Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM18, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_TM18_REST
	msgbox FrostbreakLodge_Text_TM18Given, MSGBOX_DEFAULT
	release
	end

FrostbreakLodge_Text_ShellBellIntro:
	.string "MOUNTAINEER: I found this on the\n"
	.string "peak last winter.\p"
	.string "Every time my POKEMON lands a hit,\n"
	.string "this bell chimes and they perk\l"
	.string "right up.\p"
	.string "I've got my own recovery methods\n"
	.string "up here - you take it for the\l"
	.string "road ahead.$"

FrostbreakLodge_Text_ShellBellGiven:
	.string "{PLAYER} received the SHELL BELL!$"

FrostbreakLodge_Text_ShellBellPost:
	.string "MOUNTAINEER: Stay warm out there.$"

FrostbreakLodge_Text_TM18Intro:
	.string "OLD CLIMBER: A trainer needs\n"
	.string "rest more than medals.\p"
	.string "Take this. I can't use it at\n"
	.string "this altitude anymore.$"

FrostbreakLodge_Text_TM18Given:
	.string "{PLAYER} received TM18 REST!$"
