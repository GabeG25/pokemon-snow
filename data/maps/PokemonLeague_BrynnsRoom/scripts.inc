PokemonLeague_BrynnsRoom_MapScripts::
	.byte 0

PokemonLeague_BrynnsRoom_EventScript_Brynn::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F31_BRYNN, PokemonLeague_BrynnsRoom_EventScript_BrynnDefeated
	msgbox PokemonLeague_BrynnsRoom_Text_BrynnIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F31_BRYNN, PokemonLeague_BrynnsRoom_Text_BrynnDefeat
	setflag FLAG_SNOW_BEAT_F31_BRYNN
	msgbox PokemonLeague_BrynnsRoom_Text_BrynnPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_BrynnsRoom_EventScript_BrynnDefeated::
	msgbox PokemonLeague_BrynnsRoom_Text_BrynnPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_BrynnsRoom_Text_BrynnIntro:
	.string "BRYNN: Welcome to the BORALYSS\n"
	.string "LEAGUE, trainer.\p"
	.string "I am BRYNN. My BUG POKEMON\n"
	.string "survive the cold through sheer\l"
	.string "swarm-force.\p"
	.string "Show me yours can do better.$"

PokemonLeague_BrynnsRoom_Text_BrynnDefeat:
	.string "BRYNN: Impressive.\n"
	.string "The swarm yields.$"

PokemonLeague_BrynnsRoom_Text_BrynnPostBattle:
	.string "BRYNN: VESPER waits beyond.\n"
	.string "He is... not like me.$"
