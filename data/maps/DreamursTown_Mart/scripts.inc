DreamursTown_Mart_MapScripts::
	.byte 0

@ Clerk uses the shared Snow_PokeMart_EventScript_Clerk (snow_mart.inc).

DreamursTown_Mart_EventScript_Insomniac::
	lock
	faceplayer
	msgbox DreamursTown_Mart_Text_Insomniac, MSGBOX_DEFAULT
	release
	end

DreamursTown_Mart_Text_Insomniac:
	.string "WOMAN: I can't sleep anymore.\p"
	.string "Something's blocking the\n"
	.string "MUSHARNA dream fog at night.\p"
	.string "FRAN says the Fairy aura in\n"
	.string "DREAMURS is weakening.\p"
	.string "TEAM VEIL. It has to be.$"
