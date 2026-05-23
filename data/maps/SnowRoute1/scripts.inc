SnowRoute1_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn F2 — Catching tutorial + first rival battle
@ Intercept trigger + direct-talk fallback
@ Warm, nerdy, research-passionate voice
@ ═══════════════════════════════════════════════════════════

@ ═══════════════════════════════════════════════════════════
@ Autumn y=3 trigger — forced cutscene.
@
@ Pass silently if the F2 battle has already been won. Otherwise,
@ force-walk the player to (9,3) so the scene stages face-to-face
@ with Autumn at (9,4) after her walk-up. Player x is read via
@ StorePlayerCoordsInVars into VAR_0x8004, then dispatched to the
@ matching walk_right/walk_left movement length. x=9 skips the
@ force-walk entirely.
@
@ After force-walk, flow branches on FLAG_SNOW_AUTUMN_TUTORIAL_DONE:
@   unset: first encounter — play full catching tutorial
@   set  : rematch — short dialogue then straight to battle
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_AutumnTrigger::
	@ One-shot guard: setvar keeps trigger from re-firing on every
	@ step across the row within this map session (fixes running lag).
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_SNOW_BEAT_F2_AUTUMN, SnowRoute1_EventScript_AutumnTriggerDone
	lockall
	special StorePlayerCoordsInVars
	compare VAR_0x8004, 2
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight7
	compare VAR_0x8004, 3
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight6
	compare VAR_0x8004, 4
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight5
	compare VAR_0x8004, 5
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight4
	compare VAR_0x8004, 6
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight3
	compare VAR_0x8004, 7
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight2
	compare VAR_0x8004, 8
	goto_if_eq SnowRoute1_EventScript_AutumnWalkRight1
	compare VAR_0x8004, 10
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft1
	compare VAR_0x8004, 11
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft2
	compare VAR_0x8004, 12
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft3
	compare VAR_0x8004, 13
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft4
	compare VAR_0x8004, 14
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft5
	compare VAR_0x8004, 15
	goto_if_eq SnowRoute1_EventScript_AutumnWalkLeft6
	@ Player at x=9 (or fallback): no force-walk needed.
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight7::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight7
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight6::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight6
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight5::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight5
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight4::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight4
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight3::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight3
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight2::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight2
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkRight1::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkRight1
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft1::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft1
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft2::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft2
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft3::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft3
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft4::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft4
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft5::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft5
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnWalkLeft6::
	applymovement LOCALID_PLAYER, SnowRoute1_Movement_WalkLeft6
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnEncounter

SnowRoute1_EventScript_AutumnEncounter::
	@ Player is now at (9,3) — re-orient to face south.
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement 1, SnowRoute1_Movement_AutumnApproachPlayer
	waitmovement 0
	goto_if_set FLAG_SNOW_AUTUMN_TUTORIAL_DONE, SnowRoute1_EventScript_AutumnRematch
	playse SE_PIN
	applymovement 1, SnowRoute1_Movement_AutumnExclaim
	waitmovement 0
	goto SnowRoute1_EventScript_AutumnTutorialBody

SnowRoute1_EventScript_AutumnRematch::
	msgbox SnowRoute1_Text_AutumnRematch, MSGBOX_DEFAULT
	goto SnowRoute1_EventScript_AutumnBattleIntro

SnowRoute1_EventScript_AutumnTriggerDone::
	releaseall
	end

SnowRoute1_EventScript_AutumnTutorial::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F2_AUTUMN, SnowRoute1_EventScript_AutumnDefeated
	@ Defensive fallback — the coord trigger is the real entry;
	@ if somehow interacted before the trigger, treat as rematch.
	goto SnowRoute1_EventScript_AutumnRematch

