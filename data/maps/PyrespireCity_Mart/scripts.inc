PyrespireCity_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

PyrespireCity_Mart_EventScript_EnergyPilgrim::
	lock
	faceplayer
	msgbox PyrespireCity_Mart_Text_EnergyPilgrim, MSGBOX_DEFAULT
	release
	end

PyrespireCity_Mart_Text_EnergyPilgrim:
	.string "BOY: I came here from IRONFROST\n"
	.string "to see the volcano.\p"
	.string "They said the heat could melt\n"
	.string "the permafrost for miles.\p"
	.string "If TEAM VEIL drains the caldera,\n"
	.string "all BORALYSS freezes.$"
