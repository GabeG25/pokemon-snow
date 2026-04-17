SnowRoute13_MapScripts::
	.byte 0

SnowRoute13_EventScript_Reese::
	trainerbattle_single TRAINER_SNOW_R13_1_REESE, SnowRoute13_Text_ReeseIntro, SnowRoute13_Text_ReeseDefeat
	msgbox SnowRoute13_Text_ReesePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Lyric::
	trainerbattle_single TRAINER_SNOW_R13_2_LYRIC, SnowRoute13_Text_LyricIntro, SnowRoute13_Text_LyricDefeat
	msgbox SnowRoute13_Text_LyricPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Mantis::
	trainerbattle_single TRAINER_SNOW_R13_3_MANTIS, SnowRoute13_Text_MantisIntro, SnowRoute13_Text_MantisDefeat
	msgbox SnowRoute13_Text_MantisPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Fern::
	trainerbattle_single TRAINER_SNOW_R13_4_FERN, SnowRoute13_Text_FernIntro, SnowRoute13_Text_FernDefeat
	msgbox SnowRoute13_Text_FernPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Vance::
	trainerbattle_single TRAINER_SNOW_R13_5_VANCE, SnowRoute13_Text_VanceIntro, SnowRoute13_Text_VanceDefeat
	msgbox SnowRoute13_Text_VancePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Hue::
	trainerbattle_single TRAINER_SNOW_R13_6_HUE, SnowRoute13_Text_HueIntro, SnowRoute13_Text_HueDefeat
	msgbox SnowRoute13_Text_HuePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Buzz::
	trainerbattle_single TRAINER_SNOW_R13_7_BUZZ, SnowRoute13_Text_BuzzIntro, SnowRoute13_Text_BuzzDefeat
	msgbox SnowRoute13_Text_BuzzPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Royce::
	trainerbattle_single TRAINER_SNOW_R13_8_ROYCE, SnowRoute13_Text_RoyceIntro, SnowRoute13_Text_RoyceDefeat
	msgbox SnowRoute13_Text_RoycePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute13_EventScript_Lana::
	trainerbattle_single TRAINER_SNOW_R13_9_LANA, SnowRoute13_Text_LanaIntro, SnowRoute13_Text_LanaDefeat
	msgbox SnowRoute13_Text_LanaPostBattle, MSGBOX_AUTOCLOSE
	end

@ R13 Verdant Jungle - 9-trainer gauntlet continuous with R14. No heal break.
@ Peak at R13-9 Ranger Lana (5 mons, Serperior Contrary ace).

@ R13-1 Reese (Bug Catcher) - "Pivot Hive" Yanmega/Forretress/Larvesta/Galvantula.

SnowRoute13_Text_ReeseIntro:
	.string "REESE. Pivot Hive.\p"
	.string "U-turn, Volt Switch, Pain\n"
	.string "Split. Nothing stays.$"

SnowRoute13_Text_ReeseDefeat:
	.string "GALVANTULA's THUNDER missed\n"
	.string "the wrong turn.$"

SnowRoute13_Text_ReesePostBattle:
	.string "Eight more before R14.\n"
	.string "No heal.$"

@ R13-2 Lyric (Musician) - "Lullaby Carousel" Wigglytuff/Lilligant/Altaria.

SnowRoute13_Text_LyricIntro:
	.string "LYRIC.\p"
	.string "Three voices. Two Hyper Voice\n"
	.string "conversions.\p"
	.string "ALTARIA's AERILATE is brand new.$"

SnowRoute13_Text_LyricDefeat:
	.string "The carousel stopped spinning.$"

SnowRoute13_Text_LyricPostBattle:
	.string "PIXILATE Hyper Voice = Fairy.\n"
	.string "AERILATE Hyper Voice = Flying.\p"
	.string "Same move. Two conversions.\n"
	.string "Same song.$"

@ R13-3 Mantis (Bug Catcher) - "Crit Team" Venomoth/Drapion/Scolipede/Kingler.

SnowRoute13_Text_MantisIntro:
	.string "MANTIS. Crit Team.\p"
	.string "KINGLER crabhammers at 50\n"
	.string "percent crit rate.\p"
	.string "Boralyss doubles crits.$"

SnowRoute13_Text_MantisDefeat:
	.string "The math broke on my side.$"

SnowRoute13_Text_MantisPostBattle:
	.string "SNIPER turns crits into 3x.\n"
	.string "Plus Boralyss 2x = 6x damage\l"
	.string "per crit hit.\p"
	.string "You walled it somehow.$"

