SnowRoute9_MapScripts::
	.byte 0

SnowRoute9_EventScript_Jonas::
	trainerbattle_single TRAINER_SNOW_R9_1_JONAS, SnowRoute9_Text_JonasIntro, SnowRoute9_Text_JonasDefeat
	msgbox SnowRoute9_Text_JonasPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Sterling::
	trainerbattle_single TRAINER_SNOW_R9_2_STERLING, SnowRoute9_Text_SterlingIntro, SnowRoute9_Text_SterlingDefeat
	msgbox SnowRoute9_Text_SterlingPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Vince::
	trainerbattle_single TRAINER_SNOW_R9_3_VINCE, SnowRoute9_Text_VinceIntro, SnowRoute9_Text_VinceDefeat
	msgbox SnowRoute9_Text_VincePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Burke::
	trainerbattle_single TRAINER_SNOW_R9_4_BURKE, SnowRoute9_Text_BurkeIntro, SnowRoute9_Text_BurkeDefeat
	msgbox SnowRoute9_Text_BurkePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Marsh::
	trainerbattle_single TRAINER_SNOW_R9_5_MARSH, SnowRoute9_Text_MarshIntro, SnowRoute9_Text_MarshDefeat
	msgbox SnowRoute9_Text_MarshPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Iris::
	trainerbattle_single TRAINER_SNOW_R9_6_IRIS, SnowRoute9_Text_IrisIntro, SnowRoute9_Text_IrisDefeat
	msgbox SnowRoute9_Text_IrisPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Coral::
	trainerbattle_single TRAINER_SNOW_R9_7_CORAL, SnowRoute9_Text_CoralIntro, SnowRoute9_Text_CoralDefeat
	msgbox SnowRoute9_Text_CoralPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Troy::
	trainerbattle_single TRAINER_SNOW_R9_8_TROY, SnowRoute9_Text_TroyIntro, SnowRoute9_Text_TroyDefeat
	msgbox SnowRoute9_Text_TroyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_Text_JonasIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute9_Text_JonasDefeat:
	.string "That was incredible...$"

SnowRoute9_Text_JonasPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute9_Text_SterlingIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute9_Text_SterlingDefeat:
	.string "I didn't expect that...$"

SnowRoute9_Text_SterlingPostBattle:
	.string "Good luck on your journey.$"

SnowRoute9_Text_VinceIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute9_Text_VinceDefeat:
	.string "You're stronger than I thought!$"

SnowRoute9_Text_VincePostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute9_Text_BurkeIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute9_Text_BurkeDefeat:
	.string "Wow, I lost...$"

SnowRoute9_Text_BurkePostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute9_Text_MarshIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute9_Text_MarshDefeat:
	.string "I need to train more...$"

SnowRoute9_Text_MarshPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute9_Text_IrisIntro:
	.string "No one passes without a fight!$"

SnowRoute9_Text_IrisDefeat:
	.string "You really got me...$"

SnowRoute9_Text_IrisPostBattle:
	.string "You've got real talent.$"

SnowRoute9_Text_CoralIntro:
	.string "I won't go easy on you!$"

SnowRoute9_Text_CoralDefeat:
	.string "Not bad at all...$"

SnowRoute9_Text_CoralPostBattle:
	.string "Keep pushing forward!$"

SnowRoute9_Text_TroyIntro:
	.string "Ready? Here I come!$"

SnowRoute9_Text_TroyDefeat:
	.string "I'll remember this battle!$"

SnowRoute9_Text_TroyPostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"
