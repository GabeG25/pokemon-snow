SolaceTown_MapScripts::
	.byte 0

SolaceTown_EventScript_GymLeaderErin::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F17_ERIN, SolaceTown_EventScript_ErinDefeated
	goto_if_unset FLAG_BADGE06_GET, SolaceTown_EventScript_ErinNeedBadge
	msgbox SolaceTown_Text_ErinIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F17_ERIN, SolaceTown_Text_ErinDefeat
	setflag FLAG_SNOW_BEAT_F17_ERIN
	setflag FLAG_BADGE07_GET
	msgbox SolaceTown_Text_ErinPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM36, 1
	msgbox SolaceTown_Text_ErinGiveTM, MSGBOX_DEFAULT
	release
	end

SolaceTown_EventScript_ErinDefeated::
	msgbox SolaceTown_Text_ErinPostBattle, MSGBOX_DEFAULT
	release
	end

SolaceTown_EventScript_ErinNeedBadge::
	msgbox SolaceTown_Text_ErinLocked, MSGBOX_DEFAULT
	release
	end

SolaceTown_Text_ErinIntro:
	.string "ERIN: Welcome to Solace.\p"
	.string "The earth here remembers older\n"
	.string "truths. My POKEMON know them too.\p"
	.string "Show me yours.$"

SolaceTown_Text_ErinDefeat:
	.string "ERIN: The earth yields to you.$"

SolaceTown_Text_ErinPostBattle:
	.string "ERIN: You've earned the\n"
	.string "BEDROCK BADGE.$"

SolaceTown_Text_ErinGiveTM:
	.string "ERIN: Take TM36 - EARTHQUAKE.\n"
	.string "Use it to shake the earth itself.$"

SolaceTown_Text_ErinLocked:
	.string "ERIN: Six badges first, young one.$"
