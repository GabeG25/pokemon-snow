PinegroveCity_MapScripts::
	.byte 0

@ ===== Gym 2 Cedar (Grass type) =====

PinegroveCity_EventScript_GymLeaderCedar::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F6_CEDAR, PinegroveCity_EventScript_CedarDefeated
	goto_if_unset FLAG_BADGE01_GET, PinegroveCity_EventScript_CedarNeedBadge1
	msgbox PinegroveCity_Text_CedarIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F6_CEDAR, PinegroveCity_Text_CedarDefeat
	setflag FLAG_SNOW_BEAT_F6_CEDAR
	setflag FLAG_BADGE02_GET
	msgbox PinegroveCity_Text_CedarPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM07, 1
	msgbox PinegroveCity_Text_CedarGiveTM, MSGBOX_DEFAULT
	release
	end

PinegroveCity_EventScript_CedarDefeated::
	msgbox PinegroveCity_Text_CedarPostBattle, MSGBOX_DEFAULT
	release
	end

PinegroveCity_EventScript_CedarNeedBadge1::
	msgbox PinegroveCity_Text_CedarLocked, MSGBOX_DEFAULT
	release
	end

@ ===== Toxic Orb NPC Gift =====

PinegroveCity_EventScript_ToxicOrbNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_TOXIC_ORB, PinegroveCity_EventScript_ToxicOrbDone
	msgbox PinegroveCity_Text_ToxicOrbIntro, MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_ORB, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_TOXIC_ORB
	msgbox PinegroveCity_Text_ToxicOrbGiven, MSGBOX_DEFAULT
	release
	end

PinegroveCity_EventScript_ToxicOrbDone::
	msgbox PinegroveCity_Text_ToxicOrbPost, MSGBOX_DEFAULT
	release
	end

@ ===== Old Rod Fishing NPC =====

PinegroveCity_EventScript_FishingRodNPC::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_ROD, PinegroveCity_EventScript_FishingRodDone
	msgbox PinegroveCity_Text_FishingRodIntro, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox PinegroveCity_Text_FishingRodGiven, MSGBOX_DEFAULT
	release
	end

PinegroveCity_EventScript_FishingRodDone::
	msgbox PinegroveCity_Text_FishingRodPost, MSGBOX_DEFAULT
	release
	end

@ ===== Text =====

PinegroveCity_Text_CedarIntro:
	.string "CEDAR: Welcome to my garden.\p"
	.string "Even in endless winter, life finds\n"
	.string "a way to grow. My POKEMON prove it.\p"
	.string "Show me what you've grown, trainer.$"

PinegroveCity_Text_CedarDefeat:
	.string "CEDAR: Astonishing growth.\n"
	.string "You've earned this.$"

PinegroveCity_Text_CedarPostBattle:
	.string "CEDAR: You've earned the\n"
	.string "FROSTLEAF BADGE.\p"
	.string "{PLAYER} received the\n"
	.string "FROSTLEAF BADGE!$"

PinegroveCity_Text_CedarGiveTM:
	.string "CEDAR: Take this TM as well.\p"
	.string "TM07 contains GIGA DRAIN.\n"
	.string "It absorbs enemy HP - a fitting\l"
	.string "reward for proving yourself.$"

PinegroveCity_Text_CedarLocked:
	.string "CEDAR: Earn your first badge before\n"
	.string "challenging me, trainer.$"

PinegroveCity_Text_ToxicOrbIntro:
	.string "RESEARCHER: I've been studying how\n"
	.string "certain POKEMON thrive on toxins.\p"
	.string "This orb is too dangerous for my\n"
	.string "lab work - a trainer might find\l"
	.string "a use for it.$"

PinegroveCity_Text_ToxicOrbGiven:
	.string "{PLAYER} received the TOXIC ORB!$"

PinegroveCity_Text_ToxicOrbPost:
	.string "RESEARCHER: Handle that orb\n"
	.string "carefully.$"

PinegroveCity_Text_FishingRodIntro:
	.string "FISHERMAN: You look like a trainer\n"
	.string "who might enjoy fishing!\p"
	.string "Here, take this OLD ROD.\n"
	.string "Cast it near water to catch fish.$"

PinegroveCity_Text_FishingRodGiven:
	.string "{PLAYER} received the OLD ROD!$"

PinegroveCity_Text_FishingRodPost:
	.string "FISHERMAN: Catching anything\n"
	.string "good out there?$"
