IcespireTown_PokemonCenter_1F_MapScripts::
	.byte 0

IcespireTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

IcespireTown_PokemonCenter_1F_EventScript_ShakenTrainer::
	lock
	faceplayer
	msgbox IcespireTown_PokemonCenter_1F_Text_ShakenTrainer, MSGBOX_DEFAULT
	release
	end

IcespireTown_PokemonCenter_1F_Text_ShakenTrainer:
	.string "SHAKEN TRAINER: SILVAN'S PIPLUP\n"
	.string "is faster than my starter.\p"
	.string "How is that even POSSIBLE? My\n"
	.string "POKEMON is fully evolved!\p"
	.string "...\p"
	.string "Something about the hail.\n"
	.string "Something about his ABILITY.\p"
	.string "Whatever it is, it's not fair.$"
