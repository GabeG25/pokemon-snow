IcespireTown_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Silvan — Gym 1 Leader (Ice), Pro-Veil ignorant voice
@ Warm, community-proud, grateful to Director Tyrell,
@ genuinely believes the winter is a gift to Boralyss
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_GymLeaderSilvan::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F3_SILVAN, IcespireTown_EventScript_SilvanDefeated
	msgbox IcespireTown_Text_SilvanIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F3_SILVAN, IcespireTown_Text_SilvanDefeat
	setflag FLAG_SNOW_BEAT_F3_SILVAN
	setflag FLAG_BADGE01_GET
	msgbox IcespireTown_Text_SilvanPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM03, 1
	msgbox IcespireTown_Text_SilvanGiveTM, MSGBOX_DEFAULT
	clearflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
	release
	end

IcespireTown_EventScript_SilvanDefeated::
	msgbox IcespireTown_Text_SilvanPostDefeat, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Asher F4 — Post-Gym 1 rematch
@ Compounding frustration, still not Veil yet (F14)
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_AsherF4::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F4_ASHER, IcespireTown_EventScript_AsherF4Defeated
	msgbox IcespireTown_Text_AsherF4Intro, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq IcespireTown_EventScript_AsherF4VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq IcespireTown_EventScript_AsherF4VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq IcespireTown_EventScript_AsherF4VariantC
	end

IcespireTown_EventScript_AsherF4VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_A, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_B, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_C, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4AfterBattle::
	setflag FLAG_SNOW_BEAT_F4_ASHER
	msgbox IcespireTown_Text_AsherF4PostBattle, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_AsherF4Defeated::
	msgbox IcespireTown_Text_AsherF4PostDefeat, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Wide Lens NPC gift
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_WideLensNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_WIDE_LENS, IcespireTown_EventScript_WideLensDone
	msgbox IcespireTown_Text_WideLensIntro, MSGBOX_DEFAULT
	giveitem ITEM_WIDE_LENS, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_WIDE_LENS
	msgbox IcespireTown_Text_WideLensGiven, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_WideLensDone::
	msgbox IcespireTown_Text_WideLensPost, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Roughneck Move Tutor
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_RoughneckTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, IcespireTown_EventScript_RoughneckLocked
	msgbox IcespireTown_Text_RoughneckIntro, MSGBOX_DEFAULT
	msgbox IcespireTown_Text_RoughneckOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq IcespireTown_EventScript_RoughneckTeach
	msgbox IcespireTown_Text_RoughneckDecline, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckTeach::
	checkmoney 2000
	compare VAR_RESULT, FALSE
	goto_if_eq IcespireTown_EventScript_RoughneckNoMoney
	removemoney 2000
	setvar VAR_0x8005, MOVE_BODY_SLAM
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq IcespireTown_EventScript_RoughneckCancel
	msgbox IcespireTown_Text_RoughneckTaught, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckCancel::
	msgbox IcespireTown_Text_RoughneckDecline, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckNoMoney::
	msgbox IcespireTown_Text_RoughneckNoMoney, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckLocked::
	msgbox IcespireTown_Text_RoughneckLocked, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Pro-Veil citizen - establishes Act 1 "Beautiful Lie"
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_ProVeilCitizen::
	lock
	faceplayer
	msgbox IcespireTown_Text_CitizenPraise, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

IcespireTown_Text_SilvanIntro:
	.string "SILVAN: Welcome, welcome!\p"
	.string "Beautiful day, isn't it?\n"
	.string "Fresh snow on the peaks, crisp\l"
	.string "air in the lungs - doesn't get\l"
	.string "better than this.\p"
	.string "I'm SILVAN, the ICESHARD GYM\n"
	.string "Leader. Keeper of the cold.\p"
	.string "You know, none of this would\n"
	.string "be possible without DIRECTOR\l"
	.string "TYRELL and his researchers.\p"
	.string "The perpetual winter they gave\n"
	.string "us - it's a blessing. Pokemon\l"
	.string "thrive in it. People are\l"
	.string "happier. I've never felt more\l"
	.string "connected to my craft.\p"
	.string "But I'm getting ahead of myself.\n"
	.string "You're here for a badge, not a\l"
	.string "sermon!\p"
	.string "Let me see what you're made of.$"

IcespireTown_Text_SilvanDefeat:
	.string "SILVAN: Oh my. Well done!$"

IcespireTown_Text_SilvanPostBattle:
	.string "SILVAN: Heh heh - that was\n"
	.string "splendid! Absolutely splendid!\p"
	.string "You've clearly trained in the\n"
	.string "cold before. You understand it.\p"
	.string "{PLAYER}, you have earned\n"
	.string "the ICESHARD BADGE!$"

IcespireTown_Text_SilvanGiveTM:
	.string "SILVAN: Oh - and take this.\p"
	.string "TM03: ICY WIND.\p"
	.string "It's a beautiful move. Slows\n"
	.string "opponents down and looks\l"
	.string "magnificent on a battlefield.\p"
	.string "You know, you should visit us\n"
	.string "again someday. Bring your team,\l"
	.string "enjoy the winter.\p"
	.string "The DIRECTOR promised us this\n"
	.string "will last forever. Isn't that\l"
	.string "wonderful?$"

