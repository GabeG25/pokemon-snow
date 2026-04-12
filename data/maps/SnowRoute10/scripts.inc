SnowRoute10_MapScripts::
	.byte 0

SnowRoute10_EventScript_Hank::
	trainerbattle_single TRAINER_SNOW_R10_1_HANK, SnowRoute10_Text_HankIntro, SnowRoute10_Text_HankDefeat
	msgbox SnowRoute10_Text_HankPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Lyra::
	trainerbattle_single TRAINER_SNOW_R10_2_LYRA, SnowRoute10_Text_LyraIntro, SnowRoute10_Text_LyraDefeat
	msgbox SnowRoute10_Text_LyraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Nash::
	trainerbattle_single TRAINER_SNOW_R10_3_NASH, SnowRoute10_Text_NashIntro, SnowRoute10_Text_NashDefeat
	msgbox SnowRoute10_Text_NashPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Grimm::
	trainerbattle_single TRAINER_SNOW_R10_4_GRIMM, SnowRoute10_Text_GrimmIntro, SnowRoute10_Text_GrimmDefeat
	msgbox SnowRoute10_Text_GrimmPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Zara::
	trainerbattle_single TRAINER_SNOW_R10_5_ZARA, SnowRoute10_Text_ZaraIntro, SnowRoute10_Text_ZaraDefeat
	msgbox SnowRoute10_Text_ZaraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Felix::
	trainerbattle_single TRAINER_SNOW_R10_6_FELIX, SnowRoute10_Text_FelixIntro, SnowRoute10_Text_FelixDefeat
	msgbox SnowRoute10_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Sage::
	trainerbattle_single TRAINER_SNOW_R10_7_SAGE, SnowRoute10_Text_SageIntro, SnowRoute10_Text_SageDefeat
	msgbox SnowRoute10_Text_SagePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Boone::
	trainerbattle_single TRAINER_SNOW_R10_8_BOONE, SnowRoute10_Text_BooneIntro, SnowRoute10_Text_BooneDefeat
	msgbox SnowRoute10_Text_BoonePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_Text_HankIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute10_Text_HankDefeat:
	.string "That was incredible...$"

SnowRoute10_Text_HankPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute10_Text_LyraIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute10_Text_LyraDefeat:
	.string "I didn't expect that...$"

SnowRoute10_Text_LyraPostBattle:
	.string "Good luck on your journey.$"

SnowRoute10_Text_NashIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute10_Text_NashDefeat:
	.string "You're stronger than I thought!$"

SnowRoute10_Text_NashPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute10_Text_GrimmIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute10_Text_GrimmDefeat:
	.string "Wow, I lost...$"

SnowRoute10_Text_GrimmPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute10_Text_ZaraIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute10_Text_ZaraDefeat:
	.string "I need to train more...$"

SnowRoute10_Text_ZaraPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute10_Text_FelixIntro:
	.string "No one passes without a fight!$"

SnowRoute10_Text_FelixDefeat:
	.string "You really got me...$"

SnowRoute10_Text_FelixPostBattle:
	.string "You've got real talent.$"

SnowRoute10_Text_SageIntro:
	.string "I won't go easy on you!$"

SnowRoute10_Text_SageDefeat:
	.string "Not bad at all...$"

SnowRoute10_Text_SagePostBattle:
	.string "Keep pushing forward!$"

SnowRoute10_Text_BooneIntro:
	.string "Ready? Here I come!$"

SnowRoute10_Text_BooneDefeat:
	.string "I'll remember this battle!$"

SnowRoute10_Text_BoonePostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"
