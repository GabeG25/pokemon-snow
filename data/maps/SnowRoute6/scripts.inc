SnowRoute6_MapScripts::
	.byte 0

SnowRoute6_EventScript_Nadia::
	trainerbattle_single TRAINER_SNOW_R6_1_NADIA, SnowRoute6_Text_NadiaIntro, SnowRoute6_Text_NadiaDefeat
	msgbox SnowRoute6_Text_NadiaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Reed::
	trainerbattle_single TRAINER_SNOW_R6_2_REED, SnowRoute6_Text_ReedIntro, SnowRoute6_Text_ReedDefeat
	msgbox SnowRoute6_Text_ReedPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Wade::
	trainerbattle_single TRAINER_SNOW_R6_3_WADE, SnowRoute6_Text_WadeIntro, SnowRoute6_Text_WadeDefeat
	msgbox SnowRoute6_Text_WadePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Clark::
	trainerbattle_single TRAINER_SNOW_R6_4_CLARK, SnowRoute6_Text_ClarkIntro, SnowRoute6_Text_ClarkDefeat
	msgbox SnowRoute6_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Miles::
	trainerbattle_single TRAINER_SNOW_R6_5_MILES, SnowRoute6_Text_MilesIntro, SnowRoute6_Text_MilesDefeat
	msgbox SnowRoute6_Text_MilesPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Helena::
	trainerbattle_single TRAINER_SNOW_R6_6_HELENA, SnowRoute6_Text_HelenaIntro, SnowRoute6_Text_HelenaDefeat
	msgbox SnowRoute6_Text_HelenaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Ivy::
	trainerbattle_single TRAINER_SNOW_R6_7_IVY, SnowRoute6_Text_IvyIntro, SnowRoute6_Text_IvyDefeat
	msgbox SnowRoute6_Text_IvyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Hale::
	trainerbattle_single TRAINER_SNOW_R6_8_HALE, SnowRoute6_Text_HaleIntro, SnowRoute6_Text_HaleDefeat
	msgbox SnowRoute6_Text_HalePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_Text_NadiaIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute6_Text_NadiaDefeat:
	.string "That was incredible...$"

SnowRoute6_Text_NadiaPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute6_Text_ReedIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute6_Text_ReedDefeat:
	.string "I didn't expect that...$"

SnowRoute6_Text_ReedPostBattle:
	.string "Good luck on your journey.$"

SnowRoute6_Text_WadeIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute6_Text_WadeDefeat:
	.string "You're stronger than I thought!$"

SnowRoute6_Text_WadePostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute6_Text_ClarkIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute6_Text_ClarkDefeat:
	.string "Wow, I lost...$"

SnowRoute6_Text_ClarkPostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute6_Text_MilesIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute6_Text_MilesDefeat:
	.string "I need to train more...$"

SnowRoute6_Text_MilesPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute6_Text_HelenaIntro:
	.string "No one passes without a fight!$"

SnowRoute6_Text_HelenaDefeat:
	.string "You really got me...$"

SnowRoute6_Text_HelenaPostBattle:
	.string "You've got real talent.$"

SnowRoute6_Text_IvyIntro:
	.string "I won't go easy on you!$"

SnowRoute6_Text_IvyDefeat:
	.string "Not bad at all...$"

SnowRoute6_Text_IvyPostBattle:
	.string "Keep pushing forward!$"

SnowRoute6_Text_HaleIntro:
	.string "Ready? Here I come!$"

SnowRoute6_Text_HaleDefeat:
	.string "I'll remember this battle!$"

SnowRoute6_Text_HalePostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"
