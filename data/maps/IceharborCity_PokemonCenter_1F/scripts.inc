IceharborCity_PokemonCenter_1F_MapScripts::
	.byte 0

IceharborCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

IceharborCity_PokemonCenter_1F_EventScript_Dockhand::
	lock
	faceplayer
	msgbox IceharborCity_PokemonCenter_1F_Text_Dockhand, MSGBOX_DEFAULT
	release
	end

IceharborCity_PokemonCenter_1F_Text_Dockhand:
	.string "SAILOR: DRIFTROCK ISLE is open\n"
	.string "again for the first time in\l"
	.string "years.\p"
	.string "MARINA reopened the route after\n"
	.string "the rangers cleared the\l"
	.string "CLOYSTER nests.\p"
	.string "Bring a WATER type if you go.$"
