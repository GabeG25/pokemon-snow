SnowRoute1_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn F2 — Catching tutorial + first rival battle
@ Intercept trigger + direct-talk fallback
@ Warm, nerdy, research-passionate voice
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_AutumnTrigger::
	lockall
	goto_if_set FLAG_SNOW_AUTUMN_TUTORIAL_DONE, SnowRoute1_EventScript_AutumnTriggerDone
	applymovement 1, SnowRoute1_Movement_AutumnApproachPlayer
	waitmovement 0
	playse SE_PIN
	applymovement 1, SnowRoute1_Movement_AutumnExclaim
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnTutorialBody

SnowRoute1_EventScript_AutumnTriggerDone::
	releaseall
	end

SnowRoute1_EventScript_AutumnTutorial::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F2_AUTUMN, SnowRoute1_EventScript_AutumnDefeated
	goto_if_set FLAG_SNOW_AUTUMN_TUTORIAL_DONE, SnowRoute1_EventScript_AutumnBattleIntro
	goto SnowRoute1_EventScript_AutumnTutorialBody

SnowRoute1_EventScript_AutumnTutorialBody::
	msgbox SnowRoute1_Text_AutumnIntro, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnScienceTangent, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnCatchingExplanation, MSGBOX_DEFAULT
	closemessage
	applymovement 1, SnowRoute1_Movement_AutumnToGrass
	waitmovement 0
	applymovement 1, SnowRoute1_Movement_AutumnFaceGrass
	waitmovement 0
	msgbox SnowRoute1_Text_AutumnDemoSetup, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_THROW
	delay 20
	playse SE_BALL_BOUNCE_1
	delay 30
	playse SE_BALL_BOUNCE_3
	delay 40
	playse SE_PIN
	msgbox SnowRoute1_Text_AutumnDemoCatch, MSGBOX_DEFAULT
	closemessage
	applymovement 1, SnowRoute1_Movement_AutumnReturn
	waitmovement 0
	applymovement 1, SnowRoute1_Movement_AutumnFacePlayer
	waitmovement 0
	msgbox SnowRoute1_Text_AutumnGiveBalls, MSGBOX_DEFAULT
	giveitem ITEM_POKE_BALL, 5
	compare VAR_RESULT, FALSE
	goto_if_eq SnowRoute1_EventScript_AutumnBagFull
	setflag FLAG_SNOW_AUTUMN_TUTORIAL_DONE
	setflag FLAG_SNOW_GOT_POKEBALLS
	goto SnowRoute1_EventScript_AutumnBattleIntro

SnowRoute1_EventScript_AutumnBagFull::
	msgbox SnowRoute1_Text_AutumnBagFull, MSGBOX_DEFAULT
	releaseall
	end

SnowRoute1_EventScript_AutumnBattleIntro::
	msgbox SnowRoute1_Text_AutumnChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute1_EventScript_AutumnVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute1_EventScript_AutumnVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute1_EventScript_AutumnVariantC
	end

SnowRoute1_EventScript_AutumnVariantA::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_A, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle

SnowRoute1_EventScript_AutumnVariantB::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_B, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle

SnowRoute1_EventScript_AutumnVariantC::
	trainerbattle_no_intro TRAINER_SNOW_F2_AUTUMN_C, SnowRoute1_Text_AutumnDefeat
	goto SnowRoute1_EventScript_AutumnAfterBattle

SnowRoute1_EventScript_AutumnAfterBattle::
	setflag FLAG_SNOW_BEAT_F2_AUTUMN
	msgbox SnowRoute1_Text_AutumnPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 1, SnowRoute1_Movement_AutumnDepart
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_R1
	removeobject 1
	releaseall
	end

SnowRoute1_EventScript_AutumnDefeated::
	msgbox SnowRoute1_Text_AutumnPostTutorial, MSGBOX_DEFAULT
	release
	end

@ Autumn movements ------------------------------------------
@ Start: (9,5) facing up. Grass demo tile: (4,5).

SnowRoute1_Movement_AutumnApproachPlayer:
	walk_up
	step_end

