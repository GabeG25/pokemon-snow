SnowRoute8_MapScripts::
	.byte 0

SnowRoute8_EventScript_Vivian::
	trainerbattle_single TRAINER_SNOW_R8_1_VIVIAN, SnowRoute8_Text_VivianIntro, SnowRoute8_Text_VivianDefeat
	msgbox SnowRoute8_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Tessa::
	trainerbattle_single TRAINER_SNOW_R8_2_TESSA, SnowRoute8_Text_TessaIntro, SnowRoute8_Text_TessaDefeat
	msgbox SnowRoute8_Text_TessaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Wren::
	trainerbattle_single TRAINER_SNOW_R8_3_WREN, SnowRoute8_Text_WrenIntro, SnowRoute8_Text_WrenDefeat
	msgbox SnowRoute8_Text_WrenPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Declan::
	trainerbattle_single TRAINER_SNOW_R8_4_DECLAN, SnowRoute8_Text_DeclanIntro, SnowRoute8_Text_DeclanDefeat
	msgbox SnowRoute8_Text_DeclanPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Claire::
	trainerbattle_single TRAINER_SNOW_R8_5_CLAIRE, SnowRoute8_Text_ClaireIntro, SnowRoute8_Text_ClaireDefeat
	msgbox SnowRoute8_Text_ClairePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute8_EventScript_Rook::
	trainerbattle_single TRAINER_SNOW_R8_6_ROOK, SnowRoute8_Text_RookIntro, SnowRoute8_Text_RookDefeat
	msgbox SnowRoute8_Text_RookPostBattle, MSGBOX_AUTOCLOSE
	end

@ R8 is Dreamurs Valley approach - meadow before the Fairy gym town.

@ R8-1 Lady Vivian - Skiploom/Nidorina/Bellossom/Azumarill meadow team.
@ Voice: warm, botanical, genteel but sharp.

SnowRoute8_Text_VivianIntro:
	.string "The meadow blooms three weeks\n"
	.string "before DREAMURS thaws.\p"
	.string "BELLOSSOM dances when she knows\n"
	.string "she's won.$"

SnowRoute8_Text_VivianDefeat:
	.string "She's not dancing.\n"
	.string "Oh.$"

SnowRoute8_Text_VivianPostBattle:
	.string "AZUMARILL's Huge Power doubles\n"
	.string "her Attack. I grew her from\l"
	.string "an egg. Isn't she darling.$"

@ R8-2 Musician Tessa - Ninetales/Altaria/Sigilyph. Musician class debut.
@ Voice: lyrical, references notes and keys.

SnowRoute8_Text_TessaIntro:
	.string "I tune ALTARIA like a harp.\p"
	.string "SING is the opening note.\n"
	.string "Your team sleeps through the\l"
	.string "concert.$"

SnowRoute8_Text_TessaDefeat:
	.string "Off-key.\n"
	.string "I'll rewrite the set.$"

SnowRoute8_Text_TessaPostBattle:
	.string "SIGILYPH is my bass line.\p"
	.string "MAGIC GUARD. No damage from\n"
	.string "outside the melody.$"

@ R8-3 Bug Catcher Wren - 2-mon Venomoth QD + Galvantula Sticky Web.
@ Voice: clipped, strategic, younger than Miles but colder.

SnowRoute8_Text_WrenIntro:
	.string "Two mons. Both setup.\p"
	.string "VENOMOTH's QUIVER DANCE is\n"
	.string "your problem.$"

SnowRoute8_Text_WrenDefeat:
	.string "Resisted hit still hurt.\n"
	.string "TINTED LENS, not luck.$"

SnowRoute8_Text_WrenPostBattle:
	.string "GALVANTULA's STICKY WEB stayed\n"
	.string "down. Next trainer's in trouble.\p"
	.string "You are not.$"

@ R8-4 Youngster Declan - Growlithe/Quagsire/Persian attrition.
@ Voice: stubborn, "wear you down" mentality.

SnowRoute8_Text_DeclanIntro:
	.string "GROWLITHE. QUAGSIRE. PERSIAN.\p"
	.string "Nothing one mon sweeps.\n"
	.string "I'll eat your PP.$"

SnowRoute8_Text_DeclanDefeat:
	.string "You had a GRASS move.\n"
	.string "QUAGSIRE hates that.$"

SnowRoute8_Text_DeclanPostBattle:
	.string "PERSIAN's FAKE OUT flinches for\n"
	.string "a turn every switch.\p"
	.string "Free chip every trade.$"

@ R8-5 Lass Claire - Wigglytuff/Clefable/Froslass Fairy gym preview.
@ Voice: bright, unselfconscious, genuine fan.

SnowRoute8_Text_ClaireIntro:
	.string "FRAN is my favorite gym leader\n"
	.string "and I want to BE her.\p"
	.string "WIGGLYTUFF, SING!$"

SnowRoute8_Text_ClaireDefeat:
	.string "FROSLASS outran me.\n"
	.string "I'll tell FRAN you're coming.$"

SnowRoute8_Text_ClairePostBattle:
	.string "CLEFABLE's MAGIC GUARD ignores\n"
	.string "Stealth Rock AND Life Orb\l"
	.string "recoil.\p"
	.string "FRAN taught me that.$"

@ R8-6 Special Agent Rook - Zorua Illusion + Krokorok Intimidate + Absol Super Luck.
@ Voice: cold, mission-brief, Veil-adjacent.

SnowRoute8_Text_RookIntro:
	.string "Special Agent ROOK.\p"
	.string "I'm not TEAM VEIL.\n"
	.string "But the lines are blurring.$"

SnowRoute8_Text_RookDefeat:
	.string "Noted.$"

SnowRoute8_Text_RookPostBattle:
	.string "ZORUA leads disguised as\n"
	.string "ABSOL. Illusion breaks on\l"
	.string "first hit.\p"
	.string "You noticed one turn late.\n"
	.string "I noticed sooner.$"
