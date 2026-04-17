SnowRoute15_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ F18 AUTUMN — FINAL rival fight, mid-route fork (v17 §20, §21)
@ Her retirement from battle. She walks north to the Research
@ Outpost after defeat. Sets FLAG_SNOW_BEAT_F18_AUTUMN for the
@ zone 8a→8b mid-zone cap advance (cap 72 → 73) — only mid-zone
@ sub-cap advancement in the file.
@
@ Starter-keyed A/B/C: player Treecko = A (Swampert ace),
@ Torchic = B (Sceptile ace), Mudkip = C (Blaziken ace).
@ LOCALID 3 (third object_event in map.json).
@ ═══════════════════════════════════════════════════════════════

SnowRoute15_EventScript_AutumnF18::
	lock
	faceplayer
	msgbox SnowRoute15_Text_AutumnF18Intro, MSGBOX_DEFAULT
	closemessage
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute15_EventScript_AutumnF18VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute15_EventScript_AutumnF18VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute15_EventScript_AutumnF18VariantC
	release
	end

SnowRoute15_EventScript_AutumnF18VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F18_AUTUMN_A, SnowRoute15_Text_AutumnF18Defeat
	goto SnowRoute15_EventScript_AutumnF18AfterBattle

SnowRoute15_EventScript_AutumnF18VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F18_AUTUMN_B, SnowRoute15_Text_AutumnF18Defeat
	goto SnowRoute15_EventScript_AutumnF18AfterBattle

SnowRoute15_EventScript_AutumnF18VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F18_AUTUMN_C, SnowRoute15_Text_AutumnF18Defeat
	goto SnowRoute15_EventScript_AutumnF18AfterBattle

SnowRoute15_EventScript_AutumnF18AfterBattle::
	setflag FLAG_SNOW_BEAT_F18_AUTUMN
	msgbox SnowRoute15_Text_AutumnF18PostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 3, SnowRoute15_Movement_AutumnF18Depart
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_R15
	removeobject 3
	release
	end

SnowRoute15_Movement_AutumnF18Depart:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SnowRoute15_Text_AutumnF18Intro:
	.string "AUTUMN: There you are.\p"
	.string "I was worried I'd miss you\n"
	.string "before the lagoon crest.\p"
	.string "{PLAYER}, listen.\n"
	.string "This is my last one.\p"
	.string "I've been thinking about it\n"
	.string "since GALETOP. EVERGREEN needs\l"
	.string "a research partner.\p"
	.string "I'm better with notes than\n"
	.string "with a full team.\p"
	.string "But before I step back, I\n"
	.string "want you to remember what a\l"
	.string "fair fight feels like.\p"
	.string "One more, {PLAYER}.\n"
	.string "Then I'm off your road.$"

SnowRoute15_Text_AutumnF18Defeat:
	.string "AUTUMN: ...Yes.\p"
	.string "That was the right answer.$"

SnowRoute15_Text_AutumnF18PostBattle:
	.string "AUTUMN: You're ready for what\n"
	.string "PYRESPIRE has waiting.\p"
	.string "I'm not, {PLAYER}.\n"
	.string "TYRELL scares me. FACILITY\l"
	.string "BETA scares me.\p"
	.string "What you're about to do?\n"
	.string "I couldn't.\p"
	.string "I'll be at EVERGREEN's\n"
	.string "Research Outpost north.\p"
	.string "If you come back through,\n"
	.string "find me. I'll have something\l"
	.string "for you.\p"
	.string "Go. SCORCH is waiting. The\n"
	.string "region is waiting.\p"
	.string "I trust you.$"

