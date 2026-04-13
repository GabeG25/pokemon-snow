IcespireTown_Mart_MapScripts::
	.byte 0

IcespireTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart IcespireTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
IcespireTown_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_NONE
	release
	end

IcespireTown_Mart_EventScript_ShopperWoman::
	lock
	faceplayer
	msgbox IcespireTown_Mart_Text_ShopperWoman, MSGBOX_DEFAULT
	release
	end

IcespireTown_Mart_Text_ShopperWoman:
	.string "SHOPPER: The DIRECTOR subsidizes\n"
	.string "ICE HEALS here, you know.\p"
	.string "He said no child in BORALYSS\n"
	.string "should ever lose a POKEMON to\l"
	.string "frostbite.\p"
	.string "He thinks of EVERYTHING.$"
