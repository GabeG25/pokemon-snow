SnowRoute7_MapScripts::
	.byte 0

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
