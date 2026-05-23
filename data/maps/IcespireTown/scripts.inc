IcespireTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcespireTown_OnTransition
	.byte 0

@ On every entry to IcespireTown, ensure Asher F4 is hidden until the
@ first-encounter cutscene has run. Covers both new saves (where the
@ HIDE flag is unset by default) and pre-existing saves where Asher
@ was placed visibly at (15,38) by the prior interact-only design.
IcespireTown_OnTransition::
	goto_if_set FLAG_SNOW_F4_ASHER_INTRO_DONE, IcespireTown_OnTransition_End
	setflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
IcespireTown_OnTransition_End::
	end

@ ═══════════════════════════════════════════════════════════
@ Joltik Route Guards — south-edge forest entrance, pre Gym 1.
@
@ Two Hiker NPCs stand at (15,38) and (16,38), physically blocking
@ the 2-tile gap that leads south into Route 3. Both share one
@ script and one hide flag — FLAG_BADGE01_GET. As soon as the
@ player clears Silvan and the flag goes set, the engine hides
@ them on the next map load and the Asher F4 coord triggers can
@ fire unobstructed.
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_JoltikGuard::
	lock
	faceplayer
	msgbox IcespireTown_Text_JoltikGuard, MSGBOX_DEFAULT
	release
	end

IcespireTown_Text_JoltikGuard:
	.string "WORKER: Sorry, the route's\n"
	.string "closed for now.\p"
	.string "There's a JOLTIK swarm down\n"
	.string "in the forest right now - too\l"
	.string "dangerous to walk through.\p"
	.string "A specialist is on the way to\n"
	.string "handle them. You'll have to\l"
	.string "hang tight until they come\l"
	.string "back out.$"

@ ═══════════════════════════════════════════════════════════
@ Asher F4 — Forest-entrance ambush, post Gym 1.
@
@ Trigger fires on coord (15,37) or (16,37) — the 2-tile gap
@ directly north of the R3 forest entrance. Asher walks out
@ of the forest, battles the player, and either walks off
@ (on player win) or remains in place for a rematch on loss.
@
@ Gating:
@   FLAG_BADGE01_GET unset       → silent pass, no cutscene
@   FLAG_SNOW_BEAT_F4_ASHER set  → silent pass, no cutscene
@   else, FLAG_SNOW_HIDE_ICESPIRE_ASHER set  → first encounter
@   else                                      → rematch
@
@ Asher's object_event entry in map.json (LOCALID 1) starts
@ hidden via FLAG_SNOW_HIDE_ICESPIRE_ASHER. The first-encounter
@ branch clears that flag and walks him into position (15,38).
@ On loss the flag stays cleared so Asher persists across the
@ whiteout cycle; on win the flag is re-set and Asher is
@ removed from the map for good.
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_AsherF4Trigger::
	goto_if_unset FLAG_BADGE01_GET, IcespireTown_EventScript_AsherF4TriggerSilencePass
	goto_if_set FLAG_SNOW_BEAT_F4_ASHER, IcespireTown_EventScript_AsherF4TriggerSilencePass
	lockall
	goto_if_set FLAG_SNOW_HIDE_ICESPIRE_ASHER, IcespireTown_EventScript_AsherF4FirstEncounter
	goto IcespireTown_EventScript_AsherF4Rematch

@ Silent pass: silence the trigger for this map session and end.
@ VAR_TEMP_0 resets to 0 on map reload, so silencing only sticks
@ until the player leaves/re-enters.
IcespireTown_EventScript_AsherF4TriggerSilencePass::
	setvar VAR_TEMP_0, 1
	end

IcespireTown_EventScript_AsherF4FirstEncounter::
	@ Mark intro as having played so the OnTransition hook stops
	@ re-hiding Asher on subsequent map entries (e.g. after loss).
	setflag FLAG_SNOW_F4_ASHER_INTRO_DONE
	@ Spawn Asher at the forest mouth (15,39) and walk him north
	@ onto (15,38) — the tile directly south of the player.
	setobjectxyperm 1, 15, 39
	clearflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
	addobject 1
	applymovement 1, IcespireTown_Movement_AsherF4WalkInFromForest
	waitmovement 0
	setobjectxyperm 1, 15, 38
	applymovement 1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox IcespireTown_Text_AsherF4Intro, MSGBOX_DEFAULT
	closemessage
	goto IcespireTown_EventScript_AsherF4DispatchBattle

IcespireTown_EventScript_AsherF4Rematch::
	@ Asher already standing at (15,38) from a prior loss.
	applymovement 1, IcespireTown_Movement_AsherFaceUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox IcespireTown_Text_AsherF4Rematch, MSGBOX_DEFAULT
	closemessage
	goto IcespireTown_EventScript_AsherF4DispatchBattle

