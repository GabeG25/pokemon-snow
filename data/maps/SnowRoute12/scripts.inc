SnowRoute12_MapScripts::
	.byte 0

SnowRoute12_EventScript_Nyx::
	trainerbattle_single TRAINER_SNOW_R12_1_NYX, SnowRoute12_Text_NyxIntro, SnowRoute12_Text_NyxDefeat
	msgbox SnowRoute12_Text_NyxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Holtz::
	trainerbattle_single TRAINER_SNOW_R12_2_HOLTZ, SnowRoute12_Text_HoltzIntro, SnowRoute12_Text_HoltzDefeat
	msgbox SnowRoute12_Text_HoltzPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Belmont::
	trainerbattle_single TRAINER_SNOW_R12_3_BELMONT, SnowRoute12_Text_BelmontIntro, SnowRoute12_Text_BelmontDefeat
	msgbox SnowRoute12_Text_BelmontPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Bard::
	trainerbattle_single TRAINER_SNOW_R12_4_BARD, SnowRoute12_Text_BardIntro, SnowRoute12_Text_BardDefeat
	msgbox SnowRoute12_Text_BardPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Elara::
	trainerbattle_single TRAINER_SNOW_R12_5_ELARA, SnowRoute12_Text_ElaraIntro, SnowRoute12_Text_ElaraDefeat
	msgbox SnowRoute12_Text_ElaraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Slade::
	trainerbattle_single TRAINER_SNOW_R12_6_SLADE, SnowRoute12_Text_SladeIntro, SnowRoute12_Text_SladeDefeat
	msgbox SnowRoute12_Text_SladePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Quinn::
	trainerbattle_single TRAINER_SNOW_R12_7_QUINN, SnowRoute12_Text_QuinnIntro, SnowRoute12_Text_QuinnDefeat
	msgbox SnowRoute12_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_Text_NyxIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute12_Text_NyxDefeat:
	.string "That was incredible...$"

SnowRoute12_Text_NyxPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute12_Text_HoltzIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute12_Text_HoltzDefeat:
	.string "I didn't expect that...$"

SnowRoute12_Text_HoltzPostBattle:
	.string "Good luck on your journey.$"

SnowRoute12_Text_BelmontIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute12_Text_BelmontDefeat:
	.string "You're stronger than I thought!$"

SnowRoute12_Text_BelmontPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute12_Text_BardIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute12_Text_BardDefeat:
	.string "Wow, I lost...$"

SnowRoute12_Text_BardPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute12_Text_ElaraIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute12_Text_ElaraDefeat:
	.string "I need to train more...$"

SnowRoute12_Text_ElaraPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute12_Text_SladeIntro:
	.string "No one passes without a fight!$"

SnowRoute12_Text_SladeDefeat:
	.string "You really got me...$"

SnowRoute12_Text_SladePostBattle:
	.string "You've got real talent.$"

SnowRoute12_Text_QuinnIntro:
	.string "I won't go easy on you!$"

SnowRoute12_Text_QuinnDefeat:
	.string "Not bad at all...$"

SnowRoute12_Text_QuinnPostBattle:
	.string "Keep pushing forward!$"
