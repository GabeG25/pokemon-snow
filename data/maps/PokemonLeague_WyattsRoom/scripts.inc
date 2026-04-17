PokemonLeague_WyattsRoom_MapScripts::
	.byte 0

PokemonLeague_WyattsRoom_EventScript_Wyatt::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F34_WYATT, PokemonLeague_WyattsRoom_EventScript_WyattDefeated
	msgbox PokemonLeague_WyattsRoom_Text_WyattIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F34_WYATT, PokemonLeague_WyattsRoom_Text_WyattDefeat
	setflag FLAG_SNOW_BEAT_F34_WYATT
	msgbox PokemonLeague_WyattsRoom_Text_WyattPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_WyattsRoom_EventScript_WyattDefeated::
	msgbox PokemonLeague_WyattsRoom_Text_WyattPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_WyattsRoom_Text_WyattIntro:
	.string "WYATT: Lightning doesn't\n"
	.string "announce itself.\p"
	.string "Neither do I.$"

PokemonLeague_WyattsRoom_Text_WyattDefeat:
	.string "WYATT: You held the ground.$"

PokemonLeague_WyattsRoom_Text_WyattPostBattle:
	.string "WYATT: TYRIM is through the\n"
	.string "north door.\p"
	.string "He knew you were coming long\n"
	.string "before we did.$"
