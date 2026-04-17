SolaceTown_PokemonCenter_1F_MapScripts::
	.byte 0

SolaceTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SolaceTown_PokemonCenter_1F_EventScript_OldFarmer::
	lock
	faceplayer
	msgbox SolaceTown_PokemonCenter_1F_Text_OldFarmer, MSGBOX_DEFAULT
	release
	end

SolaceTown_PokemonCenter_1F_Text_OldFarmer:
	.string "OLD FARMER: The permafrost thaws\n"
	.string "in SOLACE every spring.\p"
	.string "My PHANPY herd plows the fields\n"
	.string "soft enough for GROUND seeds.\p"
	.string "ERIN says the thaw's getting\n"
	.string "shorter. I believe her.$"
