SnowRoute10_MapScripts::
	.byte 0

SnowRoute10_EventScript_Hank::
	trainerbattle_single TRAINER_SNOW_R10_1_HANK, SnowRoute10_Text_HankIntro, SnowRoute10_Text_HankDefeat
	msgbox SnowRoute10_Text_HankPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Lyra::
	trainerbattle_single TRAINER_SNOW_R10_2_LYRA, SnowRoute10_Text_LyraIntro, SnowRoute10_Text_LyraDefeat
	msgbox SnowRoute10_Text_LyraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Nash::
	trainerbattle_single TRAINER_SNOW_R10_3_NASH, SnowRoute10_Text_NashIntro, SnowRoute10_Text_NashDefeat
	msgbox SnowRoute10_Text_NashPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Grimm::
	trainerbattle_single TRAINER_SNOW_R10_4_GRIMM, SnowRoute10_Text_GrimmIntro, SnowRoute10_Text_GrimmDefeat
	msgbox SnowRoute10_Text_GrimmPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Zara::
	trainerbattle_single TRAINER_SNOW_R10_5_ZARA, SnowRoute10_Text_ZaraIntro, SnowRoute10_Text_ZaraDefeat
	msgbox SnowRoute10_Text_ZaraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Felix::
	trainerbattle_single TRAINER_SNOW_R10_6_FELIX, SnowRoute10_Text_FelixIntro, SnowRoute10_Text_FelixDefeat
	msgbox SnowRoute10_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Sage::
	trainerbattle_single TRAINER_SNOW_R10_7_SAGE, SnowRoute10_Text_SageIntro, SnowRoute10_Text_SageDefeat
	msgbox SnowRoute10_Text_SagePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute10_EventScript_Boone::
	trainerbattle_single TRAINER_SNOW_R10_8_BOONE, SnowRoute10_Text_BooneIntro, SnowRoute10_Text_BooneDefeat
	msgbox SnowRoute10_Text_BoonePostBattle, MSGBOX_AUTOCLOSE
	end

@ R10 Snowburn Path - cave gauntlet from Iceharbor to Dragonforge.
@ Thermal extremes (Torkoal sun + Glalie ice). Gauntlet peak at R10-5
@ Dragon Tamer, closer at R10-8 Miner.

@ R10-1 Miner Hank - Torkoal sun + Aggron/Glalie/Lucario closer.
@ Voice: veteran mineshaft boss, dry humor, warns of the depths.

SnowRoute10_Text_HankIntro:
	.string "Welcome to SNOWBURN.\p"
	.string "TORKOAL brings the sun down\n"
	.string "here. GLALIE brings the cold.\p"
	.string "Cave does both at once.$"

SnowRoute10_Text_HankDefeat:
	.string "LUCARIO's BULLET PUNCH lost\n"
	.string "by a hair.$"

SnowRoute10_Text_HankPostBattle:
	.string "Seven more down the tunnel.\n"
	.string "Don't heal. Can't heal.\p"
	.string "Good luck.$"

@ R10-2 Scientist Lyra - Magneton Sturdy+Balloon, Gorilla Darmanitan, Espeon Magic Bounce.
@ Voice: academic, studying the thermals, treats battles as data.

SnowRoute10_Text_LyraIntro:
	.string "I'm measuring the cave's\n"
	.string "thermal cycle.\p"
	.string "Your team is a control group.$"

SnowRoute10_Text_LyraDefeat:
	.string "ESPEON's MAGIC BOUNCE was\n"
	.string "supposed to stop all that.$"

SnowRoute10_Text_LyraPostBattle:
	.string "MAGNETON had two stacked\n"
	.string "protections: STURDY and AIR\l"
	.string "BALLOON.\p"
	.string "You broke both.$"

@ R10-3 Miner Nash - Probopass/Magmar/Claydol. Probopass Explosion + Magmar Vital Spirit.
@ Voice: gruff, Hank-adjacent but colder, older.

SnowRoute10_Text_NashIntro:
	.string "PROBOPASS tanks. Then it\n"
	.string "EXPLODES.\p"
	.string "Your move.$"

SnowRoute10_Text_NashDefeat:
	.string "CLAYDOL held longer than I\n"
	.string "expected.$"

