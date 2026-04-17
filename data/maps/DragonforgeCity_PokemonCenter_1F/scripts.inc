DragonforgeCity_PokemonCenter_1F_MapScripts::
	.byte 0

DragonforgeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, 1
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DragonforgeCity_PokemonCenter_1F_EventScript_Analyst::
	lock
	faceplayer
	msgbox DragonforgeCity_PokemonCenter_1F_Text_Analyst, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_PokemonCenter_1F_Text_Analyst:
	.string "ANALYST: Facility ALPHA sits on\n"
	.string "the east ridge.\p"
	.string "Locked pre-Gym 8, officially.\n"
	.string "Unofficially, nobody's allowed\l"
	.string "near it at all.\p"
	.string "PRIYO keeps asking the DIRECTOR\n"
	.string "for inspection access.\p"
	.string "Still waiting.$"
