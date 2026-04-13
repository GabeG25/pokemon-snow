SnowRoute1_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn F2 — Catching tutorial + first rival battle
@ Warm, nerdy, research-passionate voice
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_AutumnTutorial::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F2_AUTUMN, SnowRoute1_EventScript_AutumnDefeated
	goto_if_set FLAG_SNOW_AUTUMN_TUTORIAL_DONE, SnowRoute1_EventScript_AutumnBattleIntro
	msgbox SnowRoute1_Text_AutumnIntro, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnScienceTangent, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnCatchingExplanation, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, SnowRoute1_Movement_AutumnToGrass
	waitmovement 0
	msgbox SnowRoute1_Text_AutumnDemoCatch, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, SnowRoute1_Movement_AutumnReturn
	waitmovement 0
	msgbox SnowRoute1_Text_AutumnGiveBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_AUTUMN_TUTORIAL_DONE
	setflag FLAG_SNOW_GOT_POKEBALLS
	goto SnowRoute1_EventScript_AutumnBattleIntro
	end

SnowRoute1_EventScript_AutumnBattleIntro::
	msgbox SnowRoute1_Text_AutumnChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute1_EventScript_AutumnVariantC
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute1_EventScript_AutumnVariantA
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute1_EventScript_AutumnVariantB
	end

SnowRoute1_EventScript_AutumnVariantA::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_A, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle
	end

SnowRoute1_EventScript_AutumnVariantB::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_B, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle
	end

SnowRoute1_EventScript_AutumnVariantC::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_C, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle
	end

SnowRoute1_EventScript_AutumnAfterBattle::
	setflag FLAG_SNOW_BEAT_F2_AUTUMN
	msgbox SnowRoute1_Text_AutumnPostBattle, MSGBOX_DEFAULT
	release
	end

SnowRoute1_EventScript_AutumnDefeated::
	msgbox SnowRoute1_Text_AutumnPostTutorial, MSGBOX_DEFAULT
	release
	end

SnowRoute1_Movement_AutumnToGrass:
	walk_down
	walk_down
	step_end

SnowRoute1_Movement_AutumnReturn:
	walk_up
	walk_up
	step_end

SnowRoute1_Text_AutumnIntro:
	.string "AUTUMN: {PLAYER}!\n"
	.string "Oh wow, you're already out here?\p"
	.string "I thought I'd catch up to you\n"
	.string "before you left Dawnflake, but\l"
	.string "you move fast!\p"
	.string "I saw Asher heading back to\n"
	.string "train. He was... sulking.\p"
	.string "Did you beat him? You beat him,\n"
	.string "didn't you. He always sulks when\l"
	.string "he loses.$"

SnowRoute1_Text_AutumnScienceTangent:
	.string "AUTUMN: So, okay, real talk - I've\n"
	.string "been DYING to show someone this.\p"
	.string "Look at that SENTRET over there.\n"
	.string "See how its tail is twitching?\p"
	.string "It's not cold. It's thermoregulating!\n"
	.string "Wild Pokemon in Boralyss have\l"
	.string "adapted to radiate heat through\l"
	.string "their extremities.\p"
	.string "Basically, the tail IS the heater.\n"
	.string "Isn't that incredible?\p"
	.string "...Sorry. Sorry. I know you\n"
	.string "didn't ask. I get excited.$"

SnowRoute1_Text_AutumnCatchingExplanation:
	.string "AUTUMN: Anyway - have you caught\n"
	.string "a wild Pokemon yet?\p"
	.string "No? Okay, let me show you.\n"
	.string "Watch carefully!$"

SnowRoute1_Text_AutumnDemoCatch:
	.string "AUTUMN weakened a wild SENTRET\n"
	.string "with her starter!\p"
	.string "She waited until it was tired,\n"
	.string "then threw a POKE BALL...\p"
	.string "...\p"
	.string "GOTCHA! The SENTRET was caught!\p"
	.string "AUTUMN: YES! On the first try!\n"
	.string "This one's coming with me for\l"
	.string "further study. Look at that\l"
	.string "adorable face!$"

