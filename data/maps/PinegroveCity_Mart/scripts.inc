PinegroveCity_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

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
