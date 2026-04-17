PokemonLeague_VespersRoom_MapScripts::
	.byte 0

PokemonLeague_VespersRoom_EventScript_Vesper::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F32_VESPER, PokemonLeague_VespersRoom_EventScript_VesperDefeated
	msgbox PokemonLeague_VespersRoom_Text_VesperIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F32_VESPER, PokemonLeague_VespersRoom_Text_VesperDefeat
	setflag FLAG_SNOW_BEAT_F32_VESPER
	msgbox PokemonLeague_VespersRoom_Text_VesperPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_VespersRoom_EventScript_VesperDefeated::
	msgbox PokemonLeague_VespersRoom_Text_VesperPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_VespersRoom_Text_VesperIntro:
	.string "VESPER: Four trainers in the\n"
	.string "last decade cleared BRYNN.\p"
	.string "Two made it past me.\n"
	.string "Neither reached the throne.\p"
	.string "I don't expect you to do better.$"

PokemonLeague_VespersRoom_Text_VesperDefeat:
	.string "VESPER: ...\n"
	.string "Huh.$"

PokemonLeague_VespersRoom_Text_VesperPostBattle:
	.string "VESPER: REVERIE will see through\n"
	.string "your confidence.\p"
	.string "The dead know every trick.$"
