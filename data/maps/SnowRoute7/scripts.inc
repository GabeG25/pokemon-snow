SnowRoute7_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ F10 AUTUMN — R7 Galetop Plateau, her "stepping back" moment
@ Per v17 §20, F10 Autumn #3 is mid-game rival where she realizes
@ her passion is research, not battling. After defeat she gifts the
@ player TM14 Acrobatics (v17 §15) and walks south.
@
@ Starter-keyed A/B/C per VAR_STARTER_MON. LOCALID 6.
@ ═══════════════════════════════════════════════════════════════

SnowRoute7_EventScript_AutumnF10::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F10_AUTUMN, SnowRoute7_EventScript_AutumnF10OfferTm
	msgbox SnowRoute7_Text_AutumnF10Intro, MSGBOX_DEFAULT
	closemessage
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute7_EventScript_AutumnF10VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute7_EventScript_AutumnF10VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute7_EventScript_AutumnF10VariantC
	release
	end

SnowRoute7_EventScript_AutumnF10VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F10_AUTUMN_A, SnowRoute7_Text_AutumnF10Defeat
	goto SnowRoute7_EventScript_AutumnF10AfterBattle

SnowRoute7_EventScript_AutumnF10VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F10_AUTUMN_B, SnowRoute7_Text_AutumnF10Defeat
	goto SnowRoute7_EventScript_AutumnF10AfterBattle

SnowRoute7_EventScript_AutumnF10VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F10_AUTUMN_C, SnowRoute7_Text_AutumnF10Defeat
	goto SnowRoute7_EventScript_AutumnF10AfterBattle

SnowRoute7_EventScript_AutumnF10AfterBattle::
	setflag FLAG_SNOW_BEAT_F10_AUTUMN
	msgbox SnowRoute7_Text_AutumnF10PostBattle, MSGBOX_DEFAULT
	closemessage
	goto SnowRoute7_EventScript_AutumnF10OfferTm

SnowRoute7_EventScript_AutumnF10OfferTm::
	giveitem ITEM_TM14, 1
	compare VAR_RESULT, FALSE
	goto_if_eq SnowRoute7_EventScript_AutumnF10BagFull
	setflag FLAG_SNOW_GOT_TM14_ACROBATICS
	msgbox SnowRoute7_Text_AutumnF10TmGift, MSGBOX_DEFAULT
	closemessage
	applymovement 6, SnowRoute7_Movement_AutumnF10Depart
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_R7
	removeobject 6
	release
	end

SnowRoute7_EventScript_AutumnF10BagFull::
	msgbox SnowRoute7_Text_AutumnF10BagFull, MSGBOX_DEFAULT
	release
	end

SnowRoute7_Movement_AutumnF10Depart:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SnowRoute7_Text_AutumnF10Intro:
	.string "AUTUMN: Hey! Hey.\p"
	.string "I was hoping you'd come\n"
	.string "through GALETOP today.\p"
	.string "I've been up at the LODGE\n"
	.string "reading PROF. EVERGREEN's\l"
	.string "field notes.\p"
	.string "{PLAYER}, I... I want to have\n"
	.string "one more battle with you.\p"
	.string "Properly, this time.\n"
	.string "Full team, no holding back.\p"
	.string "And then I want to tell you\n"
	.string "something. But battle first!$"

SnowRoute7_Text_AutumnF10Defeat:
	.string "AUTUMN: You're really\n"
	.string "something, {PLAYER}.$"

SnowRoute7_Text_AutumnF10PostBattle:
	.string "AUTUMN: So here's the thing.\p"
	.string "I love POKEMON. I love\n"
	.string "studying them. Notes,\l"
	.string "patterns, the way species\l"
	.string "learn new moves...\p"
	.string "But battling at YOUR level?\n"
	.string "I don't think I can keep up.\p"
	.string "And honestly? I don't want\n"
	.string "to. That's not where my\l"
	.string "passion lives.\p"
	.string "EVERGREEN asked if I'd help\n"
	.string "with his research. I said\l"
	.string "yes.\p"
	.string "So this is me stepping back.\n"
	.string "A little, anyway.$"

SnowRoute7_Text_AutumnF10TmGift:
	.string "AUTUMN: Here. TM14.\p"
	.string "ACROBATICS. It's a physical\n"
	.string "Flying move. The user gets\l"
	.string "double power when holding\l"
	.string "no item.\p"
	.string "I was going to write a paper\n"
	.string "on it but... use it instead.\p"
	.string "One more fight, someday.\n"
	.string "When the time's right.\p"
	.string "Go beat SCORCH for me,\n"
	.string "{PLAYER}.$"

SnowRoute7_Text_AutumnF10BagFull:
	.string "AUTUMN: Your bag is full.\p"
	.string "I'll hold onto the TM. Make\n"
	.string "space and talk to me again.$"