SnowRoute1_Movement_AutumnExclaim:
	emote_exclamation_mark
	step_end

SnowRoute1_Movement_AutumnToGrass:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SnowRoute1_Movement_AutumnFaceGrass:
	face_left
	step_end

SnowRoute1_Movement_AutumnReturn:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_AutumnFacePlayer:
	face_up
	step_end

SnowRoute1_Movement_AutumnDepart:
	walk_up
	walk_up
	walk_up
	step_end

@ Autumn text ------------------------------------------------

SnowRoute1_Text_AutumnIntro:
	.string "AUTUMN: {PLAYER}!\p"
	.string "Oh wow, you're already out here?\n"
	.string "I tried to catch up before you\l"
	.string "left Dawnflake, but you move\l"
	.string "fast!\p"
	.string "I saw ASHER trudging home a\n"
	.string "minute ago. He was... sulking.\p"
	.string "You beat him, didn't you. He\n"
	.string "always sulks when he loses.$"

SnowRoute1_Text_AutumnScienceTangent:
	.string "AUTUMN: Okay, real talk - I've\n"
	.string "been DYING to show someone this.\p"
	.string "See that SENTRET over there in\n"
	.string "the grass? Watch its tail.\p"
	.string "It's not shivering. That's\n"
	.string "thermoregulation!\p"
	.string "Pokemon in BORALYSS have adapted\n"
	.string "to radiate heat through their\l"
	.string "extremities. The tail IS the\l"
	.string "heater.\p"
	.string "Isn't that incredible?\p"
	.string "...Sorry. Sorry. I know you\n"
	.string "didn't ask. I get excited.$"

SnowRoute1_Text_AutumnCatchingExplanation:
	.string "AUTUMN: Anyway - have you caught\n"
	.string "a wild POKEMON yet?\p"
	.string "No? Oh, you have to see this.\n"
	.string "Watch me - I'll show you how.$"

SnowRoute1_Text_AutumnDemoSetup:
	.string "AUTUMN: First, you weaken it.\n"
	.string "Never chuck balls at a healthy\l"
	.string "POKEMON - that's just rude.\p"
	.string "Okay, here goes...$"

SnowRoute1_Text_AutumnDemoCatch:
	.string "GOTCHA! AUTUMN caught a wild\n"
	.string "SENTRET!\p"
	.string "AUTUMN: YES! First try!\p"
	.string "Look at that face. Look at it.\n"
	.string "This one's coming home with me\l"
	.string "for further study. Absolutely\l"
	.string "adorable.$"

SnowRoute1_Text_AutumnGiveBalls:
	.string "AUTUMN: See how it works?\p"
	.string "Weaken them first. Status helps\n"
	.string "too - sleep and paralysis are\l"
	.string "huge.\p"
	.string "Here - take some of my spare\n"
	.string "POKE BALLS. I bought way too\l"
	.string "many. Field budget, don't ask.$"

SnowRoute1_Text_AutumnBagFull:
	.string "AUTUMN: Wait, your BAG is full?\n"
	.string "Come back for these when you've\l"
	.string "got room. I'll hold them.$"

SnowRoute1_Text_AutumnChallenge:
	.string "AUTUMN: Oh! Since we're both out\n"
	.string "here, let's battle!\p"
	.string "I want to see how your starter\n"
	.string "is adapting. It's for... research.\p"
	.string "(Also it's fun. Don't tell my\n"
	.string "field notes I said that.)$"

SnowRoute1_Text_AutumnDefeat:
	.string "AUTUMN: Wow! Okay, no pity\n"
	.string "there!$"

SnowRoute1_Text_AutumnPostBattle:
	.string "AUTUMN: That was a GREAT battle!\p"
	.string "Your starter's already showing\n"
	.string "good instincts. Did you see how\l"
	.string "it handled the cold?\p"
	.string "I'm going to keep cataloguing\n"
	.string "wild populations up here.\p"
	.string "You go on ahead - POWDERPATH\n"
	.string "VILLAGE is just south.\p"
	.string "Good luck, {PLAYER}! Don't be\n"
	.string "a stranger!$"

