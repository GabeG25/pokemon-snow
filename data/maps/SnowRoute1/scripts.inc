SnowRoute1_MapScripts::
	.byte 0

@ ===== Autumn catching tutorial + F2 battle =====
@ Sequence:
@ 1. Player enters mandatory grass -> Autumn stops them
@ 2. Autumn explains catching and demonstrates (scripted cutscene)
@ 3. Gives player 5 Poke Balls
@ 4. Challenges player to F2 battle (Sentret + starter)
@ 5. Variant A/B/C based on player's starter (A=player picked Treecko, etc.)

SnowRoute1_EventScript_AutumnTutorial::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F2_AUTUMN, SnowRoute1_EventScript_AutumnDefeated
	goto_if_set FLAG_SNOW_AUTUMN_TUTORIAL_DONE, SnowRoute1_EventScript_AutumnBattleIntro
	msgbox SnowRoute1_Text_AutumnIntro, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnCatchingExplanation, MSGBOX_DEFAULT
	@ Scripted catch demonstration
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
	@ A=Mudkip, B=Treecko, C=Torchic
	@ Player Treecko -> Autumn Torchic (C)
	@ Player Torchic -> Autumn Mudkip  (A)
	@ Player Mudkip  -> Autumn Treecko (B)
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute1_EventScript_AutumnVariantC
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute1_EventScript_AutumnVariantA
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute1_EventScript_AutumnVariantB
	end

@ Autumn's starter also has type advantage over player
@ Player Treecko(0) -> Autumn Torchic (A) [F2_A has Mudkip though, let me check]
@ Actually Autumn_A has Mudkip (from trainers.party earlier)
@ So A=Mudkip, B=Treecko, C=Torchic... need to map by advantage
@ Player Treecko (weak to Fire)  -> Autumn Torchic -> variant with Torchic
@ Player Torchic (weak to Water) -> Autumn Mudkip  -> variant with Mudkip
@ Player Mudkip  (weak to Grass) -> Autumn Treecko -> variant with Treecko

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
	.string "AUTUMN: {PLAYER}! Hold up!\p"
	.string "I was hoping to catch you out here.\n"
	.string "Have you caught a wild POKEMON yet?\p"
	.string "You're going to need a full team\n"
	.string "if you want to take on the gyms!$"

SnowRoute1_Text_AutumnCatchingExplanation:
	.string "AUTUMN: Catching is simple - let me\n"
	.string "show you how it's done.\p"
	.string "Weaken a wild POKEMON first in\n"
	.string "battle, then throw a POKE BALL.\p"
	.string "Watch me!$"

SnowRoute1_Text_AutumnDemoCatch:
	.string "AUTUMN found a wild SENTRET!\p"
	.string "She weakened it with her starter\n"
	.string "and threw a POKE BALL...\p"
	.string "...\p"
	.string "GOTCHA! SENTRET was caught!$"

SnowRoute1_Text_AutumnGiveBalls:
	.string "AUTUMN: See? Easy!\p"
	.string "Here, take some of my spare balls\n"
	.string "so you can try it yourself.$"

SnowRoute1_Text_AutumnChallenge:
	.string "AUTUMN: Now that I've got my SENTRET,\n"
	.string "how about a quick battle?\p"
	.string "I want to see how your starter\n"
	.string "stacks up against mine!$"

SnowRoute1_Text_AutumnDefeat:
	.string "AUTUMN: Whoa! You're stronger\n"
	.string "than I expected!$"

SnowRoute1_Text_AutumnPostBattle:
	.string "AUTUMN: That was a great battle!\p"
	.string "Keep pushing forward - I'll be\n"
	.string "training too. See you down the road!$"

SnowRoute1_Text_AutumnPostTutorial:
	.string "AUTUMN: Catch some good POKEMON\n"
	.string "out there! See you soon.$"

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
	.string "Think you can handle the cold?\nLet's find out!$"

SnowRoute1_Text_NoelDefeat:
	.string "That was incredible...$"

SnowRoute1_Text_NoelPostBattle:
	.string "The path ahead gets tougher.\nBe careful out there.$"

SnowRoute1_Text_EliseIntro:
	.string "A challenger? Perfect timing!$"

SnowRoute1_Text_EliseDefeat:
	.string "I didn't expect that...$"

SnowRoute1_Text_ElisePostBattle:
	.string "Good luck on your journey.$"

SnowRoute1_Text_KaiIntro:
	.string "I've been training for this!\nBring it on!$"

SnowRoute1_Text_KaiDefeat:
	.string "You're stronger than I thought!$"

SnowRoute1_Text_KaiPostBattle:
	.string "I'll be training hard for\nnext time we meet.$"
