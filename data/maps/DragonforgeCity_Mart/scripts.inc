DragonforgeCity_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

DragonforgeCity_Mart_EventScript_Traveler::
	lock
	faceplayer
	msgbox DragonforgeCity_Mart_Text_Traveler, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_Mart_Text_Traveler:
	.string "BATTLE GIRL: The Dept Store here\n"
	.string "stocks EVERY evolution stone.\p"
	.string "Five floors of gear. I've been\n"
	.string "saving up for months.\p"
	.string "Sure beats the basic mart in\n"
	.string "POWDERPATH.$"