SnowRoute1_EventScript_AutumnTutorialBody::
	msgbox SnowRoute1_Text_AutumnIntro, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnScienceTangent, MSGBOX_DEFAULT
	msgbox SnowRoute1_Text_AutumnCatchingExplanation, MSGBOX_DEFAULT
	closemessage
	applymovement 1, SnowRoute1_Movement_AutumnToGrass
	waitmovement 0
	applymovement 1, SnowRoute1_Movement_AutumnFaceGrass
	waitmovement 0
	@ Sentret cry plays the moment Autumn faces the grass — "spotted one."
	@ Use NORMAL cry mode (fuller envelope than ENCOUNTER) and a small
	@ delay so the cry isn't stomped by the textbox-open SE_SELECT.
	playmoncry SPECIES_SENTRET, CRY_MODE_NORMAL
	delay 36
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
	@ Advice msgbox fires only on a successful give — bag-full path skips it
	@ and re-enters the tutorial later with empty inventory.
	msgbox SnowRoute1_Text_AutumnAdvice, MSGBOX_DEFAULT
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
@ Start: (9,5) facing up. Grass demo tile: (3,5).

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
	walk_right
	step_end

SnowRoute1_Movement_AutumnFacePlayer:
	face_up
	step_end

@ Autumn departs south off-screen into R1 after the F2 battle.
@ 7 tiles south from (9,4) -> (9,11). Column x=9 is clear of
@ Noel (7,17), Elise (10,9 — Autumn passes at x=9 beside her),
@ and Kai (18,6).
SnowRoute1_Movement_AutumnDepart:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Force-walk movements — player at (?,3) -> (9,3) along y=3.
SnowRoute1_Movement_WalkRight1:
	walk_right
	step_end

SnowRoute1_Movement_WalkRight2:
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkRight3:
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkRight4:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkRight5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkRight6:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkRight7:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SnowRoute1_Movement_WalkLeft1:
	walk_left
	step_end

SnowRoute1_Movement_WalkLeft2:
	walk_left
	walk_left
	step_end

SnowRoute1_Movement_WalkLeft3:
	walk_left
	walk_left
	walk_left
	step_end

SnowRoute1_Movement_WalkLeft4:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SnowRoute1_Movement_WalkLeft5:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SnowRoute1_Movement_WalkLeft6:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Autumn text ------------------------------------------------

SnowRoute1_Text_AutumnIntro:
	.string "AUTUMN: Oh, hey {PLAYER}!\n"
	.string "You finally caught up, I see.\p"
	.string "Well anyway, I just saw ASHER\n"
	.string "walking southbound a few\l"
	.string "minutes ago.\p"
	.string "So we better get started with\n"
	.string "what I wanted to show you, if\l"
	.string "we want to keep up.$"

SnowRoute1_Text_AutumnScienceTangent:
	.string "AUTUMN: See those dark patches\n"
	.string "of grass?\p"
	.string "That's where the wild POKEMON\n"
	.string "hide.\p"
	.string "Every ROUTE has its own little\n"
	.string "ecosystem - SO cool, I know!\p"
	.string "ROUTE 1 is loaded with them.\n"
	.string "Watch this.$"

SnowRoute1_Text_AutumnCatchingExplanation:
	.string "AUTUMN: Now then - let me\n"
	.string "demonstrate how to catch a\l"
	.string "POKEMON in the wild!$"

SnowRoute1_Text_AutumnDemoSetup:
	.string "AUTUMN: Omg, {PLAYER}, I found\n"
	.string "a SENTRET!\p"
	.string "He looks sooo cute - he's\n"
	.string "definitely coming home with\l"
	.string "me.\p"
	.string "Alright, {PLAYER}, here's how\n"
	.string "this works.\p"
	.string "Usually, you battle a POKEMON\n"
	.string "first and weaken it before\l"
	.string "throwing any POKE BALLS.\p"
	.string "But this case is different -\n"
	.string "this SENTRET is weak enough\l"
	.string "that a single throw should\l"
	.string "do it.$"

SnowRoute1_Text_AutumnDemoCatch:
	.string "GOTCHA! AUTUMN caught a wild\n"
	.string "SENTRET!\p"
	.string "AUTUMN: YES!!\n"
	.string "See, {PLAYER}? Told you that\l"
	.string "would work.\p"
	.string "This guy is a certified cutie\n"
	.string "for sure!$"

