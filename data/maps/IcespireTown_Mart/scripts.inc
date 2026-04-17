IcespireTown_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

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
