SnowRoute13_MapScripts::
	.byte 0

SnowRoute13_EventScript_Reese::
	trainerbattle_single TRAINER_SNOW_R13_1_REESE, SnowRoute13_Text_ReeseIntro, SnowRoute13_Text_ReeseDefeat
	msgbox SnowRoute13_Text_ReesePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Lyric::
	trainerbattle_single TRAINER_SNOW_R13_2_LYRIC, SnowRoute13_Text_LyricIntro, SnowRoute13_Text_LyricDefeat
	msgbox SnowRoute13_Text_LyricPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Mantis::
	trainerbattle_single TRAINER_SNOW_R13_3_MANTIS, SnowRoute13_Text_MantisIntro, SnowRoute13_Text_MantisDefeat
	msgbox SnowRoute13_Text_MantisPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Fern::
	trainerbattle_single TRAINER_SNOW_R13_4_FERN, SnowRoute13_Text_FernIntro, SnowRoute13_Text_FernDefeat
	msgbox SnowRoute13_Text_FernPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Vance::
	trainerbattle_single TRAINER_SNOW_R13_5_VANCE, SnowRoute13_Text_VanceIntro, SnowRoute13_Text_VanceDefeat
	msgbox SnowRoute13_Text_VancePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Hue::
	trainerbattle_single TRAINER_SNOW_R13_6_HUE, SnowRoute13_Text_HueIntro, SnowRoute13_Text_HueDefeat
	msgbox SnowRoute13_Text_HuePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Buzz::
	trainerbattle_single TRAINER_SNOW_R13_7_BUZZ, SnowRoute13_Text_BuzzIntro, SnowRoute13_Text_BuzzDefeat
	msgbox SnowRoute13_Text_BuzzPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Royce::
	trainerbattle_single TRAINER_SNOW_R13_8_ROYCE, SnowRoute13_Text_RoyceIntro, SnowRoute13_Text_RoyceDefeat
	msgbox SnowRoute13_Text_RoycePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Lana::
	trainerbattle_single TRAINER_SNOW_R13_9_LANA, SnowRoute13_Text_LanaIntro, SnowRoute13_Text_LanaDefeat
	msgbox SnowRoute13_Text_LanaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_Text_ReeseIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute13_Text_ReeseDefeat:
	.string "That was incredible...$"

SnowRoute13_Text_ReesePostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute13_Text_LyricIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute13_Text_LyricDefeat:
	.string "I didn't expect that...$"

SnowRoute13_Text_LyricPostBattle:
	.string "Good luck on your journey.$"

SnowRoute13_Text_MantisIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute13_Text_MantisDefeat:
	.string "You're stronger than I thought!$"

SnowRoute13_Text_MantisPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute13_Text_FernIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute13_Text_FernDefeat:
	.string "Wow, I lost...$"

SnowRoute13_Text_FernPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute13_Text_VanceIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute13_Text_VanceDefeat:
	.string "I need to train more...$"

SnowRoute13_Text_VancePostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute13_Text_HueIntro:
	.string "No one passes without a fight!$"

SnowRoute13_Text_HueDefeat:
	.string "You really got me...$"

SnowRoute13_Text_HuePostBattle:
	.string "You've got real talent.$"

SnowRoute13_Text_BuzzIntro:
	.string "I won't go easy on you!$"

SnowRoute13_Text_BuzzDefeat:
	.string "Not bad at all...$"

SnowRoute13_Text_BuzzPostBattle:
	.string "Keep pushing forward!$"

SnowRoute13_Text_RoyceIntro:
	.string "Ready? Here I come!$"

SnowRoute13_Text_RoyceDefeat:
	.string "I'll remember this battle!$"

SnowRoute13_Text_RoycePostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"

SnowRoute13_Text_LanaIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute13_Text_LanaDefeat:
	.string "That was incredible...$"

SnowRoute13_Text_LanaPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"
