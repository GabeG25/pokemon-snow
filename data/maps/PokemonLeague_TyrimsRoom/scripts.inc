PokemonLeague_TyrimsRoom_MapScripts::
	.byte 0

PokemonLeague_TyrimsRoom_EventScript_Tyrim::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_TyrimsRoom_EventScript_TyrimDefeated
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F35_TYRIM, PokemonLeague_TyrimsRoom_Text_TyrimDefeat
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimSpeech, MSGBOX_DEFAULT
	closemessage
	@ Walk Tyrim to the north door, then warp player to Hall of Fame.
	@ FLAG_IS_CHAMPION is set inside the HoF cutscene after Evergreen's
	@ initiation, so repeat visitors to Tyrim's room still replay his
	@ escort to HoF until the credits have run once.
	applymovement 1, PokemonLeague_TyrimsRoom_Movement_TyrimLeadToHoF
	applymovement LOCALID_PLAYER, PokemonLeague_TyrimsRoom_Movement_PlayerFollowToHoF
	waitmovement 0
	warp MAP_BORALYSS_HALL_OF_FAME, 255, 6, 15
	waitstate
	release
	end

PokemonLeague_TyrimsRoom_EventScript_TyrimDefeated::
	msgbox PokemonLeague_TyrimsRoom_Text_TyrimPostChampion, MSGBOX_DEFAULT
	release
	end

PokemonLeague_TyrimsRoom_Movement_TyrimLeadToHoF:
	walk_up
	walk_up
	step_end

PokemonLeague_TyrimsRoom_Movement_PlayerFollowToHoF:
	walk_in_place_faster_up
	walk_up
	step_end

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

PokemonLeague_TyrimsRoom_Text_TyrimSpeech:
	.string "TYRIM: When TYRELL began his\n"
	.string "winter, the region forgot\l"
	.string "something important.\p"
	.string "POKEMON and people are not\n"
	.string "separate. We endure TOGETHER.\p"
	.string "TYRELL believed the cold\n"
	.string "would break us. He believed\l"
	.string "change could be forced.\p"
	.string "He was wrong.\p"
	.string "You reminded BORALYSS that\n"
	.string "together we are greater than\l"
	.string "any change that confronts us.\p"
	.string "The League has a tradition\n"
	.string "for trainers who prove what\l"
	.string "you just proved.\p"
	.string "Come with me.$"

PokemonLeague_TyrimsRoom_Text_TyrimPostChampion:
	.string "TYRIM: The throne is yours,\n"
	.string "Champion.\p"
	.string "PRIYO will be insufferable.$"