SnowRoute15_EventScript_Briney::
	trainerbattle_single TRAINER_SNOW_R15_1_BRINEY, SnowRoute15_Text_BrineyIntro, SnowRoute15_Text_BrineyDefeat
	msgbox SnowRoute15_Text_BrineyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Ahab::
	trainerbattle_single TRAINER_SNOW_R15_2_AHAB, SnowRoute15_Text_AhabIntro, SnowRoute15_Text_AhabDefeat
	msgbox SnowRoute15_Text_AhabPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Cousteau::
	trainerbattle_single TRAINER_SNOW_R15_3_COUSTEAU, SnowRoute15_Text_CousteauIntro, SnowRoute15_Text_CousteauDefeat
	msgbox SnowRoute15_Text_CousteauPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Hadley::
	trainerbattle_single TRAINER_SNOW_R15_4_HADLEY, SnowRoute15_Text_HadleyIntro, SnowRoute15_Text_HadleyDefeat
	msgbox SnowRoute15_Text_HadleyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Volt::
	trainerbattle_single TRAINER_SNOW_R15_5_VOLT, SnowRoute15_Text_VoltIntro, SnowRoute15_Text_VoltDefeat
	msgbox SnowRoute15_Text_VoltPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Quint::
	trainerbattle_single TRAINER_SNOW_R15_6_QUINT, SnowRoute15_Text_QuintIntro, SnowRoute15_Text_QuintDefeat
	msgbox SnowRoute15_Text_QuintPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Nori::
	trainerbattle_single TRAINER_SNOW_R15_7_NORI, SnowRoute15_Text_NoriIntro, SnowRoute15_Text_NoriDefeat
	msgbox SnowRoute15_Text_NoriPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Triton::
	trainerbattle_single TRAINER_SNOW_R15_8_TRITON, SnowRoute15_Text_TritonIntro, SnowRoute15_Text_TritonDefeat
	msgbox SnowRoute15_Text_TritonPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute15_EventScript_Nemo::
	trainerbattle_single TRAINER_SNOW_R15_9_NEMO, SnowRoute15_Text_NemoIntro, SnowRoute15_Text_NemoDefeat
	msgbox SnowRoute15_Text_NemoPostBattle, MSGBOX_AUTOCLOSE
	end

@ R15 Pyrespire Lagoon - volcanic tropical, Autumn F18 mid-route fork.
@ 2 pre-fork, F18 Autumn junction, 7 post-fork (3 Surf-gated Swimmers).

@ R15-1 Briney (Sailor) - Pre-Fork "Tide Watcher". Sudowoodo/Relicanth/Poliwrath.

SnowRoute15_Text_BrineyIntro:
	.string "BRINEY. Tide Watcher.\p"
	.string "RELICANTH's ROCK HEAD negates\n"
	.string "HEAD SMASH recoil entirely.$"

SnowRoute15_Text_BrineyDefeat:
	.string "POLIWRATH's BULK UP needed\n"
	.string "one more turn.$"

SnowRoute15_Text_BrineyPostBattle:
	.string "AUTUMN waits at the fork\n"
	.string "north.\p"
	.string "I can't prepare you for her.$"

@ R15-2 Ahab (Fisherman) - Pre-Fork "Old Salt". Politoed rain + Tentacruel.

SnowRoute15_Text_AhabIntro:
	.string "AHAB.\p"
	.string "Two mons. POLITOED rains.\n"
	.string "TENTACRUEL poisons your drain\l"
	.string "moves.\p"
	.string "Last test before the fork.$"

SnowRoute15_Text_AhabDefeat:
	.string "LIQUID OOZE's punishment\n"
	.string "didn't land enough times.$"

SnowRoute15_Text_AhabPostBattle:
	.string "After AUTUMN, the lagoon gets\n"
	.string "deeper.\p"
	.string "Bring SURF if you have it.$"

@ R15-3 Cousteau (Pokemon Tycoon) - "The Curator". 4 fossil-mid-evo specimens.

SnowRoute15_Text_CousteauIntro:
	.string "COUSTEAU.\p"
	.string "Marine curator. Four fossil\n"
	.string "pre-evos on EVIOLITE.\p"
	.string "They hit like finals.$"

SnowRoute15_Text_CousteauDefeat:
	.string "PUPITAR's DRAGON DANCE landed\n"
	.string "one turn late.$"