IcespireTown_EventScript_AsherF4DispatchBattle::
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

IcespireTown_EventScript_AsherF4VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_B, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle

IcespireTown_EventScript_AsherF4VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_C, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle

IcespireTown_EventScript_AsherF4AfterBattle::
	setflag FLAG_SNOW_BEAT_F4_ASHER
	msgbox IcespireTown_Text_AsherF4PostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 1, IcespireTown_Movement_AsherF4WalkOffToPC
	waitmovement 0
	setflag FLAG_SNOW_HIDE_ICESPIRE_ASHER
	removeobject 1
	setvar VAR_TEMP_0, 1
	releaseall
	end

@ Walk in from forest mouth: 1 step north (from (15,39) to (15,38)).
IcespireTown_Movement_AsherF4WalkInFromForest:
	walk_up
	step_end

@ After-win walk-off. Routes via (14,38) first so Asher steps clear
@ of the player's column at (15,37)/(16,37) before heading north —
@ avoids the NPC bouncing off the locked player sprite. Then walks
@ up 10 to (14,28), well above the visible window centered on the
@ player, then west 7 toward the Pokémon Center at (4,13).
@ removeobject is called after waitmovement so we don't need to
@ reach the PC exactly — just leave the visible area.
IcespireTown_Movement_AsherF4WalkOffToPC:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

IcespireTown_Movement_AsherFaceUp:
	walk_in_place_faster_up
	step_end

@ Interact handler — if the player presses A on Asher while he's
@ standing in position post-loss, route through the same rematch
@ flow. Player won't normally hit this since the coord trigger
@ fires first, but it covers the case of approaching from a
@ direction that doesn't cross y=37.
IcespireTown_EventScript_AsherF4::
	lockall
	goto_if_set FLAG_SNOW_BEAT_F4_ASHER, IcespireTown_EventScript_AsherF4InteractDone
	goto IcespireTown_EventScript_AsherF4Rematch

IcespireTown_EventScript_AsherF4InteractDone::
	releaseall
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
@ Roughneck Move Tutor — Mega Punch, 2500 yen, gated on Badge 1
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
	checkmoney 2500
	compare VAR_RESULT, FALSE
	goto_if_eq IcespireTown_EventScript_RoughneckNoMoney
	removemoney 2500
	setvar VAR_0x8005, MOVE_MEGA_PUNCH
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
@ Pro-Veil citizen — Beautiful Lie, moved to walkable tile
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_ProVeilCitizen::
	lock
	faceplayer
	msgbox IcespireTown_Text_CitizenPraise, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ School kid — innocent cult chant
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_SchoolKid::
	lock
	faceplayer
	msgbox IcespireTown_Text_SchoolKidChant, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Doubter elder — memory-loss hint, late-game breadcrumb
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_DoubterElder::
	lock
	faceplayer
	msgbox IcespireTown_Text_DoubterElder, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Fanatic preacher — full-cult Veil true believer
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_FanaticPreacher::
	lock
	faceplayer
	msgbox IcespireTown_Text_FanaticPreacher, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_GymSign::
	msgbox IcespireTown_Text_GymSign, MSGBOX_SIGN
	end

IcespireTown_EventScript_MartSign::
	msgbox IcespireTown_Text_MartSign, MSGBOX_SIGN
	end

IcespireTown_EventScript_PCSign::
	msgbox IcespireTown_Text_PCSign, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

IcespireTown_Text_AsherF4Intro:
	.string "ASHER: Oh, look who it is.\p"
	.string "Wasn't expecting to see you\n"
	.string "this far south yet, I thought\l"
	.string "you might be slower.\p"
	.string "Anyway, since we're here,\n"
	.string "why not battle?\p"
	.string "I need the practice anyway,\n"
	.string "and it looks like you do too.$"

IcespireTown_Text_AsherF4Rematch:
	.string "ASHER: Heh, back for more\n"
	.string "I see?\p"
	.string "Well lucky for you, I'm ready\n"
	.string "to humble you again.$"

IcespireTown_Text_AsherF4Defeat:
	.string "ASHER: No. No no no.$"

IcespireTown_Text_AsherF4PostBattle:
	.string "ASHER: Are you serious...\p"
	.string "What the hell, how did I\n"
	.string "lose that?\p"
	.string "Whatever, a broken clock is\n"
	.string "right once a day, or however\l"
	.string "the saying goes.\p"
	.string "Later, jackass.$"

IcespireTown_Text_AsherF4PostDefeat:
	.string "ASHER: Still here? Still winning?\p"
	.string "Whatever. I'm heading down to\n"
	.string "PINEGROVE. Try to keep up.$"

