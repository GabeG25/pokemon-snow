SolaceTown_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

SolaceTown_Mart_EventScript_Rancher::
	lock
	faceplayer
	msgbox SolaceTown_Mart_Text_Rancher, MSGBOX_DEFAULT
	release
	end

SolaceTown_Mart_Text_Rancher:
	.string "RANCHER: Strangers in black\n"
	.string "coats asked about our barn\l"
	.string "last week.\p"
	.string "Wanted to 'inspect the\n"
	.string "geothermal vents.'\p"
	.string "ERIN ran them off with a single\n"
	.string "look from her DONPHAN.$"
