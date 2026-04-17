DreamursTown_PokemonCenter_1F_MapScripts::
	.byte 0

DreamursTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DreamursTown_PokemonCenter_1F_EventScript_Dreamer::
	lock
	faceplayer
	msgbox DreamursTown_PokemonCenter_1F_Text_Dreamer, MSGBOX_DEFAULT
	release
	end

DreamursTown_PokemonCenter_1F_Text_Dreamer:
	.string "LITTLE GIRL: Did you know?\n"
	.string "At night, the MUSHARNA floats\l"
	.string "over our rooftops.\p"
	.string "FRAN says it eats bad dreams.\n"
	.string "That's why kids sleep soundly\l"
	.string "in DREAMURS.$"