SnowRoute15_Text_CousteauPostBattle:
	.string "METANG's IRON FIST METEOR MASH\n"
	.string "with Steel Gem = 243 BP.\p"
	.string "You took one hit. Barely.$"

@ R15-4 Hadley (Fisherman) - "Shore Veteran". Bulky Water trio.

SnowRoute15_Text_HadleyIntro:
	.string "HADLEY.\p"
	.string "Three Water-immune mons.\n"
	.string "QUAGSIRE. SEALEO. JELLICENT.\p"
	.string "Your Water moves heal us.$"

SnowRoute15_Text_HadleyDefeat:
	.string "JELLICENT's RECOVER couldn't\n"
	.string "catch up.$"

SnowRoute15_Text_HadleyPostBattle:
	.string "SEALEO on EVIOLITE has the\n"
	.string "same effective bulk as a fully\l"
	.string "evolved tank.\p"
	.string "Mid-evo deception.$"

@ R15-5 Volt (Sailor) - "Lagoon Stormcaller". Sigilyph/Stunfisk/Ampharos.

SnowRoute15_Text_VoltIntro:
	.string "VOLT. Stormcaller.\p"
	.string "The lagoon conducts electricity.\n"
	.string "AMPHAROS closes with COTTON\l"
	.string "GUARD plus three Defense.$"

SnowRoute15_Text_VoltDefeat:
	.string "THUNDERBOLT didn't catch.$"

SnowRoute15_Text_VoltPostBattle:
	.string "SIGILYPH's MAGIC GUARD ignored\n"
	.string "every hazard I put down.\p"
	.string "She was my most reliable mon.$"

@ R15-6 Quint (Fisherman) - MANDATORY GATE. 5 mons "Master of the Lagoon".

SnowRoute15_Text_QuintIntro:
	.string "QUINT.\p"
	.string "Master of the lagoon. Five\n"
	.string "mons. No passing without me.\p"
	.string "PYRESPIRE is one fight away.$"

SnowRoute15_Text_QuintDefeat:
	.string "Pass. You earned it.$"

SnowRoute15_Text_QuintPostBattle:
	.string "PYRESPIRE CITY is south.\p"
	.string "FACILITY BETA is waiting.\n"
	.string "SCORCH is waiting.$"

@ R15-7 Nori (Swimmer) - SURF-GATED. "Lagoon Shallows".

SnowRoute15_Text_NoriIntro:
	.string "NORI.\p"
	.string "You brought SURF. Good.\n"
	.string "Lagoon water's warm here.$"

SnowRoute15_Text_NoriDefeat:
	.string "You swim faster than you look.$"

SnowRoute15_Text_NoriPostBattle:
	.string "Deeper water means TRITON.\n"
	.string "He's harder than I am.$"

@ R15-8 Triton (Swimmer) - SURF-GATED. "Lagoon Mid-Depth".

SnowRoute15_Text_TritonIntro:
	.string "TRITON.\p"
	.string "Mid-depth. The sun stops\n"
	.string "reaching down here.$"

SnowRoute15_Text_TritonDefeat:
	.string "You read the current.$"

SnowRoute15_Text_TritonPostBattle:
	.string "NEMO's at the bottom. If you\n"
	.string "beat him you've beaten every\l"
	.string "Swimmer in BORALYSS.$"

@ R15-9 Nemo (Swimmer) - SURF-GATED. "Deep Lagoon Master". R15 HARDEST OPTIONAL.

SnowRoute15_Text_NemoIntro:
	.string "NEMO.\p"
	.string "Deep lagoon master.\n"
	.string "R15 hardest. Optional.\p"
	.string "You chose to come down here.$"

SnowRoute15_Text_NemoDefeat:
	.string "No one beats the deep.\n"
	.string "You did.$"

SnowRoute15_Text_NemoPostBattle:
	.string "Every Swimmer in BORALYSS.\p"
	.string "You can go back to the surface\n"
	.string "now. PYRESPIRE's waiting.$"