SnowRoute10_Text_NashPostBattle:
	.string "MAGMAR's VITAL SPIRIT. Sleep\n"
	.string "doesn't land.\p"
	.string "Everyone tries the SPORE trick\n"
	.string "once.$"

@ R10-4 Special Agent Grimm - 2 Dark-type Weavile + Honchkrow.
@ Voice: minimal, intimidating, Rook-family cold.

SnowRoute10_Text_GrimmIntro:
	.string "Eye of the storm.\p"
	.string "Two mons.\n"
	.string "Both Dark.$"

SnowRoute10_Text_GrimmDefeat:
	.string "Fighting types. Always.$"

SnowRoute10_Text_GrimmPostBattle:
	.string "WEAVILE's PRESSURE doubled\n"
	.string "PP loss on every move you\l"
	.string "used against her.\p"
	.string "Look at your team's PP.$"

@ R10-5 Dragon Tamer Zara - CLASS DEBUT, 5-mon peak difficulty.
@ Voice: calm, operatic, five-dragon choreographer.

SnowRoute10_Text_ZaraIntro:
	.string "Dragon Tamer ZARA.\p"
	.string "Five dragons.\n"
	.string "Each one teaches a different\l"
	.string "lesson.\p"
	.string "I hope you're taking notes.$"

SnowRoute10_Text_ZaraDefeat:
	.string "HAXORUS missed its window.\n"
	.string "You taught me something.$"

SnowRoute10_Text_ZaraPostBattle:
	.string "KINGDRA's FOCUS ENERGY plus\n"
	.string "SNIPER makes crits triple.\p"
	.string "HYDRO PUMP averaged 363 BP\n"
	.string "per turn.\p"
	.string "You outlived the math.$"

@ R10-6 Scientist Felix - Metang/Exeggutor/Cryogonal sun synergy.
@ Voice: younger than Lyra, more excitable, sun-deploy strategy.

SnowRoute10_Text_FelixIntro:
	.string "SUNNY DAY up top!\n"
	.string "EXEGGUTOR doubles speed!\p"
	.string "SLEEP POWDER hits YOU first!$"

SnowRoute10_Text_FelixDefeat:
	.string "CRYOGONAL... I depended on\n"
	.string "her too much.$"

SnowRoute10_Text_FelixPostBattle:
	.string "Sun weakened your WATER moves\n"
	.string "by half.\p"
	.string "Most trainers don't notice\n"
	.string "until mon three.$"

@ R10-7 Collector Sage - Spiritomb/Rampardos/Pupitar/Heracross.
@ Voice: obsessive, rare-mon focus, Heracross-pride.

SnowRoute10_Text_SageIntro:
	.string "RAMPARDOS has the highest ATK\n"
	.string "in the regional dex.\p"
	.string "HERACROSS ignites her own\n"
	.string "TOXIC ORB.\p"
	.string "I collect lethal things.$"

SnowRoute10_Text_SageDefeat:
	.string "HERACROSS burned out before\n"
	.string "she could close.$"

SnowRoute10_Text_SagePostBattle:
	.string "TOXIC ORB GUTS boosted every\n"
	.string "move by 50 percent.\p"
	.string "She punched above her price\n"
	.string "tag.$"

@ R10-8 Miner Boone - GAUNTLET CLOSER. Three Sturdy mons + Machamp No Guard + Gigalith ace.
@ Voice: patriarch of the mines, final boss of the route.

SnowRoute10_Text_BooneIntro:
	.string "Seven trainers told you about me.\p"
	.string "SKARMORY. FORRETRESS. GIGALITH.\n"
	.string "All STURDY.\p"
	.string "Plus MACHAMP's DYNAMIC PUNCH.\n"
	.string "One hundred percent confusion.$"

SnowRoute10_Text_BooneDefeat:
	.string "You had a special attacker\n"
	.string "left.\p"
	.string "Most don't make it this far.$"

SnowRoute10_Text_BoonePostBattle:
	.string "GIGALITH's CURSE escalates\n"
	.string "forever behind STURDY.\p"
	.string "You hit it hard enough, fast\n"
	.string "enough, special enough.\p"
	.string "DRAGONFORGE's waiting.$"