SnowRoute1_Text_AutumnGiveBalls:
	.string "AUTUMN: See how easy that was?\p"
	.string "Here - take some POKE BALLS\n"
	.string "and try it out for yourself.$"

SnowRoute1_Text_AutumnAdvice:
	.string "AUTUMN: Just remember -\n"
	.string "weaken the stronger POKEMON\l"
	.string "first before throwing.\p"
	.string "For the lower-level ones, you\n"
	.string "can usually skip that step and\l"
	.string "throw a POKE BALL straight off.$"

SnowRoute1_Text_AutumnBagFull:
	.string "AUTUMN: Oh no, your BAG is\n"
	.string "full!\p"
	.string "I'll hold onto these until\n"
	.string "you've got some room.$"

SnowRoute1_Text_AutumnChallenge:
	.string "AUTUMN: Well, now that we're\n"
	.string "done with that - I was thinking\l"
	.string "we could battle!\p"
	.string "It'd give both of us some\n"
	.string "much-needed practice.\p"
	.string "And I can't lie - this place\n"
	.string "is pretty cinematic for a\l"
	.string "battle, right?\p"
	.string "Anyway - get ready, {PLAYER}!$"

SnowRoute1_Text_AutumnDefeat:
	.string "AUTUMN: Ha, well that was\n"
	.string "embarrassing.$"

SnowRoute1_Text_AutumnPostBattle:
	.string "AUTUMN: Wow, {PLAYER}, you're\n"
	.string "really good at this!\p"
	.string "Your starter is already super\n"
	.string "strong, and you two fought\l"
	.string "like a perfect team.\p"
	.string "No wonder you won!\p"
	.string "Anyway, don't you worry -\n"
	.string "I'll get stronger, and when I\l"
	.string "do, a rematch is definitely\l"
	.string "in order.\p"
	.string "Alrighty, I'm gonna run ahead\n"
	.string "to POWDERPATH VILLAGE to see\l"
	.string "if I can find some rare\l"
	.string "POKEMON.\p"
	.string "See ya, {PLAYER}!$"

SnowRoute1_Text_AutumnRematch:
	.string "AUTUMN: Oh, already back for\n"
	.string "more, {PLAYER}?\p"
	.string "I'm ready for another battle\n"
	.string "if you are!$"

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
	.string "Hey there trainer!\n"
	.string "That POTION is mine!$"

SnowRoute1_Text_NoelDefeat:
	.string "Well then.\n"
	.string "I guess you can have it.$"

SnowRoute1_Text_NoelPostBattle:
	.string "Sorry about that, I get a\n"
	.string "little protective when\l"
	.string "calling dibs.$"

SnowRoute1_Text_EliseIntro:
	.string "Oh, hi there!\p"
	.string "When two trainers' eyes meet\n"
	.string "that means a battle,\l"
	.string "so get ready!$"

SnowRoute1_Text_EliseDefeat:
	.string "Woah you're pretty good\n"
	.string "at this huh?$"

SnowRoute1_Text_ElisePostBattle:
	.string "You're pretty strong kid,\n"
	.string "keep that up and you'll\l"
	.string "beat SILVAN in no time!$"

SnowRoute1_Text_KaiIntro:
	.string "Oh, hey there trainer!\p"
	.string "POWDERPATH VILLAGE is just south\n"
	.string "of here, but you gotta battle me\l"
	.string "first before I let you pass.$"

SnowRoute1_Text_KaiDefeat:
	.string "Alright you can pass\n"
	.string "through now.$"

SnowRoute1_Text_KaiPostBattle:
	.string "I heard POWDERPATH VILLAGE has\n"
	.string "the best ice cream in BORALYSS!\p"
	.string "Make sure to try some\n"
	.string "for me.$"

@ ═══════════════════════════════════════════════════════════
@ Potion item ball
@ ═══════════════════════════════════════════════════════════

SnowRoute1_EventScript_PotionBall::
	finditem ITEM_POTION
	setflag FLAG_SNOW_GOT_POTION_R1
	end