IcespireTown_Text_WideLensIntro:
	.string "WORN-OUT TRAINER: That gym nearly\n"
	.string "did me in.\p"
	.string "Silvan's team - the hail, the\n"
	.string "evasion, his PIPLUP's SPEED...\p"
	.string "My POKEMON just couldn't land\n"
	.string "a hit.\p"
	.string "Here. I picked this up on R2\n"
	.string "but I'm done battling for a\l"
	.string "while.\p"
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
	.string "I've watched trainers come and\n"
	.string "go through this gym for years.\p"
	.string "The ones who make it big all\n"
	.string "have the same thing in common -\l"
	.string "they don't JUST rely on type\l"
	.string "charts.\p"
	.string "They hit hard. They hit dirty.\n"
	.string "They SCRAP.\p"
	.string "I didn't learn to fight in any\n"
	.string "gym. You want me to teach your\l"
	.string "POKEMON how to actually brawl?$"

IcespireTown_Text_RoughneckOffer:
	.string "ROUGHNECK: I can teach MEGA PUNCH\n"
	.string "for 2500 yen.\p"
	.string "Pure brute force. No tricks, no\n"
	.string "type games. Just a fist that\l"
	.string "ends fights.\p"
	.string "Interested?$"

IcespireTown_Text_RoughneckDecline:
	.string "ROUGHNECK: Think about it.\n"
	.string "Door's always open.$"

IcespireTown_Text_RoughneckNoMoney:
	.string "ROUGHNECK: You're short. Come\n"
	.string "back when your wallet isn't.$"

IcespireTown_Text_RoughneckLocked:
	.string "ROUGHNECK: Kid, come back with a\n"
	.string "badge. I don't waste lessons on\l"
	.string "trainers who can't prove they\l"
	.string "can take a hit.$"

IcespireTown_Text_RoughneckTaught:
	.string "ROUGHNECK: MEGA PUNCH taught. Now\n"
	.string "go hit something with it.$"

IcespireTown_Text_CitizenPraise:
	.string "CITIZEN: Beautiful day, isn't it?\p"
	.string "I moved here from SLATEPORT years\n"
	.string "ago. Couldn't stand the heat.\p"
	.string "Then DIRECTOR TYRELL and his\n"
	.string "researchers changed everything.\p"
	.string "This winter - it's a miracle.\n"
	.string "The air is clean, the POKEMON\l"
	.string "are thriving, crime is down.\p"
	.string "I don't know how he did it, but\n"
	.string "I trust him completely.\p"
	.string "DIRECTOR TYRELL saved BORALYSS.$"

IcespireTown_Text_SchoolKidChant:
	.string "SCHOOL KID: The snow is kind!\n"
	.string "The snow is clean!\p"
	.string "The DIRECTOR loves us!\n"
	.string "The DIRECTOR keeps us!\p"
	.string "I know the whole song! We sing\n"
	.string "it at recess.\p"
	.string "My teacher says if we're really\n"
	.string "good, the DIRECTOR might come\l"
	.string "visit our class again!$"

IcespireTown_Text_DoubterElder:
	.string "OLD WOMAN: Mmh. Another trainer.\p"
	.string "You know, I was born in this\n"
	.string "town. Long before the winter.\p"
	.string "It used to rain here. Real\n"
	.string "rain, the warm kind. My mother\l"
	.string "kept a garden by the south wall.\p"
	.string "I can't remember what was in\n"
	.string "it. I try, and the shape just...\l"
	.string "goes away.\p"
	.string "Everyone says the cold is a\n"
	.string "gift. I believe them.\p"
	.string "I just wish I could remember\n"
	.string "the garden.$"

IcespireTown_Text_FanaticPreacher:
	.string "MAN IN WHITE: Trainer! You walk\n"
	.string "in blessed air!\p"
	.string "Do you feel it? The HUSH. The\n"
	.string "PURITY. The DIRECTOR reached\l"
	.string "into the sky and FIXED it.\p"
	.string "Those who complain of the cold\n"
	.string "are complaining of a GIFT.\p"
	.string "Some say TEAM VEIL are just\n"
	.string "men. I say they are HANDS.\l"
	.string "The DIRECTOR'S hands.\p"
	.string "When KYUREM smiles upon us,\n"
	.string "all of BORALYSS will be free\l"
	.string "of summer forever.\p"
	.string "Praise the VEIL.$"

IcespireTown_Text_GymSign:
	.string "ICESHARD GYM\p"
	.string "LEADER: SILVAN\n"
	.string "KEEPER OF THE COLD$"

IcespireTown_Text_MartSign:
	.string "ICESPIRE POKEMON MART\n"
	.string "Warm hands. Cold prices.$"

IcespireTown_Text_PCSign:
	.string "ICESPIRE POKEMON CENTER\n"
	.string "Heal your team. Rest your soul.$"
