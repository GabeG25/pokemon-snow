SnowVictoryRoad_MapScripts::
	.byte 0

SnowVictoryRoad_EventScript_Soleil::
	trainerbattle_single TRAINER_SNOW_VR_1_SOLEIL, SnowVictoryRoad_Text_SoleilIntro, SnowVictoryRoad_Text_SoleilDefeat
	msgbox SnowVictoryRoad_Text_SoleilPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Maren::
	trainerbattle_single TRAINER_SNOW_VR_2_MAREN, SnowVictoryRoad_Text_MarenIntro, SnowVictoryRoad_Text_MarenDefeat
	msgbox SnowVictoryRoad_Text_MarenPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Dune::
	trainerbattle_single TRAINER_SNOW_VR_3_DUNE, SnowVictoryRoad_Text_DuneIntro, SnowVictoryRoad_Text_DuneDefeat
	msgbox SnowVictoryRoad_Text_DunePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Neve::
	trainerbattle_single TRAINER_SNOW_VR_4_NEVE, SnowVictoryRoad_Text_NeveIntro, SnowVictoryRoad_Text_NeveDefeat
	msgbox SnowVictoryRoad_Text_NevePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Pyre::
	trainerbattle_single TRAINER_SNOW_VR_5_PYRE, SnowVictoryRoad_Text_PyreIntro, SnowVictoryRoad_Text_PyreDefeat
	msgbox SnowVictoryRoad_Text_PyrePostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Jinx::
	trainerbattle_single TRAINER_SNOW_VR_6_JINX, SnowVictoryRoad_Text_JinxIntro, SnowVictoryRoad_Text_JinxDefeat
	msgbox SnowVictoryRoad_Text_JinxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Zeno::
	trainerbattle_single TRAINER_SNOW_VR_7_ZENO, SnowVictoryRoad_Text_ZenoIntro, SnowVictoryRoad_Text_ZenoDefeat
	msgbox SnowVictoryRoad_Text_ZenoPostBattle, MSGBOX_AUTOCLOSE
	end

SnowVictoryRoad_EventScript_Kyros::
	trainerbattle_single TRAINER_SNOW_VR_8_KYROS, SnowVictoryRoad_Text_KyrosIntro, SnowVictoryRoad_Text_KyrosDefeat
	msgbox SnowVictoryRoad_Text_KyrosPostBattle, MSGBOX_AUTOCLOSE
	end

@ Victory Road - 8 Ace Trainers, 48 Pokemon, Lv85-89 GAUNTLET.
@ 4 Weather teams (Soleil/Maren/Dune/Neve) + 4 Freestyle (Pyre/Jinx/Zeno/Kyros).

@ VR-1 Soleil (Ace Trainer) - SUN "Solar Forge". Ninetales Drought ace.
@ Voice: radiant, forged-in-fire, reveres the sun.

SnowVictoryRoad_Text_SoleilIntro:
	.string "SOLEIL.\p"
	.string "The sun doesn't set in this\n"
	.string "tunnel.\p"
	.string "NINETALES holds the Heat Rock.\n"
	.string "Permanent DROUGHT.$"

SnowVictoryRoad_Text_SoleilDefeat:
	.string "You outlived the sun.$"

SnowVictoryRoad_Text_SoleilPostBattle:
	.string "RAPIDASH's MORNING SUN heals\n"
	.string "66 percent in sun.\p"
	.string "I counted on three more turns.$"

@ VR-2 Maren (Ace Trainer) - RAIN "Monsoon". Politoed Drizzle + Azumarill BD ace.
@ Voice: deluge-tempered, thunderhead metaphors, calm.

SnowVictoryRoad_Text_MarenIntro:
	.string "MAREN.\p"
	.string "POLITOED brings the monsoon.\n"
	.string "THUNDER and HURRICANE hit at\l"
	.string "100 percent in rain.\p"
	.string "AZUMARILL closes with BELLY\n"
	.string "DRUM plus HUGE POWER.$"

SnowVictoryRoad_Text_MarenDefeat:
	.string "AZUMARILL at plus six with\n"
	.string "AQUA JET priority should have\l"
	.string "won.$"

SnowVictoryRoad_Text_MarenPostBattle:
	.string "360 BP priority in rain.\p"
	.string "Whatever you had, it was bigger.$"

@ VR-3 Dune (Ace Trainer) - SAND "Stone Tide". Hippowdon Sand Stream + Lucario Technician ace.
@ Voice: desert stoic, slow-burn, Boralyss-foreign.

SnowVictoryRoad_Text_DuneIntro:
	.string "DUNE.\p"
	.string "HIPPOWDON sets the sand.\n"
	.string "Everything not Rock-Ground-\l"
	.string "Steel takes chip per turn.\p"
	.string "LUCARIO's priority is the close.$"

