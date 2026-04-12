SnowRoute2_MapScripts::
	.byte 0

SnowRoute2_EventScript_Brett::
	trainerbattle_single TRAINER_SNOW_R2_1_BRETT, SnowRoute2_Text_BrettIntro, SnowRoute2_Text_BrettDefeat
	msgbox SnowRoute2_Text_BrettPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Finn::
	trainerbattle_single TRAINER_SNOW_R2_2_FINN, SnowRoute2_Text_FinnIntro, SnowRoute2_Text_FinnDefeat
	msgbox SnowRoute2_Text_FinnPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Mila::
	trainerbattle_single TRAINER_SNOW_R2_3_MILA, SnowRoute2_Text_MilaIntro, SnowRoute2_Text_MilaDefeat
	msgbox SnowRoute2_Text_MilaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Gus::
	trainerbattle_single TRAINER_SNOW_R2_4_GUS, SnowRoute2_Text_GusIntro, SnowRoute2_Text_GusDefeat
	msgbox SnowRoute2_Text_GusPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_Text_BrettIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute2_Text_BrettDefeat:
	.string "That was incredible...$"

SnowRoute2_Text_BrettPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute2_Text_FinnIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute2_Text_FinnDefeat:
	.string "I didn't expect that...$"

SnowRoute2_Text_FinnPostBattle:
	.string "Good luck on your journey.$"

SnowRoute2_Text_MilaIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute2_Text_MilaDefeat:
	.string "You're stronger than I thought!$"

SnowRoute2_Text_MilaPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute2_Text_GusIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute2_Text_GusDefeat:
	.string "Wow, I lost...$"

SnowRoute2_Text_GusPostBattle:
	.string "You should rest at the next\ntown if you can.$"
