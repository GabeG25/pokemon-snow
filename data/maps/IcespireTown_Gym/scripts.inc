IcespireTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcespireTown_Gym_OnTransition
	.byte 0

@ Force the player to face north on warp-in so they're staring up
@ the gym at Silvan. The bottom doormat at (6,16) is a flat tile
@ (MB_NORMAL), so without this script the engine doesn't auto-face.
IcespireTown_Gym_OnTransition::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

@ ═══════════════════════════════════════════════════════════
@ Silvan — Gym 1 Leader (Ice), warm, proud, Pro-Veil ignorant
@ ═══════════════════════════════════════════════════════════

IcespireTown_Gym_EventScript_Silvan::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F3_SILVAN, IcespireTown_Gym_EventScript_SilvanPostVictory
	msgbox IcespireTown_Gym_Text_SilvanIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F3_SILVAN, IcespireTown_Gym_Text_SilvanDefeat
	goto IcespireTown_Gym_EventScript_SilvanDefeated
	end

IcespireTown_Gym_EventScript_SilvanDefeated::
	message IcespireTown_Gym_Text_ReceivedIceshardBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox IcespireTown_Gym_Text_IceshardBadgeInfo, MSGBOX_DEFAULT
	setflag FLAG_SNOW_BEAT_F3_SILVAN
	setflag FLAG_BADGE01_GET
	goto_if_set FLAG_SNOW_GOT_TM03_ICY_WIND, IcespireTown_Gym_EventScript_SilvanSkipTM
	giveitem ITEM_TM03, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_TM03_ICY_WIND
	msgbox IcespireTown_Gym_Text_SilvanGiveTM, MSGBOX_DEFAULT
IcespireTown_Gym_EventScript_SilvanSkipTM::
	msgbox IcespireTown_Gym_Text_SilvanDirectorLine, MSGBOX_DEFAULT
	clearflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
	release
	end

IcespireTown_Gym_EventScript_SilvanPostVictory::
	msgbox IcespireTown_Gym_Text_SilvanPostVictory, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Gym Guide
@ ═══════════════════════════════════════════════════════════

IcespireTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F3_SILVAN, IcespireTown_Gym_EventScript_GymGuidePostVictory
	msgbox IcespireTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

IcespireTown_Gym_EventScript_GymGuidePostVictory::
	msgbox IcespireTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Gym Trainers — Boarder TUCKER + Skier NIECA
@ ═══════════════════════════════════════════════════════════

IcespireTown_Gym_EventScript_Tucker::
	trainerbattle_single TRAINER_SNOW_GYM1_TUCKER, IcespireTown_Gym_Text_TuckerIntro, IcespireTown_Gym_Text_TuckerDefeat
	msgbox IcespireTown_Gym_Text_TuckerPostBattle, MSGBOX_AUTOCLOSE
	end

IcespireTown_Gym_EventScript_Nieca::
	trainerbattle_single TRAINER_SNOW_GYM1_NIECA, IcespireTown_Gym_Text_NiecaIntro, IcespireTown_Gym_Text_NiecaDefeat
	msgbox IcespireTown_Gym_Text_NiecaPostBattle, MSGBOX_AUTOCLOSE
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

IcespireTown_Gym_Text_SilvanIntro:
	.string "SILVAN: Welcome, welcome!\p"
	.string "I'm SILVAN, LEADER of the\n"
	.string "ICESHARD GYM. Keeper of the\l"
	.string "cold.\p"
	.string "Beautiful day, isn't it? Fresh\n"
	.string "snow on the peaks, crisp air\l"
	.string "in the lungs.\p"
	.string "None of this would be possible\n"
	.string "without DIRECTOR TYRELL and his\l"
	.string "fine researchers. The winter\l"
	.string "they gave us - it's a blessing.\p"
	.string "POKEMON thrive in it. People\n"
	.string "are happier. I've never felt\l"
	.string "more connected to my craft.\p"
	.string "But I'm getting ahead of myself.\n"
	.string "You're here for a badge, not\l"
	.string "a sermon!\p"
	.string "Let me see what you're made of.$"

IcespireTown_Gym_Text_SilvanDefeat:
	.string "SILVAN: Oh my. Oh MY.\n"
	.string "Well done!$"

IcespireTown_Gym_Text_ReceivedIceshardBadge:
	.string "{PLAYER} received the ICESHARD\n"
	.string "BADGE from SILVAN.$"

IcespireTown_Gym_Text_IceshardBadgeInfo:
	.string "SILVAN: The ICESHARD BADGE is\n"
	.string "yours, {PLAYER}.\p"
	.string "Trainers up to level 20 will\n"
	.string "obey you without question now.\p"
	.string "And take this, too.$"

IcespireTown_Gym_Text_SilvanGiveTM:
	.string "{PLAYER} received TM03:\n"
	.string "ICY WIND.$"

IcespireTown_Gym_Text_SilvanDirectorLine:
	.string "SILVAN: ICY WIND is a beautiful\n"
	.string "move. Slows opponents and looks\l"
	.string "magnificent on a battlefield.\p"
	.string "You know - DIRECTOR TYRELL\n"
	.string "himself honored our gym with a\l"
	.string "visit last month.\p"
	.string "Such a polite man. He asked\n"
	.string "after the children. He\l"
	.string "remembered all their names.\p"
	.string "He promised the winter will\n"
	.string "last forever. A man that kind\l"
	.string "doesn't break a promise.\p"
	.string "Off you go, {PLAYER}. Show the\n"
	.string "rest of BORALYSS what the\l"
	.string "ICESHARD BADGE means.$"

IcespireTown_Gym_Text_SilvanPostVictory:
	.string "SILVAN: {PLAYER}! Good to see\n"
	.string "you again.\p"
	.string "Enjoying our lovely winter?\n"
	.string "I do hope the DIRECTOR keeps\l"
	.string "his promise. I don't know what\l"
	.string "I'd do without the cold.$"

IcespireTown_Gym_Text_GymGuideAdvice:
	.string "GYM GUIDE: Yo! First-timer?\p"
	.string "SILVAN runs an ICE gym. Permanent\n"
	.string "hail. Snow Cloak evasion. His\l"
	.string "PIPLUP is the ace.\p"
	.string "Fire, Fighting, Rock, Steel -\n"
	.string "those are your friends here.\p"
	.string "Good luck in there, trainer!$"

IcespireTown_Gym_Text_GymGuidePostVictory:
	.string "GYM GUIDE: That was something\n"
	.string "else!\p"
	.string "You should see the look on\n"
	.string "SILVAN'S face. He loves a good\l"
	.string "loss. Says it keeps him honest.\p"
	.string "On to the next gym, trainer!$"

IcespireTown_Gym_Text_TuckerIntro:
	.string "BOARDER TUCKER: Yo! Snow's perfect\n"
	.string "today.\p"
	.string "Lemme show you a real run!$"

IcespireTown_Gym_Text_TuckerDefeat:
	.string "BOARDER TUCKER: Wiped out!$"

IcespireTown_Gym_Text_TuckerPostBattle:
	.string "BOARDER TUCKER: That was clean.\p"
	.string "Beat SILVAN. Then come back\n"
	.string "so I can lose to you again.$"

IcespireTown_Gym_Text_NiecaIntro:
	.string "SKIER NIECA: I don't fall.\p"
	.string "Watch this carve.$"

IcespireTown_Gym_Text_NiecaDefeat:
	.string "SKIER NIECA: Lost my edge.$"

IcespireTown_Gym_Text_NiecaPostBattle:
	.string "SKIER NIECA: Beautiful run.\p"
	.string "Go win that ICESHARD BADGE.$"