SnowRoute1_Text_AutumnPostTutorial:
	.string "AUTUMN: I'm cataloguing the\n"
	.string "SENTRET population out here.\p"
	.string "Did you know they form family\n"
	.string "groups? It is SO cute.\p"
	.string "Go on, get after it! I'll catch\n"
	.string "up with you down the road.$"

@ ═══════════════════════════════════════════════════════════
@ Route trainers — Noel, Elise, Kai
@ Three distinct voices: cocky local / shy traveler / gruff guardian
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
	.string "Hey! Flatlander!\p"
	.string "I was born in powder like this.\n"
	.string "Bet you've never even seen a\l"
	.string "real snowbank before today!$"

SnowRoute1_Text_NoelDefeat:
	.string "...Okay. Okay, that was fair.$"

SnowRoute1_Text_NoelPostBattle:
	.string "My mom says outsiders get slow\n"
	.string "in the cold.\p"
	.string "I guess that's not a rule.\n"
	.string "It's more like... a suggestion.$"

SnowRoute1_Text_EliseIntro:
	.string "Oh - hi! Sorry, I'm new at this.\p"
	.string "My parents said the trail would\n"
	.string "be a good place to find my\l"
	.string "first battle.\p"
	.string "Um... would you mind? Just one?\n"
	.string "I promise I'll try my best!$"

SnowRoute1_Text_EliseDefeat:
	.string "Oh - oh wow. Okay. That was\n"
	.string "a LOT to learn at once.$"

SnowRoute1_Text_ElisePostBattle:
	.string "Thank you for going easy on me.\p"
	.string "...You WERE going easy, right?\n"
	.string "Oh no.\p"
	.string "Good luck out there. Be safe!$"

SnowRoute1_Text_KaiIntro:
	.string "Hold it right there.\p"
	.string "Rule of the trail: no traveler\n"
	.string "passes without proving their\l"
	.string "grit.\p"
	.string "Don't look at me like that -\n"
	.string "I didn't make the rule. I just\l"
	.string "enforce it.$"

SnowRoute1_Text_KaiDefeat:
	.string "Hah! Proper grit. Pass through.$"

SnowRoute1_Text_KaiPostBattle:
	.string "POWDERPATH is just down the\n"
	.string "trail. Buy yourself some VANILLITE\l"
	.string "ice cream when you get there -\l"
	.string "the vendor makes it the old way.\p"
	.string "Tell her KAI sent you. She'll\n"
	.string "roll her eyes. That's how I\l"
	.string "know she remembers me.$"

@ ═══════════════════════════════════════════════════════════
@ Trail regular — non-battle flavor NPC
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_TrailRegular::
	lock
	faceplayer
	msgbox SnowRoute1_Text_TrailRegular, MSGBOX_DEFAULT
	release
	end

SnowRoute1_Text_TrailRegular:
	.string "Walked this trail for thirty\n"
	.string "winters, kid.\p"
	.string "Every year the SENTRET come\n"
	.string "back a little bolder. I think\l"
	.string "they're getting used to us.\p"
	.string "Mind the tall grass. And mind\n"
	.string "your footing on the ice.$"

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_TrailheadSign::
	msgbox SnowRoute1_Text_TrailheadSign, MSGBOX_SIGN
	end

SnowRoute1_Text_TrailheadSign:
	.string "POWDERPATH TRAIL\p"
	.string "North: DAWNFLAKE TOWN\n"
	.string "South: POWDERPATH VILLAGE\p"
	.string "Travelers, stay on the path.$"

SnowRoute1_EventScript_GrassSign::
	msgbox SnowRoute1_Text_GrassSign, MSGBOX_SIGN
	end

SnowRoute1_Text_GrassSign:
	.string "TRAIL NOTICE\p"
	.string "Wild POKEMON live in the tall\n"
	.string "grass. Keep a POKEMON of your\l"
	.string "own ready before you step in.$"

@ ═══════════════════════════════════════════════════════════
@ Potion item ball
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_PotionBall::
	finditem ITEM_POTION
	setflag FLAG_SNOW_GOT_POTION_R1
	end
