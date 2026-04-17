PinegroveCity_PokemonCenter_1F_MapScripts::
	.byte 0

PinegroveCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PinegroveCity_PokemonCenter_1F_EventScript_Botanist::
	lock
	faceplayer
	msgbox PinegroveCity_PokemonCenter_1F_Text_Botanist, MSGBOX_DEFAULT
	release
	end

PinegroveCity_PokemonCenter_1F_Text_Botanist:
	.string "BOTANIST: The pinegroves outside\n"
	.string "town are a microclimate.\p"
	.string "The heat from the volcanic vents\n"
	.string "lets conifers survive the snow.\p"
	.string "It's beautiful, but fragile.$"