@ R13-4 Fern (Pokemon Ranger) - "Three Recoveries" Umbreon/Vaporeon/Leafeon.

SnowRoute13_Text_FernIntro:
	.string "Three Eeveelutions.\p"
	.string "Three ways to not die.\n"
	.string "Pick one you can break.$"

SnowRoute13_Text_FernDefeat:
	.string "LEAFEON's Sub went down.\n"
	.string "Clean.$"

SnowRoute13_Text_FernPostBattle:
	.string "SUB behind POISON HEAL is\n"
	.string "the nastiest combo this route.\p"
	.string "You broke it on the setup turn.$"

@ R13-5 Vance (Pokemon Tycoon) - "Specimen Showcase" Lapras/Spiritomb/Eelektross/Cradily.

SnowRoute13_Text_VanceIntro:
	.string "Four rare specimens.\p"
	.string "SPIRITOMB sacrifices. CRADILY\n"
	.string "cannot be phazed. LAPRAS\l"
	.string "freeze-drys Water.\p"
	.string "EELEKTROSS has no weakness.$"

SnowRoute13_Text_VanceDefeat:
	.string "CRADILY was my exit plan.\n"
	.string "Exit denied.$"

SnowRoute13_Text_VancePostBattle:
	.string "SUCTION CUPS means nothing\n"
	.string "phazes CRADILY out.\p"
	.string "Every CURSE compounded.\n"
	.string "You killed it before six.$"

@ R13-6 Hue (Painter) - "Strategic Delay" Togekiss/Sigilyph/Lumineon/Chandelure.

SnowRoute13_Text_HueIntro:
	.string "HUE.\p"
	.string "FUTURE SIGHT fires two turns\n"
	.string "after I cast it.\p"
	.string "By the time it lands, you'll\n"
	.string "have switched.$"

SnowRoute13_Text_HueDefeat:
	.string "You kept the right mon in.$"

SnowRoute13_Text_HuePostBattle:
	.string "CHANDELURE's TRICK ROOM flips\n"
	.string "speed. Quiet nature makes it\l"
	.string "optimal.\p"
	.string "Five turns is a long time.$"

@ R13-7 Buzz (Bug Catcher) - "Three Tricks" Heracross/Magcargo/Carnivine.

SnowRoute13_Text_BuzzIntro:
	.string "BUZZ.\p"
	.string "Three tricks. Sash Reversal.\n"
	.string "Water Absorb Magcargo.\l"
	.string "Trick Room Carnivine.$"

SnowRoute13_Text_BuzzDefeat:
	.string "CARNIVINE's substitute broke\n"
	.string "on turn two.$"

SnowRoute13_Text_BuzzPostBattle:
	.string "MAGCARGO with WATER ABSORB\n"
	.string "is the fire/rock that eats\l"
	.string "your counter move.\p"
	.string "Surprise.$"

@ R13-8 Royce (Pokemon Tycoon) - "The Punch" 2-mon Rampardos + Druddigon Life Orb.

SnowRoute13_Text_RoyceIntro:
	.string "ROYCE.\p"
	.string "Two mons. Both nukes.\n"
	.string "RAMPARDOS Mold Breaker.\l"
	.string "DRUDDIGON Life Orb Sheer Force.\p"
	.string "CEO-one-off item. Enjoy.$"

SnowRoute13_Text_RoyceDefeat:
	.string "Life Orb chipped too fast.$"

SnowRoute13_Text_RoycePostBattle:
	.string "SHEER FORCE plus LIFE ORB =\n"
	.string "1.69x attack, zero recoil.\p"
	.string "Single two-mon fight doing\n"
	.string "four-mon damage.$"

@ R13-9 Lana (Pokemon Ranger) - R13 PEAK, 5 mons, Serperior Contrary ace.

SnowRoute13_Text_LanaIntro:
	.string "LANA. R13 closer.\p"
	.string "Five mons. Five styles.\n"
	.string "SERPERIOR's LEAF STORM grants\l"
	.string "plus two every cast.\p"
	.string "You flow directly into R14.\n"
	.string "No heal.$"

SnowRoute13_Text_LanaDefeat:
	.string "SERPERIOR at plus four was\n"
	.string "supposed to end this.\p"
	.string "R14 won't be kind.$"

SnowRoute13_Text_LanaPostBattle:
	.string "You walked through a nine-fight\n"
	.string "gauntlet and I was the last\l"
	.string "stop before the volcano.\p"
	.string "R14 starts now.$"