SnowVictoryRoad_Text_DuneDefeat:
	.string "The sand cleared.\n"
	.string "You cleared it.$"

SnowVictoryRoad_Text_DunePostBattle:
	.string "TECHNICIAN LUCARIO hits with\n"
	.string "four priority moves, all\l"
	.string "boosted.\p"
	.string "You had priority too. Barely.$"

@ VR-4 Neve (Ace Trainer) - HAIL "Permafrost". Abomasnow + Glalie Refrigerate Explosion ace.
@ Voice: quiet, freezing, precise.

SnowVictoryRoad_Text_NeveIntro:
	.string "NEVE.\p"
	.string "Permanent hail. AURORA VEIL.\n"
	.string "Every hit halved for five\l"
	.string "turns.\p"
	.string "GLALIE's EXPLOSION is Ice-type.\n"
	.string "675 eff BP.$"

SnowVictoryRoad_Text_NeveDefeat:
	.string "The veil broke early.$"

SnowVictoryRoad_Text_NevePostBattle:
	.string "REFRIGERATE GLALIE is the\n"
	.string "hardest single Ice hit in\l"
	.string "Boralyss.\p"
	.string "You took it. Congratulations.$"

@ VR-5 Pyre (Ace Trainer) - FREESTYLE "Sacrifice/recoil". Darmanitan Sheer Force Fire Gem ace.
@ Voice: burning-out warrior, trade-for-trade, no regrets.

SnowVictoryRoad_Text_PyreIntro:
	.string "PYRE.\p"
	.string "Every mon on this team trades\n"
	.string "one for one.\p"
	.string "Even winning costs you.\n"
	.string "DARMANITAN hits 351 BP.$"

SnowVictoryRoad_Text_PyreDefeat:
	.string "Trade was net positive.\n"
	.string "For you.$"

SnowVictoryRoad_Text_PyrePostBattle:
	.string "ELECTRODE's AFTERMATH takes\n"
	.string "25 percent on contact KO.\p"
	.string "RAMPARDOS recoils. ARCHEOPS\n"
	.string "burns a Gem.\p"
	.string "Everything was designed to\n"
	.string "bleed.$"

@ VR-6 Jinx (Ace Trainer) - FREESTYLE "Mirror/Punishment". Togekiss paraflinch ace.
@ Voice: cold, observational, "you beat yourself" taunt.

SnowVictoryRoad_Text_JinxIntro:
	.string "JINX.\p"
	.string "Toxic Spikes. Unaware. Prankster\n"
	.string "burn. Effect Spore. Paraflinch.\p"
	.string "You beat yourself. I watch.$"

SnowVictoryRoad_Text_JinxDefeat:
	.string "You stopped flinching.\n"
	.string "Impressive.$"

SnowVictoryRoad_Text_JinxPostBattle:
	.string "QUAGSIRE's UNAWARE ignored\n"
	.string "every boost you made.\p"
	.string "Your setup was pointless.\n"
	.string "So you skipped it.$"

@ VR-7 Zeno (Ace Trainer) - FREESTYLE "Trick Room inversion". Beartic Intimidate ace.
@ Voice: backward-world philosopher, slow-speed appreciator.

SnowVictoryRoad_Text_ZenoIntro:
	.string "ZENO.\p"
	.string "Six mons. All slow. All Brave\n"
	.string "or Quiet.\p"
	.string "TRICK ROOM flips the world.\n"
	.string "In the inversion, I'm faster.$"

SnowVictoryRoad_Text_ZenoDefeat:
	.string "Five turns passed.\n"
	.string "You survived them.$"

SnowVictoryRoad_Text_ZenoPostBattle:
	.string "BEARTIC's INTIMIDATE drops\n"
	.string "your Attack. Then SD to plus\l"
	.string "two. Then ICICLE CRASH.\p"
	.string "First hit. Under TR.$"

@ VR-8 Kyros (Ace Trainer) - FREESTYLE "Last Stand". Gallade SD + Shadow Sneak ace.
@ Voice: final boss, no theatrics, pure focus.

SnowVictoryRoad_Text_KyrosIntro:
	.string "KYROS.\p"
	.string "No weather. No gimmick.\n"
	.string "Six individually lethal mons.\p"
	.string "Four priority moves across\n"
	.string "three types.\p"
	.string "You can't outspeed the close.$"

SnowVictoryRoad_Text_KyrosDefeat:
	.string "GALLADE's SHADOW SNEAK missed\n"
	.string "the OHKO.\p"
	.string "Clean fight.$"

SnowVictoryRoad_Text_KyrosPostBattle:
	.string "The league is through the north\n"
	.string "door.\p"
	.string "BRYNN. VESPER. REVERIE. WYATT.\n"
	.string "TYRIM.\p"
	.string "You earned your way here.\n"
	.string "Now earn the rest.$"
