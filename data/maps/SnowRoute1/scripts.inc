SnowRoute1_MapScripts::
	.byte 0

SnowRoute1_EventScript_Noel::
	trainerbattle_single TRAINER_SNOW_R1_1_NOEL, SnowRoute1_Text_NoelIntro, SnowRoute1_Text_NoelDefeat
	msgbox SnowRoute1_Text_NoelPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_EventScript_Elise::
	trainerbattle_single TRAINER_SNOW_R1_2_ELISE, SnowRoute1_Text_EliseIntro, SnowRoute1_Text_EliseDefeat
	msgbox SnowRoute1_Text_ElisePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_EventScript_Kai::
	trainerbattle_single TRAINER_SNOW_R1_3_KAI, SnowRoute1_Text_KaiIntro, SnowRoute1_Text_KaiDefeat
	msgbox SnowRoute1_Text_KaiPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_Text_NoelIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute1_Text_NoelDefeat:
	.string "That was incredible...$"

SnowRoute1_Text_NoelPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute1_Text_EliseIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute1_Text_EliseDefeat:
	.string "I didn't expect that...$"

SnowRoute1_Text_ElisePostBattle:
	.string "Good luck on your journey.$"

SnowRoute1_Text_KaiIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute1_Text_KaiDefeat:
	.string "You're stronger than I thought!$"

SnowRoute1_Text_KaiPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"
