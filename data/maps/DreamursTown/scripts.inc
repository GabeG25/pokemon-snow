DreamursTown_MapScripts::
	.byte 0

DreamursTown_EventScript_GymLeaderFran::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F11_FRAN, DreamursTown_EventScript_FranDefeated
	goto_if_unset FLAG_BADGE03_GET, DreamursTown_EventScript_FranNeedBadge
	msgbox DreamursTown_Text_FranIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F11_FRAN, DreamursTown_Text_FranDefeat
	setflag FLAG_SNOW_BEAT_F11_FRAN
	setflag FLAG_BADGE04_GET
	msgbox DreamursTown_Text_FranPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM15, 1
	msgbox DreamursTown_Text_FranGiveTM, MSGBOX_DEFAULT
	release
	end

DreamursTown_EventScript_FranDefeated::
	msgbox DreamursTown_Text_FranPostBattle, MSGBOX_DEFAULT
	release
	end

DreamursTown_EventScript_FranNeedBadge::
	msgbox DreamursTown_Text_FranLocked, MSGBOX_DEFAULT
	release
	end

DreamursTown_Text_FranIntro:
	.string "FRAN: Dreams have power here.\p"
	.string "My POKEMON weave them into light\n"
	.string "and sound. Can you withstand them?$"

DreamursTown_Text_FranDefeat:
	.string "FRAN: Your resolve... is beautiful.$"

DreamursTown_Text_FranPostBattle:
	.string "FRAN: You've earned the\n"
	.string "DREAMVEIL BADGE.\p"
	.string "{PLAYER} received the\n"
	.string "DREAMVEIL BADGE!$"

DreamursTown_Text_FranGiveTM:
	.string "FRAN: And take TM15.\p"
	.string "DAZZLING GLEAM - a burst of light\n"
	.string "that dazzles all opponents.$"

DreamursTown_Text_FranLocked:
	.string "FRAN: You need three badges\n"
	.string "before challenging me.$"