SnowRoute7_EventScript_Harlan::
	trainerbattle_single TRAINER_SNOW_R7_1_HARLAN, SnowRoute7_Text_HarlanIntro, SnowRoute7_Text_HarlanDefeat
	msgbox SnowRoute7_Text_HarlanPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Corey::
	trainerbattle_single TRAINER_SNOW_R7_2_COREY, SnowRoute7_Text_CoreyIntro, SnowRoute7_Text_CoreyDefeat
	msgbox SnowRoute7_Text_CoreyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Opal::
	trainerbattle_single TRAINER_SNOW_R7_3_OPAL, SnowRoute7_Text_OpalIntro, SnowRoute7_Text_OpalDefeat
	msgbox SnowRoute7_Text_OpalPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Brenna::
	trainerbattle_single TRAINER_SNOW_R7_4_BRENNA, SnowRoute7_Text_BrennaIntro, SnowRoute7_Text_BrennaDefeat
	msgbox SnowRoute7_Text_BrennaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute7_EventScript_Lumi::
	trainerbattle_single TRAINER_SNOW_R7_5_LUMI, SnowRoute7_Text_LumiIntro, SnowRoute7_Text_LumiDefeat
	msgbox SnowRoute7_Text_LumiPostBattle, MSGBOX_AUTOCLOSE
	end

@ R7-1 Collector Harlan - Murkrow/Larvesta/Monferno/Porygon.
@ Voice: obsessive archivist, proud of the roster.

SnowRoute7_Text_HarlanIntro:
	.string "Four mons nobody else climbs\n"
	.string "with. I collected them.\p"
	.string "MURKROW crits half the time.\n"
	.string "In BORALYSS that's double damage.$"

SnowRoute7_Text_HarlanDefeat:
	.string "Fine specimens, all four.\n"
	.string "Still not enough.$"

SnowRoute7_Text_HarlanPostBattle:
	.string "PORYGON copies whatever DOWNLOAD\n"
	.string "tells it to fear most.\p"
	.string "Today it feared you.$"

@ R7-2 Youngster Corey - parafusion + Swagger disruption.
@ Voice: overeager kid, quotes strategy he half-understands.

SnowRoute7_Text_CoreyIntro:
	.string "SWAGGER! Confuse you, boost\n"
	.string "your Attack, watch you hit\l"
	.string "yourself!\p"
	.string "It's GALAXY BRAIN, right?$"

SnowRoute7_Text_CoreyDefeat:
	.string "You didn't hit yourself\n"
	.string "once!$"

SnowRoute7_Text_CoreyPostBattle:
	.string "FLAAFFY's THUNDER WAVE plus\n"
	.string "CONFUSE RAY is called parafusion.\p"
	.string "I read about it!$"

@ R7-3 Scientist Opal - Synchronize + Magic Guard tech.
@ Voice: dry, precise, competitor more than conversationalist.

SnowRoute7_Text_OpalIntro:
	.string "Status won't help you.\n"
	.string "XATU bounces it back.\p"
	.string "DUOSION is unkillable.\n"
	.string "Please stop reading articles\l"
	.string "about me.$"

SnowRoute7_Text_OpalDefeat:
	.string "Hmm. Metang missed the\n"
	.string "Agility window.$"

SnowRoute7_Text_OpalPostBattle:
	.string "MAGIC GUARD blocks all indirect\n"
	.string "damage. Stealth Rock, poison,\l"
	.string "burn, Life Orb - nothing.\p"
	.string "You hit it directly. Fine.$"

@ R7-4 Skier Brenna - ONE MON (Piloswine endurance test).
@ Voice: stoic, two-sentence warrior. All Piloswine energy.

SnowRoute7_Text_BrennaIntro:
	.string "One mon.\p"
	.string "Longer than four.$"

SnowRoute7_Text_BrennaDefeat:
	.string "Curse wasn't enough.$"

SnowRoute7_Text_BrennaPostBattle:
	.string "PILOSWINE took eleven turns\n"
	.string "against the last trainer.\p"
	.string "You did it in nine.\n"
	.string "Respect.$"

@ R7-5 Painter Lumi - last before Autumn. Togetic/Corsola/Musharna.
@ Voice: soft, observant, sees you as a subject before an opponent.

SnowRoute7_Text_LumiIntro:
	.string "Hold still, trainer.\n"
	.string "I want to paint you mid-battle.\p"
	.string "TOGETIC flinches. CORSOLA bleeds\n"
	.string "light. Give me ten turns.$"

SnowRoute7_Text_LumiDefeat:
	.string "Beautiful. Quick.\n"
	.string "Hard to capture.$"

SnowRoute7_Text_LumiPostBattle:
	.string "AUTUMN is at the peak.\p"
	.string "She'll paint you too,\n"
	.string "but with harder brushes.$"