SnowRoute1_Text_AutumnGiveBalls:
	.string "AUTUMN: See how it works?\p"
	.string "Weaken them first - don't just\n"
	.string "throw balls at healthy Pokemon,\l"
	.string "that's a waste.\p"
	.string "Status effects help too - sleep\n"
	.string "and paralysis are huge.\p"
	.string "Here, take some of my spare\n"
	.string "balls. I bought way too many.\p"
	.string "You'll need them more than I do.$"

SnowRoute1_Text_AutumnChallenge:
	.string "AUTUMN: Oh! Since we're both out\n"
	.string "here anyway, let's battle!\p"
	.string "I want to see how your starter's\n"
	.string "adapting. It's for... research.\p"
	.string "(Also it's just fun. Don't tell\n"
	.string "my field notes I said that.)$"

SnowRoute1_Text_AutumnDefeat:
	.string "AUTUMN: Wow! Okay, no pity there!$"

SnowRoute1_Text_AutumnPostBattle:
	.string "AUTUMN: That was a GREAT battle!\p"
	.string "Your starter's already showing\n"
	.string "adaptation instincts. Did you\l"
	.string "see how it responded to the cold?\p"
	.string "I'm going to keep documenting\n"
	.string "wild populations along this route.\p"
	.string "You go ahead - Powderpath Village\n"
	.string "is just south of here.\p"
	.string "Good luck, {PLAYER}! Don't be\n"
	.string "a stranger!$"

SnowRoute1_Text_AutumnPostTutorial:
	.string "AUTUMN: I'm cataloguing the wild\n"
	.string "SENTRET population here.\p"
	.string "Did you know they form family\n"
	.string "groups? It's SO cute.\p"
	.string "Anyway - go get 'em! I'll catch\n"
	.string "up with you down the road!$"

@ ═══════════════════════════════════════════════════════════
@ Route trainers (unchanged from previous batch)
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_Noel::
	trainerbattle_single TRAINER_SNOW_R1_1_NOEL, SnowRoute1_Text_NoelIntro, SnowRoute1_Text_NoelDefeat
	msgbox SnowRoute1_Text_NoelPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_EventScript_Elise::
	trainerbattle_single TRAINER_SNOW_R1_2_ELISE, SnowRoute1_Text_EliseIntro, SnowRoute1_Text_EliseDefeat
	msgbox SnowRoute1_Text_ElisePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_EventScript_Kai::
	trainerbattle_single TRAINER_SNOW_R1_3_KAI, SnowRoute1_Text_KaiIntro, SnowRoute1_Text_KaiDefeat
	msgbox SnowRoute1_Text_KaiPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute1_Text_NoelIntro:
	.string "I was born in this snow!\n"
	.string "Let's see if you can keep up!$"

SnowRoute1_Text_NoelDefeat:
	.string "That was incredible...$"

SnowRoute1_Text_NoelPostBattle:
	.string "Mom says everyone from outside\n"
	.string "the region is slower in the cold.\p"
	.string "I guess that's not always true!$"

SnowRoute1_Text_EliseIntro:
	.string "Oh! A traveler!\n"
	.string "I've never battled one before!$"

SnowRoute1_Text_EliseDefeat:
	.string "I didn't expect that at all...$"

SnowRoute1_Text_ElisePostBattle:
	.string "Good luck on the rest of your\n"
	.string "journey! Be safe out there!$"

SnowRoute1_Text_KaiIntro:
	.string "You there! Stop!\n"
	.string "A trainer doesn't pass without\n"
	.string "a battle - that's the rule of\n"
	.string "the trail!$"

SnowRoute1_Text_KaiDefeat:
	.string "Hah! A good fight!$"

SnowRoute1_Text_KaiPostBattle:
	.string "Head on to Powderpath. Buy some\n"
	.string "ice cream while you're there -\n"
	.string "the vendor makes it old-school.$"
