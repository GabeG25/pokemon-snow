SnowRoute15_MapScripts::
	.byte 0

SnowRoute15_EventScript_Briney::
	trainerbattle_single TRAINER_SNOW_R15_1_BRINEY, SnowRoute15_Text_BrineyIntro, SnowRoute15_Text_BrineyDefeat
	msgbox SnowRoute15_Text_BrineyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Ahab::
	trainerbattle_single TRAINER_SNOW_R15_2_AHAB, SnowRoute15_Text_AhabIntro, SnowRoute15_Text_AhabDefeat
	msgbox SnowRoute15_Text_AhabPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Cousteau::
	trainerbattle_single TRAINER_SNOW_R15_3_COUSTEAU, SnowRoute15_Text_CousteauIntro, SnowRoute15_Text_CousteauDefeat
	msgbox SnowRoute15_Text_CousteauPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Hadley::
	trainerbattle_single TRAINER_SNOW_R15_4_HADLEY, SnowRoute15_Text_HadleyIntro, SnowRoute15_Text_HadleyDefeat
	msgbox SnowRoute15_Text_HadleyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Volt::
	trainerbattle_single TRAINER_SNOW_R15_5_VOLT, SnowRoute15_Text_VoltIntro, SnowRoute15_Text_VoltDefeat
	msgbox SnowRoute15_Text_VoltPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Quint::
	trainerbattle_single TRAINER_SNOW_R15_6_QUINT, SnowRoute15_Text_QuintIntro, SnowRoute15_Text_QuintDefeat
	msgbox SnowRoute15_Text_QuintPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Nori::
	trainerbattle_single TRAINER_SNOW_R15_7_NORI, SnowRoute15_Text_NoriIntro, SnowRoute15_Text_NoriDefeat
	msgbox SnowRoute15_Text_NoriPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Triton::
	trainerbattle_single TRAINER_SNOW_R15_8_TRITON, SnowRoute15_Text_TritonIntro, SnowRoute15_Text_TritonDefeat
	msgbox SnowRoute15_Text_TritonPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Nemo::
	trainerbattle_single TRAINER_SNOW_R15_9_NEMO, SnowRoute15_Text_NemoIntro, SnowRoute15_Text_NemoDefeat
	msgbox SnowRoute15_Text_NemoPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_Text_BrineyIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute15_Text_BrineyDefeat:
	.string "That was incredible...$"

SnowRoute15_Text_BrineyPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute15_Text_AhabIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute15_Text_AhabDefeat:
	.string "I didn't expect that...$"

SnowRoute15_Text_AhabPostBattle:
	.string "Good luck on your journey.$"

SnowRoute15_Text_CousteauIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute15_Text_CousteauDefeat:
	.string "You're stronger than I thought!$"

SnowRoute15_Text_CousteauPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute15_Text_HadleyIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute15_Text_HadleyDefeat:
	.string "Wow, I lost...$"

SnowRoute15_Text_HadleyPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute15_Text_VoltIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute15_Text_VoltDefeat:
	.string "I need to train more...$"

SnowRoute15_Text_VoltPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute15_Text_QuintIntro:
	.string "No one passes without a fight!$"

SnowRoute15_Text_QuintDefeat:
	.string "You really got me...$"

SnowRoute15_Text_QuintPostBattle:
	.string "You've got real talent.$"

SnowRoute15_Text_NoriIntro:
	.string "I won't go easy on you!$"

SnowRoute15_Text_NoriDefeat:
	.string "Not bad at all...$"

SnowRoute15_Text_NoriPostBattle:
	.string "Keep pushing forward!$"

SnowRoute15_Text_TritonIntro:
	.string "Ready? Here I come!$"

SnowRoute15_Text_TritonDefeat:
	.string "I'll remember this battle!$"

SnowRoute15_Text_TritonPostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"

SnowRoute15_Text_NemoIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute15_Text_NemoDefeat:
	.string "That was incredible...$"

SnowRoute15_Text_NemoPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"