IcespireTown_Text_SilvanPostDefeat:
	.string "SILVAN: Oh! {PLAYER}, good to\n"
	.string "see you again!\p"
	.string "Enjoying our lovely winter?\n"
	.string "I hope the DIRECTOR keeps his\l"
	.string "promise - I don't know what I'd\l"
	.string "do without the cold.$"

IcespireTown_Text_AsherF4Intro:
	.string "ASHER: Of course.\p"
	.string "Of COURSE you beat Silvan first.\p"
	.string "I've been up here for days.\n"
	.string "Days. I know his rotation, his\l"
	.string "leads, his switches. I was\l"
	.string "THIS close to -\p"
	.string "...\p"
	.string "You know what? Forget it.\n"
	.string "You want the ICESHARD BADGE?\p"
	.string "Then you can handle me.\n"
	.string "One more time.$"

IcespireTown_Text_AsherF4Defeat:
	.string "ASHER: No. No no no.$"

IcespireTown_Text_AsherF4PostBattle:
	.string "ASHER: ...\p"
	.string "I'm stronger than this.\n"
	.string "I'm SUPPOSED to be stronger\l"
	.string "than this.\p"
	.string "...\p"
	.string "Why does everything come so\n"
	.string "easy to you?\p"
	.string "My team is training harder\n"
	.string "than yours. I KNOW they are.\p"
	.string "So why -\p"
	.string "Never mind.\p"
	.string "I'll see you at Gym 2. And\n"
	.string "the one after that. And the\l"
	.string "one after that.\p"
	.string "Eventually, you'll run out of\n"
	.string "luck, {PLAYER}.$"

IcespireTown_Text_AsherF4PostDefeat:
	.string "ASHER: Still here? Still winning?\p"
	.string "Great. Fine. Whatever.\n"
	.string "I'm heading to Pinegrove.$"

IcespireTown_Text_WideLensIntro:
	.string "WORN-OUT TRAINER: That gym nearly\n"
	.string "did me in.\p"
	.string "Silvan's team - the hail, the\n"
	.string "evasion, his Piplup's SPEED...\p"
	.string "My POKEMON just couldn't land\n"
	.string "a hit.\p"
	.string "Here. I picked this up on R2 but\n"
	.string "I'm done battling for a while.\p"
	.string "Maybe it'll help you land more\n"
	.string "attacks than I did.$"

IcespireTown_Text_WideLensGiven:
	.string "{PLAYER} received the WIDE LENS!$"

IcespireTown_Text_WideLensPost:
	.string "WORN-OUT TRAINER: I think I'm\n"
	.string "going to retire and open a\l"
	.string "little cafe. Somewhere warm.$"

IcespireTown_Text_RoughneckIntro:
	.string "ROUGHNECK: Hey, you. Yeah, you.\p"
	.string "I've been watching trainers come\n"
	.string "and go through this gym for years.\p"
	.string "The ones who make it big always\n"
	.string "have the same thing in common -\l"
	.string "they don't JUST rely on type\l"
	.string "charts.\p"
	.string "They hit hard. They hit dirty.\n"
	.string "They SCRAP.\p"
	.string "I didn't learn to fight in any\n"
	.string "gym. You want me to teach your\l"
	.string "POKEMON how to actually brawl?$"

IcespireTown_Text_RoughneckOffer:
	.string "ROUGHNECK: I can teach BODY SLAM\n"
	.string "for 2000 yen.\p"
	.string "Big heavy hit. Might paralyze.\n"
	.string "Changes fights.\p"
	.string "Interested?$"

IcespireTown_Text_RoughneckDecline:
	.string "ROUGHNECK: Think about it. Door's\n"
	.string "always open.$"

IcespireTown_Text_RoughneckNoMoney:
	.string "ROUGHNECK: You're short. Come\n"
	.string "back when your wallet isn't.$"

IcespireTown_Text_RoughneckLocked:
	.string "ROUGHNECK: Kid, come back with a\n"
	.string "badge. I don't waste lessons on\l"
	.string "trainers who can't prove they\l"
	.string "can take a hit.$"

IcespireTown_Text_RoughneckTaught:
	.string "ROUGHNECK: BODY SLAM taught. Now\n"
	.string "go hit something with it.$"

IcespireTown_Text_CitizenPraise:
	.string "CITIZEN: Beautiful day, isn't it?\p"
	.string "I moved here from Slateport years\n"
	.string "ago. Couldn't stand the heat.\p"
	.string "Then DIRECTOR TYRELL and his\n"
	.string "researchers changed everything.\p"
	.string "This winter - it's a miracle.\n"
	.string "The air is clean, the POKEMON\l"
	.string "are thriving, crime is down...\p"
	.string "I don't know how he did it, but\n"
	.string "I trust him completely.\p"
	.string "Director Tyrell saved Boralyss.$"
