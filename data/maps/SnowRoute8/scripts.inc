SnowRoute8_MapScripts::
	.byte 0

SnowRoute8_EventScript_Vivian::
	trainerbattle_single TRAINER_SNOW_R8_1_VIVIAN, SnowRoute8_Text_VivianIntro, SnowRoute8_Text_VivianDefeat
	msgbox SnowRoute8_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Tessa::
	trainerbattle_single TRAINER_SNOW_R8_2_TESSA, SnowRoute8_Text_TessaIntro, SnowRoute8_Text_TessaDefeat
	msgbox SnowRoute8_Text_TessaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Wren::
	trainerbattle_single TRAINER_SNOW_R8_3_WREN, SnowRoute8_Text_WrenIntro, SnowRoute8_Text_WrenDefeat
	msgbox SnowRoute8_Text_WrenPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Declan::
	trainerbattle_single TRAINER_SNOW_R8_4_DECLAN, SnowRoute8_Text_DeclanIntro, SnowRoute8_Text_DeclanDefeat
	msgbox SnowRoute8_Text_DeclanPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Claire::
	trainerbattle_single TRAINER_SNOW_R8_5_CLAIRE, SnowRoute8_Text_ClaireIntro, SnowRoute8_Text_ClaireDefeat
	msgbox SnowRoute8_Text_ClairePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Rook::
	trainerbattle_single TRAINER_SNOW_R8_6_ROOK, SnowRoute8_Text_RookIntro, SnowRoute8_Text_RookDefeat
	msgbox SnowRoute8_Text_RookPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_Text_VivianIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute8_Text_VivianDefeat:
	.string "That was incredible...$"

SnowRoute8_Text_VivianPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute8_Text_TessaIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute8_Text_TessaDefeat:
	.string "I didn't expect that...$"

SnowRoute8_Text_TessaPostBattle:
	.string "Good luck on your journey.$"

SnowRoute8_Text_WrenIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute8_Text_WrenDefeat:
	.string "You're stronger than I thought!$"

SnowRoute8_Text_WrenPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute8_Text_DeclanIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute8_Text_DeclanDefeat:
	.string "Wow, I lost...$"

SnowRoute8_Text_DeclanPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute8_Text_ClaireIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute8_Text_ClaireDefeat:
	.string "I need to train more...$"

SnowRoute8_Text_ClairePostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute8_Text_RookIntro:
	.string "No one passes without a fight!$"

SnowRoute8_Text_RookDefeat:
	.string "You really got me...$"

SnowRoute8_Text_RookPostBattle:
	.string "You've got real talent.$"
