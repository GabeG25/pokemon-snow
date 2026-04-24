PowderpathVillage_Mart_MapScripts::
	.byte 0

PowderpathVillage_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart PowderpathVillage_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PowderpathVillage_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Youngster — enthusiastic trainer-kid, explains the stock
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_Mart_EventScript_Youngster::
	lock
	faceplayer
	msgbox PowderpathVillage_Mart_Text_Youngster, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Mart_Text_Youngster:
	.string "YOUNGSTER: Hey, you're a new\n"
	.string "trainer, right? I can tell.\p"
	.string "Okay, listen - POTIONS you know.\n"
	.string "POKE BALLS obviously. ANTIDOTE\l"
	.string "for the ZUBAT you're gonna fight\l"
	.string "in the caves.\p"
	.string "REPEL is the one most kids skip.\n"
	.string "Don't. The trail up to ICESPIRE\l"
	.string "is a SNORUNT convention.\p"
	.string "Trust me. I've been through.$"
