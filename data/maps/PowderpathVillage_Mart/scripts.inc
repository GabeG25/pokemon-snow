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

PowderpathVillage_Mart_EventScript_Boy::
	lock
	faceplayer
	msgbox PowderpathVillage_Mart_Text_Boy, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Mart_Text_Boy:
	.string "BURN HEAL in a snow region? You'd\n"
	.string "be surprised.\p"
	.string "The thermal vents past ICESPIRE\n"
	.string "run hot enough to singe a\l"
	.string "HOUNDOUR.$"
