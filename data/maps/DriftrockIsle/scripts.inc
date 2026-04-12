DriftrockIsle_MapScripts::
	.byte 0

DriftrockIsle_EventScript_Daphne::
	trainerbattle_single TRAINER_SNOW_DI_1_DAPHNE, DriftrockIsle_Text_DaphneIntro, DriftrockIsle_Text_DaphneDefeat
	msgbox DriftrockIsle_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

DriftrockIsle_EventScript_Pearl::
	trainerbattle_single TRAINER_SNOW_DI_2_PEARL, DriftrockIsle_Text_PearlIntro, DriftrockIsle_Text_PearlDefeat
	msgbox DriftrockIsle_Text_PearlPostBattle, MSGBOX_AUTOCLOSE
	end

DriftrockIsle_EventScript_Flynn::
	trainerbattle_single TRAINER_SNOW_DI_3_FLYNN, DriftrockIsle_Text_FlynnIntro, DriftrockIsle_Text_FlynnDefeat
	msgbox DriftrockIsle_Text_FlynnPostBattle, MSGBOX_AUTOCLOSE
	end

DriftrockIsle_EventScript_Tara::
	trainerbattle_single TRAINER_SNOW_DI_4_TARA, DriftrockIsle_Text_TaraIntro, DriftrockIsle_Text_TaraDefeat
	msgbox DriftrockIsle_Text_TaraPostBattle, MSGBOX_AUTOCLOSE
	end

DriftrockIsle_EventScript_Heath::
	trainerbattle_single TRAINER_SNOW_DI_5_HEATH, DriftrockIsle_Text_HeathIntro, DriftrockIsle_Text_HeathDefeat
	msgbox DriftrockIsle_Text_HeathPostBattle, MSGBOX_AUTOCLOSE
	end

DriftrockIsle_Text_DaphneIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

DriftrockIsle_Text_DaphneDefeat:
	.string "That was incredible...$"

DriftrockIsle_Text_DaphnePostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

DriftrockIsle_Text_PearlIntro:
	.string "A challenger? Perfect timing!$"

DriftrockIsle_Text_PearlDefeat:
	.string "I didn't expect that...$"

DriftrockIsle_Text_PearlPostBattle:
	.string "Good luck on your journey.$"

DriftrockIsle_Text_FlynnIntro:
	.string "I've been training for this!\nBring it on!$"

DriftrockIsle_Text_FlynnDefeat:
	.string "You're stronger than I thought!$"

DriftrockIsle_Text_FlynnPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

DriftrockIsle_Text_TaraIntro:
	.string "You look tough, but I'm tougher!$"

DriftrockIsle_Text_TaraDefeat:
	.string "Wow, I lost...$"

DriftrockIsle_Text_TaraPostBattle:
	.string "You should rest at the next\ntown if you can.$"

DriftrockIsle_Text_HeathIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

DriftrockIsle_Text_HeathDefeat:
	.string "I need to train more...$"

DriftrockIsle_Text_HeathPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"
