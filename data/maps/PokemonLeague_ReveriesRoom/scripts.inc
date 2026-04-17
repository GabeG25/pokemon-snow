PokemonLeague_ReveriesRoom_MapScripts::
	.byte 0

PokemonLeague_ReveriesRoom_EventScript_Reverie::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F33_REVERIE, PokemonLeague_ReveriesRoom_EventScript_ReverieDefeated
	msgbox PokemonLeague_ReveriesRoom_Text_ReverieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F33_REVERIE, PokemonLeague_ReveriesRoom_Text_ReverieDefeat
	setflag FLAG_SNOW_BEAT_F33_REVERIE
	msgbox PokemonLeague_ReveriesRoom_Text_ReveriePostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_ReveriesRoom_EventScript_ReverieDefeated::
	msgbox PokemonLeague_ReveriesRoom_Text_ReveriePostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_ReveriesRoom_Text_ReverieIntro:
	.string "REVERIE: I dreamed of you last\n"
	.string "week, {PLAYER}.\p"
	.string "You lost.\n"
	.string "Let me show you how.$"

PokemonLeague_ReveriesRoom_Text_ReverieDefeat:
	.string "REVERIE: Dreams are imperfect.\n"
	.string "This one was wrong.$"

PokemonLeague_ReveriesRoom_Text_ReveriePostBattle:
	.string "REVERIE: WYATT strikes without\n"
	.string "warning. Be ready.$"
