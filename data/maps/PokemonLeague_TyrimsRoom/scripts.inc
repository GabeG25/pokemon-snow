PokemonLeague_TyrimsRoom_MapScripts::
	.byte 0

PokemonLeague_TyrimsRoom_EventScript_Tyrim::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_TyrimsRoom_EventScript_TyrimDefeated
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F35_TYRIM, PokemonLeague_TyrimsRoom_Text_TyrimDefeat
	setflag FLAG_IS_CHAMPION
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimPostBattle, MSGBOX_DEFAULT
	@ TODO (CEO): Hall of Fame cutscene + credits roll go here.
	@ For now, release and let the player walk back out.
	release
	end

PokemonLeague_TyrimsRoom_EventScript_TyrimDefeated::
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimPostBattle, MSGBOX_DEFAULT
	release
	end

PokemonLeague_TyrimsRoom_Text_TyrimIntro:
	.string "TYRIM: Welcome, {PLAYER}.\p"
	.string "PRIYO speaks of you often.\n"
	.string "My little brother's eye for\l"
	.string "talent is sharp.\p"
	.string "He was right about you.\p"
	.string "Show me the trainer who stopped\n"
	.string "TYRELL.$"

PokemonLeague_TyrimsRoom_Text_TyrimDefeat:
	.string "TYRIM: Eight years.\n"
	.string "Eight years I sat here.\p"
	.string "Thank you for coming.$"

PokemonLeague_TyrimsRoom_Text_TyrimPostBattle:
	.string "TYRIM: The league is yours,\n"
	.string "Champion.\p"
	.string "PRIYO will be insufferable.$"
