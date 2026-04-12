SnowRoute7_MapScripts::
	.byte 0

SnowRoute7_EventScript_Harlan::
	trainerbattle_single TRAINER_SNOW_R7_1_HARLAN, SnowRoute7_Text_HarlanIntro, SnowRoute7_Text_HarlanDefeat
	msgbox SnowRoute7_Text_HarlanPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Corey::
	trainerbattle_single TRAINER_SNOW_R7_2_COREY, SnowRoute7_Text_CoreyIntro, SnowRoute7_Text_CoreyDefeat
	msgbox SnowRoute7_Text_CoreyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Opal::
	trainerbattle_single TRAINER_SNOW_R7_3_OPAL, SnowRoute7_Text_OpalIntro, SnowRoute7_Text_OpalDefeat
	msgbox SnowRoute7_Text_OpalPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Brenna::
	trainerbattle_single TRAINER_SNOW_R7_4_BRENNA, SnowRoute7_Text_BrennaIntro, SnowRoute7_Text_BrennaDefeat
	msgbox SnowRoute7_Text_BrennaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Lumi::
	trainerbattle_single TRAINER_SNOW_R7_5_LUMI, SnowRoute7_Text_LumiIntro, SnowRoute7_Text_LumiDefeat
	msgbox SnowRoute7_Text_LumiPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_Text_HarlanIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute7_Text_HarlanDefeat:
	.string "That was incredible...$"

SnowRoute7_Text_HarlanPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute7_Text_CoreyIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute7_Text_CoreyDefeat:
	.string "I didn't expect that...$"

SnowRoute7_Text_CoreyPostBattle:
	.string "Good luck on your journey.$"

SnowRoute7_Text_OpalIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute7_Text_OpalDefeat:
	.string "You're stronger than I thought!$"

SnowRoute7_Text_OpalPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute7_Text_BrennaIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute7_Text_BrennaDefeat:
	.string "Wow, I lost...$"

SnowRoute7_Text_BrennaPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute7_Text_LumiIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute7_Text_LumiDefeat:
	.string "I need to train more...$"

SnowRoute7_Text_LumiPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"
