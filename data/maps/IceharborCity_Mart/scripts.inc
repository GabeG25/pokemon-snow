IceharborCity_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

IceharborCity_Mart_EventScript_Captain::
	lock
	faceplayer
	msgbox IceharborCity_Mart_Text_Captain, MSGBOX_DEFAULT
	release
	end

IceharborCity_Mart_Text_Captain:
	.string "FAT MAN: Skipper of the FERRY.\p"
	.string "We used to run daily trips to\n"
	.string "DRIFTROCK ISLE.\p"
	.string "Now it's weekly. The sea's\n"
	.string "colder every year.\p"
	.string "My old KINGLER can barely feel\n"
	.string "its pincers some days.$"
