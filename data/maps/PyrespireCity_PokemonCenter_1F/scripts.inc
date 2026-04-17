PyrespireCity_PokemonCenter_1F_MapScripts::
	.byte 0

PyrespireCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PyrespireCity_PokemonCenter_1F_EventScript_Vulcanist::
	lock
	faceplayer
	msgbox PyrespireCity_PokemonCenter_1F_Text_Vulcanist, MSGBOX_DEFAULT
	release
	end

PyrespireCity_PokemonCenter_1F_Text_Vulcanist:
	.string "VULCANIST: PYRESPIRE is the only\n"
	.string "warm city in BORALYSS.\p"
	.string "The volcano runs hot year-round.\n"
	.string "MAGMAR and TORKOAL nest on the\l"
	.string "slopes.\p"
	.string "SCORCH says Facility Beta is\n"
	.string "stealing the geothermal heat.$"
