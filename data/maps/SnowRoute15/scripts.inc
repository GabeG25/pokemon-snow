SnowRoute15_MapScripts::
	.byte 0

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
