SnowRoute11_MapScripts::
	.byte 0

SnowRoute11_EventScript_Vera::
	trainerbattle_single TRAINER_SNOW_R11_1_VERA, SnowRoute11_Text_VeraIntro, SnowRoute11_Text_VeraDefeat
	msgbox SnowRoute11_Text_VeraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Tucker::
	trainerbattle_single TRAINER_SNOW_R11_2_TUCKER, SnowRoute11_Text_TuckerIntro, SnowRoute11_Text_TuckerDefeat
	msgbox SnowRoute11_Text_TuckerPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Cypress::
	trainerbattle_single TRAINER_SNOW_R11_3_CYPRESS, SnowRoute11_Text_CypressIntro, SnowRoute11_Text_CypressDefeat
	msgbox SnowRoute11_Text_CypressPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Nina::
	trainerbattle_single TRAINER_SNOW_R11_4_NINA, SnowRoute11_Text_NinaIntro, SnowRoute11_Text_NinaDefeat
	msgbox SnowRoute11_Text_NinaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Cade::
	trainerbattle_single TRAINER_SNOW_R11_5_CADE, SnowRoute11_Text_CadeIntro, SnowRoute11_Text_CadeDefeat
	msgbox SnowRoute11_Text_CadePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Odette::
	trainerbattle_single TRAINER_SNOW_R11_6_ODETTE, SnowRoute11_Text_OdetteIntro, SnowRoute11_Text_OdetteDefeat
	msgbox SnowRoute11_Text_OdettePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_Text_VeraIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute11_Text_VeraDefeat:
	.string "That was incredible...$"

SnowRoute11_Text_VeraPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute11_Text_TuckerIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute11_Text_TuckerDefeat:
	.string "I didn't expect that...$"

SnowRoute11_Text_TuckerPostBattle:
	.string "Good luck on your journey.$"

SnowRoute11_Text_CypressIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute11_Text_CypressDefeat:
	.string "You're stronger than I thought!$"

SnowRoute11_Text_CypressPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute11_Text_NinaIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute11_Text_NinaDefeat:
	.string "Wow, I lost...$"

SnowRoute11_Text_NinaPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute11_Text_CadeIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute11_Text_CadeDefeat:
	.string "I need to train more...$"

SnowRoute11_Text_CadePostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute11_Text_OdetteIntro:
	.string "No one passes without a fight!$"

SnowRoute11_Text_OdetteDefeat:
	.string "You really got me...$"

SnowRoute11_Text_OdettePostBattle:
	.string "You've got real talent.$"
