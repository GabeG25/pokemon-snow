SnowRoute3_MapScripts::
	.byte 0

SnowRoute3_EventScript_Tate::
	trainerbattle_single TRAINER_SNOW_R3_1_TATE, SnowRoute3_Text_TateIntro, SnowRoute3_Text_TateDefeat
	msgbox SnowRoute3_Text_TatePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Liam::
	trainerbattle_single TRAINER_SNOW_R3_2_LIAM, SnowRoute3_Text_LiamIntro, SnowRoute3_Text_LiamDefeat
	msgbox SnowRoute3_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Faye::
	trainerbattle_single TRAINER_SNOW_R3_3_FAYE, SnowRoute3_Text_FayeIntro, SnowRoute3_Text_FayeDefeat
	msgbox SnowRoute3_Text_FayePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Rowan::
	trainerbattle_single TRAINER_SNOW_R3_4_ROWAN, SnowRoute3_Text_RowanIntro, SnowRoute3_Text_RowanDefeat
	msgbox SnowRoute3_Text_RowanPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Grunt1::
	trainerbattle_single TRAINER_SNOW_R3_5_GRUNT, SnowRoute3_Text_Grunt1Intro, SnowRoute3_Text_Grunt1Defeat
	msgbox SnowRoute3_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_Text_TateIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute3_Text_TateDefeat:
	.string "That was incredible...$"

SnowRoute3_Text_TatePostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute3_Text_LiamIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute3_Text_LiamDefeat:
	.string "I didn't expect that...$"

SnowRoute3_Text_LiamPostBattle:
	.string "Good luck on your journey.$"

SnowRoute3_Text_FayeIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute3_Text_FayeDefeat:
	.string "You're stronger than I thought!$"

SnowRoute3_Text_FayePostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute3_Text_RowanIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute3_Text_RowanDefeat:
	.string "Wow, I lost...$"

SnowRoute3_Text_RowanPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute3_Text_Grunt1Intro:
	.string "Team Veil will not be stopped!$"

SnowRoute3_Text_Grunt1Defeat:
	.string "This changes nothing...$"

SnowRoute3_Text_Grunt1PostBattle:
	.string "Team Veil's plan is already\nin motion. You're too late.$"
