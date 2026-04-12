IcespireTown_MapScripts::
	.byte 0

@ ===== Gym 1 Silvan (Ice type) =====
@ Placeholder: battle triggers from an NPC in town until gym interior exists.

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
	@ Unlock next rival battle
	clearflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
	release
	end

IcespireTown_EventScript_SilvanDefeated::
	msgbox IcespireTown_Text_SilvanPostBattle, MSGBOX_DEFAULT
	release
	end

@ ===== Asher F4 (after Gym 1) =====
@ A=Fire/Combusken, B=Water/Marshtomp, C=Grass/Grovyle

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
	msgbox IcespireTown_Text_AsherF4PostBattle, MSGBOX_DEFAULT
	release
	end

@ ===== Wide Lens NPC gift (v17 §16) =====

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

@ ===== Roughneck Move Tutor (v17 §15, Post-Gym 1) =====
@ Simplified: teaches Body Slam for 2000 yen (single move placeholder until
@ scrollable multichoice list is set up for full 6-move selection)

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

@ ===== Text =====

IcespireTown_Text_SilvanIntro:
	.string "SILVAN: Welcome to my gym.\p"
	.string "You've come seeking the ICESHARD\n"
	.string "BADGE, haven't you?\p"
	.string "I won't make this easy.\n"
	.string "The cold reveals all weakness.$"

IcespireTown_Text_SilvanDefeat:
	.string "SILVAN: Impressive.\n"
	.string "The cold didn't break you.$"

IcespireTown_Text_SilvanPostBattle:
	.string "SILVAN: You've earned the\n"
	.string "ICESHARD BADGE.\p"
	.string "{PLAYER} received the\n"
	.string "ICESHARD BADGE!$"

IcespireTown_Text_SilvanGiveTM:
	.string "SILVAN: Take this as well.\p"
	.string "TM03 contains ICY WIND.\n"
	.string "It lowers the opponent's speed.\p"
	.string "A fitting tool for cold battles.$"

IcespireTown_Text_AsherF4Intro:
	.string "ASHER: {PLAYER}! Heard you beat\n"
	.string "Silvan!\p"
	.string "Don't think that means you're\n"
	.string "ahead of me. I've been training\l"
	.string "hard too - let me show you!$"

IcespireTown_Text_AsherF4Defeat:
	.string "ASHER: Gah! Not again!$"

IcespireTown_Text_AsherF4PostBattle:
	.string "ASHER: You got lucky.\p"
	.string "I'll catch up - count on it.\n"
	.string "See you at Gym 2!$"

IcespireTown_Text_WideLensIntro:
	.string "TRAINER: That gym nearly did me in.\p"
	.string "My POKEMON couldn't land a hit.\p"
	.string "Here - I picked this up on R2 but\n"
	.string "I'm done with battling for now.\p"
	.string "Maybe it'll help you.$"

IcespireTown_Text_WideLensGiven:
	.string "{PLAYER} received the WIDE LENS!$"

IcespireTown_Text_WideLensPost:
	.string "TRAINER: Good luck out there.$"

IcespireTown_Text_RoughneckIntro:
	.string "ROUGHNECK: I didn't learn to fight\n"
	.string "in any gym.\p"
	.string "Want me to teach your POKEMON\n"
	.string "how to scrap?$"

IcespireTown_Text_RoughneckOffer:
	.string "ROUGHNECK: I can teach BODY SLAM.\n"
	.string "Costs 2000 yen. Interested?$"

IcespireTown_Text_RoughneckDecline:
	.string "ROUGHNECK: Suit yourself.$"

IcespireTown_Text_RoughneckNoMoney:
	.string "ROUGHNECK: Not enough yen.\n"
	.string "Come back when you've got it.$"

IcespireTown_Text_RoughneckLocked:
	.string "ROUGHNECK: Earn your first badge\n"
	.string "before you come asking me for\l"
	.string "anything, kid.$"

IcespireTown_Text_RoughneckTaught:
	.string "ROUGHNECK: Done. BODY SLAM taught.$"
