SnowRoute14_MapScripts::
	.byte 0

SnowRoute14_EventScript_Cinder::
	trainerbattle_single TRAINER_SNOW_R14_1_CINDER, SnowRoute14_Text_CinderIntro, SnowRoute14_Text_CinderDefeat
	msgbox SnowRoute14_Text_CinderPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Marlow::
	trainerbattle_single TRAINER_SNOW_R14_2_MARLOW, SnowRoute14_Text_MarlowIntro, SnowRoute14_Text_MarlowDefeat
	msgbox SnowRoute14_Text_MarlowPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Cassia::
	trainerbattle_single TRAINER_SNOW_R14_3_CASSIA, SnowRoute14_Text_CassiaIntro, SnowRoute14_Text_CassiaDefeat
	msgbox SnowRoute14_Text_CassiaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Forge::
	trainerbattle_single TRAINER_SNOW_R14_4_FORGE, SnowRoute14_Text_ForgeIntro, SnowRoute14_Text_ForgeDefeat
	msgbox SnowRoute14_Text_ForgePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Vesta::
	trainerbattle_single TRAINER_SNOW_R14_5_VESTA, SnowRoute14_Text_VestaIntro, SnowRoute14_Text_VestaDefeat
	msgbox SnowRoute14_Text_VestaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Ember::
	trainerbattle_single TRAINER_SNOW_R14_6_EMBER, SnowRoute14_Text_EmberIntro, SnowRoute14_Text_EmberDefeat
	msgbox SnowRoute14_Text_EmberPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Vex::
	trainerbattle_single TRAINER_SNOW_R14_7_VEX, SnowRoute14_Text_VexIntro, SnowRoute14_Text_VexDefeat
	msgbox SnowRoute14_Text_VexPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Marek::
	trainerbattle_single TRAINER_SNOW_R14_8_MAREK, SnowRoute14_Text_MarekIntro, SnowRoute14_Text_MarekDefeat
	msgbox SnowRoute14_Text_MarekPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Halden::
	trainerbattle_single TRAINER_SNOW_R14_9_HALDEN, SnowRoute14_Text_HaldenIntro, SnowRoute14_Text_HaldenDefeat
	msgbox SnowRoute14_Text_HaldenPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_Text_CinderIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute14_Text_CinderDefeat:
	.string "That was incredible...$"

SnowRoute14_Text_CinderPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute14_Text_MarlowIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute14_Text_MarlowDefeat:
	.string "I didn't expect that...$"

SnowRoute14_Text_MarlowPostBattle:
	.string "Good luck on your journey.$"

SnowRoute14_Text_CassiaIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute14_Text_CassiaDefeat:
	.string "You're stronger than I thought!$"

SnowRoute14_Text_CassiaPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowRoute14_Text_ForgeIntro:
	.string "You look tough, but I'm tougher!$"

SnowRoute14_Text_ForgeDefeat:
	.string "Wow, I lost...$"

SnowRoute14_Text_ForgePostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowRoute14_Text_VestaIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowRoute14_Text_VestaDefeat:
	.string "I need to train more...$"

SnowRoute14_Text_VestaPostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowRoute14_Text_EmberIntro:
	.string "No one passes without a fight!$"

SnowRoute14_Text_EmberDefeat:
	.string "You really got me...$"

SnowRoute14_Text_EmberPostBattle:
	.string "You've got real talent.$"

SnowRoute14_Text_VexIntro:
	.string "I won't go easy on you!$"

SnowRoute14_Text_VexDefeat:
	.string "Not bad at all...$"

SnowRoute14_Text_VexPostBattle:
	.string "Keep pushing forward!$"

SnowRoute14_Text_MarekIntro:
	.string "Ready? Here I come!$"

SnowRoute14_Text_MarekDefeat:
	.string "I'll remember this battle!$"

SnowRoute14_Text_MarekPostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"

SnowRoute14_Text_HaldenIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute14_Text_HaldenDefeat:
	.string "That was incredible...$"

SnowRoute14_Text_HaldenPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"
