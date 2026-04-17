PinegroveCity_Mart_MapScripts::
	.byte 0

PinegroveCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart PinegroveCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PinegroveCity_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

PinegroveCity_Mart_EventScript_Shopper::
	lock
	faceplayer
	msgbox PinegroveCity_Mart_Text_Shopper, MSGBOX_DEFAULT
	release
	end

PinegroveCity_Mart_Text_Shopper:
	.string "BUG CATCHER: Did you know JOLTIK\n"
	.string "can survive on static electricity\l"
	.string "from clothes?\p"
	.string "In the snow, they cling to\n"
	.string "travelers to stay warm.\p"
	.string "Cute... or horrifying!$"
