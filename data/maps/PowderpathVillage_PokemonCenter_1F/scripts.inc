PowderpathVillage_PokemonCenter_1F_MapScripts::
	.byte 0

PowderpathVillage_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

PowderpathVillage_PokemonCenter_1F_EventScript_Gentleman::
	lock
	faceplayer
	msgbox PowderpathVillage_PokemonCenter_1F_Text_Gentleman, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_PokemonCenter_1F_Text_Gentleman:
	.string "Heading up into the pass? Good.\n"
	.string "Rest here before you try.\p"
	.string "ICESPIRE TOWN is over the ridge,\n"
	.string "but the climb eats trainers who\l"
	.string "don't top off first.$"
