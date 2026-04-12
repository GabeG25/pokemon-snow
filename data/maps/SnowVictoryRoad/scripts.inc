SnowVictoryRoad_MapScripts::
	.byte 0

SnowVictoryRoad_EventScript_Soleil::
	trainerbattle_single TRAINER_SNOW_VR_1_SOLEIL, SnowVictoryRoad_Text_SoleilIntro, SnowVictoryRoad_Text_SoleilDefeat
	msgbox SnowVictoryRoad_Text_SoleilPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Maren::
	trainerbattle_single TRAINER_SNOW_VR_2_MAREN, SnowVictoryRoad_Text_MarenIntro, SnowVictoryRoad_Text_MarenDefeat
	msgbox SnowVictoryRoad_Text_MarenPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Dune::
	trainerbattle_single TRAINER_SNOW_VR_3_DUNE, SnowVictoryRoad_Text_DuneIntro, SnowVictoryRoad_Text_DuneDefeat
	msgbox SnowVictoryRoad_Text_DunePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Neve::
	trainerbattle_single TRAINER_SNOW_VR_4_NEVE, SnowVictoryRoad_Text_NeveIntro, SnowVictoryRoad_Text_NeveDefeat
	msgbox SnowVictoryRoad_Text_NevePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Pyre::
	trainerbattle_single TRAINER_SNOW_VR_5_PYRE, SnowVictoryRoad_Text_PyreIntro, SnowVictoryRoad_Text_PyreDefeat
	msgbox SnowVictoryRoad_Text_PyrePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Jinx::
	trainerbattle_single TRAINER_SNOW_VR_6_JINX, SnowVictoryRoad_Text_JinxIntro, SnowVictoryRoad_Text_JinxDefeat
	msgbox SnowVictoryRoad_Text_JinxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Zeno::
	trainerbattle_single TRAINER_SNOW_VR_7_ZENO, SnowVictoryRoad_Text_ZenoIntro, SnowVictoryRoad_Text_ZenoDefeat
	msgbox SnowVictoryRoad_Text_ZenoPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Kyros::
	trainerbattle_single TRAINER_SNOW_VR_8_KYROS, SnowVictoryRoad_Text_KyrosIntro, SnowVictoryRoad_Text_KyrosDefeat
	msgbox SnowVictoryRoad_Text_KyrosPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_Text_SoleilIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowVictoryRoad_Text_SoleilDefeat:
	.string "That was incredible...$"

SnowVictoryRoad_Text_SoleilPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowVictoryRoad_Text_MarenIntro:
	.string "A challenger? Perfect timing!$"

SnowVictoryRoad_Text_MarenDefeat:
	.string "I didn't expect that...$"

SnowVictoryRoad_Text_MarenPostBattle:
	.string "Good luck on your journey.$"

SnowVictoryRoad_Text_DuneIntro:
	.string "I've been training for this!\nBring it on!$"

SnowVictoryRoad_Text_DuneDefeat:
	.string "You're stronger than I thought!$"

SnowVictoryRoad_Text_DunePostBattle:
	.string "I'll be training hard for\nnext time we meet.$"

SnowVictoryRoad_Text_NeveIntro:
	.string "You look tough, but I'm tougher!$"

SnowVictoryRoad_Text_NeveDefeat:
	.string "Wow, I lost...$"

SnowVictoryRoad_Text_NevePostBattle:
	.string "You should rest at the next\ntown if you can.$"

SnowVictoryRoad_Text_PyreIntro:
	.string "Hey! You're a trainer too?\nLet's battle!$"

SnowVictoryRoad_Text_PyreDefeat:
	.string "I need to train more...$"

SnowVictoryRoad_Text_PyrePostBattle:
	.string "The wild POKéMON around here\ncan be tricky. Stay alert.$"

SnowVictoryRoad_Text_JinxIntro:
	.string "No one passes without a fight!$"

SnowVictoryRoad_Text_JinxDefeat:
	.string "You really got me...$"

SnowVictoryRoad_Text_JinxPostBattle:
	.string "You've got real talent.$"

SnowVictoryRoad_Text_ZenoIntro:
	.string "I won't go easy on you!$"

SnowVictoryRoad_Text_ZenoDefeat:
	.string "Not bad at all...$"

SnowVictoryRoad_Text_ZenoPostBattle:
	.string "Keep pushing forward!$"

SnowVictoryRoad_Text_KyrosIntro:
	.string "Ready? Here I come!$"

SnowVictoryRoad_Text_KyrosDefeat:
	.string "I'll remember this battle!$"

SnowVictoryRoad_Text_KyrosPostBattle:
	.string "I've got nothing left to say.\nJust... wow.$"
