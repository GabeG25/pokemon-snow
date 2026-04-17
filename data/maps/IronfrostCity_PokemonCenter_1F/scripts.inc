IronfrostCity_PokemonCenter_1F_MapScripts::
	.byte 0

IronfrostCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

IronfrostCity_PokemonCenter_1F_EventScript_Miner::
	lock
	faceplayer
	msgbox IronfrostCity_PokemonCenter_1F_Text_Miner, MSGBOX_DEFAULT
	release
	end

IronfrostCity_PokemonCenter_1F_Text_Miner:
	.string "MINER: The cave's been acting\n"
	.string "strange lately.\p"
	.string "We hit an ice vein last week,\n"
	.string "and something moved inside it.\p"
	.string "Wasn't a POKEMON. Wasn't a rock.\n"
	.string "It was... watching.$"
