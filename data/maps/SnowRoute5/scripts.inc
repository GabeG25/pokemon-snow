SnowRoute5_MapScripts::
	.byte 0

SnowRoute5_EventScript_Knox::
	trainerbattle_single TRAINER_SNOW_R5_1_KNOX, SnowRoute5_Text_KnoxIntro, SnowRoute5_Text_KnoxDefeat
	msgbox SnowRoute5_Text_KnoxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Lina::
	trainerbattle_single TRAINER_SNOW_R5_2_LINA, SnowRoute5_Text_LinaIntro, SnowRoute5_Text_LinaDefeat
	msgbox SnowRoute5_Text_LinaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Grunt1::
	trainerbattle_single TRAINER_SNOW_R5_3_GRUNT, SnowRoute5_Text_Grunt1Intro, SnowRoute5_Text_Grunt1Defeat
	msgbox SnowRoute5_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Grunt2::
	trainerbattle_single TRAINER_SNOW_R5_4_GRUNT, SnowRoute5_Text_Grunt2Intro, SnowRoute5_Text_Grunt2Defeat
	msgbox SnowRoute5_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Grunt3::
	trainerbattle_single TRAINER_SNOW_R5_5_GRUNT, SnowRoute5_Text_Grunt3Intro, SnowRoute5_Text_Grunt3Defeat
	msgbox SnowRoute5_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Grunt4::
	trainerbattle_single TRAINER_SNOW_R5_6_GRUNT, SnowRoute5_Text_Grunt4Intro, SnowRoute5_Text_Grunt4Defeat
	msgbox SnowRoute5_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_Text_KnoxIntro:
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute5_Text_KnoxDefeat:
	.string "That was incredible...$"

SnowRoute5_Text_KnoxPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute5_Text_LinaIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute5_Text_LinaDefeat:
	.string "I didn't expect that...$"

SnowRoute5_Text_LinaPostBattle:
	.string "Good luck on your journey.$"

SnowRoute5_Text_Grunt1Intro:
	.string "Get out of our way!$"

SnowRoute5_Text_Grunt1Defeat:
	.string "Lord Tyrell will hear about this!$"

SnowRoute5_Text_Grunt1PostBattle:
	.string "This isn't over...$"

SnowRoute5_Text_Grunt2Intro:
	.string "For Lord Tyrell!$"

SnowRoute5_Text_Grunt2Defeat:
	.string "You got lucky...$"

SnowRoute5_Text_Grunt2PostBattle:
	.string "We have more important things\nto do than deal with you.$"

SnowRoute5_Text_Grunt3Intro:
	.string "Team Veil will not be stopped!$"

SnowRoute5_Text_Grunt3Defeat:
	.string "This changes nothing...$"

SnowRoute5_Text_Grunt3PostBattle:
	.string "Team Veil's plan is already\nin motion. You're too late.$"

SnowRoute5_Text_Grunt4Intro:
	.string "You dare challenge Team Veil?$"

SnowRoute5_Text_Grunt4Defeat:
	.string "Tch... you'll regret this!$"

SnowRoute5_Text_Grunt4PostBattle:
	.string "You don't know what you're\ngetting into...$"
