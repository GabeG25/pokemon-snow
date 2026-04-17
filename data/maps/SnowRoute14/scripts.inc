SnowRoute14_MapScripts::
	.byte 0

SnowRoute14_EventScript_Cinder::
	trainerbattle_single TRAINER_SNOW_R14_1_CINDER, SnowRoute14_Text_CinderIntro, SnowRoute14_Text_CinderDefeat
	msgbox SnowRoute14_Text_CinderPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Marlow::
	trainerbattle_single TRAINER_SNOW_R14_2_MARLOW, SnowRoute14_Text_MarlowIntro, SnowRoute14_Text_MarlowDefeat
	msgbox SnowRoute14_Text_MarlowPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Cassia::
	trainerbattle_single TRAINER_SNOW_R14_3_CASSIA, SnowRoute14_Text_CassiaIntro, SnowRoute14_Text_CassiaDefeat
	msgbox SnowRoute14_Text_CassiaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Forge::
	trainerbattle_single TRAINER_SNOW_R14_4_FORGE, SnowRoute14_Text_ForgeIntro, SnowRoute14_Text_ForgeDefeat
	msgbox SnowRoute14_Text_ForgePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Vesta::
	trainerbattle_single TRAINER_SNOW_R14_5_VESTA, SnowRoute14_Text_VestaIntro, SnowRoute14_Text_VestaDefeat
	msgbox SnowRoute14_Text_VestaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Ember::
	trainerbattle_single TRAINER_SNOW_R14_6_EMBER, SnowRoute14_Text_EmberIntro, SnowRoute14_Text_EmberDefeat
	msgbox SnowRoute14_Text_EmberPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Vex::
	trainerbattle_single TRAINER_SNOW_R14_7_VEX, SnowRoute14_Text_VexIntro, SnowRoute14_Text_VexDefeat
	msgbox SnowRoute14_Text_VexPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Marek::
	trainerbattle_single TRAINER_SNOW_R14_8_MAREK, SnowRoute14_Text_MarekIntro, SnowRoute14_Text_MarekDefeat
	msgbox SnowRoute14_Text_MarekPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute14_EventScript_Halden::
	trainerbattle_single TRAINER_SNOW_R14_9_HALDEN, SnowRoute14_Text_HaldenIntro, SnowRoute14_Text_HaldenDefeat
	msgbox SnowRoute14_Text_HaldenPostBattle, MSGBOX_AUTOCLOSE
	end

@ R14 Cinderstone Path - volcanic gauntlet continuous from R13. No heal break.
@ Peak at R14-8 Marek+Halden Sailor tag double (4+4 = 8 mons, R14 PEAK).

@ R14-1 Cinder (Miner) - Torkoal/Golem/Golurk/Aggron "Stone Crushers".

SnowRoute14_Text_CinderIntro:
	.string "CINDER.\p"
	.string "Four stone mons. Two Rock Head\n"
	.string "recoil-free nukes.\p"
	.string "TORKOAL sets the rocks first.$"

SnowRoute14_Text_CinderDefeat:
	.string "GOLEM's explosion went early.\n"
	.string "That was on me.$"

SnowRoute14_Text_CinderPostBattle:
	.string "Eight more.\n"
	.string "Still no heal.$"

@ R14-2 Marlow (Fisherman) - Pelipper Drizzle + Poliwrath BD + Kingdra Swift Swim.

SnowRoute14_Text_MarlowIntro:
	.string "MARLOW.\p"
	.string "Rain team. POLIWRATH Belly\n"
	.string "Drums to plus six.\l"
	.string "KINGDRA doubles speed in rain.$"

SnowRoute14_Text_MarlowDefeat:
	.string "BELLY DRUM dropped too early.$"

SnowRoute14_Text_MarlowPostBattle:
	.string "KINGDRA's HYDRO PUMP in rain:\n"
	.string "272 effective BP per turn.\p"
	.string "You tanked how many?$"

@ R14-3 Cassia (Scientist) - 2 mon Magnezone + Iron Fist Metagross.

SnowRoute14_Text_CassiaIntro:
	.string "CASSIA.\p"
	.string "MAGNETON traps. METAGROSS\n"
	.string "punches.\p"
	.string "Iron Fist quad-punch ace.$"

SnowRoute14_Text_CassiaDefeat:
	.string "METEOR MASH missed the boost.$"

SnowRoute14_Text_CassiaPostBattle:
	.string "MAGNET PULL locks Steel mons.\n"
	.string "If you had a Steel switch-in,\l"
	.string "it died there.\p"
	.string "You didn't.$"

@ R14-4 Forge (Miner) - Stunfisk/Machoke Dynamic Punch + Lucario Technician priority.

SnowRoute14_Text_ForgeIntro:
	.string "FORGE.\p"
	.string "LUCARIO hits first with four\n"
	.string "priority moves.\p"
	.string "Speed doesn't save you.$"

SnowRoute14_Text_ForgeDefeat:
	.string "VACUUM WAVE wasn't enough.$"

SnowRoute14_Text_ForgePostBattle:
	.string "TECHNICIAN boosts moves at or\n"
	.string "under 60 BP.\p"
	.string "LUCARIO has four of them.\n"
	.string "All priority.$"

@ R14-5 Vesta (Dragon Tamer) - Dragonair MS + Meganium + Shelgon + Hydreigon turn-1 nuke.

SnowRoute14_Text_VestaIntro:
	.string "VESTA. Dragon's hoard.\p"
	.string "Four treasures. HYDREIGON\n"
	.string "fires DRACO METEOR turn one.\p"
	.string "Dragon Gem. Plus 30 percent.\n"
	.string "292 eff BP.$"

SnowRoute14_Text_VestaDefeat:
	.string "Gem spent. Team broke.\n"
	.string "Clean sweep, trainer.$"

SnowRoute14_Text_VestaPostBattle:
	.string "MEGANIUM's ADAPTABILITY Giga\n"
	.string "Drain healed more than it\l"
	.string "hurt.\p"
	.string "You bypassed it. Good instinct.$"

@ R14-6 Ember (Miner) - Larvitar Sash Endeavor + Probopass Lock-On + two Stealth Rock setters.

SnowRoute14_Text_EmberIntro:
	.string "EMBER.\p"
	.string "LARVITAR at 1 HP drags you\n"
	.string "down to 1 HP.\p"
	.string "That's the opening move.\n"
	.string "Trap and drain.$"

SnowRoute14_Text_EmberDefeat:
	.string "CLAYDOL's TRICK swap came\n"
	.string "too late.$"

SnowRoute14_Text_EmberPostBattle:
	.string "Two Stealth Rock setters\n"
	.string "on one team.\p"
	.string "DEFOG couldn't keep up. Your\n"
	.string "switches took full chip.$"

@ R14-7 Vex (Special Agent) - Intimidate-counterplay theme, Pawniard Defiant.

SnowRoute14_Text_VexIntro:
	.string "VEX.\p"
	.string "Lead INTIMIDATE at me and\n"
	.string "PAWNIARD gets plus two.\p"
	.string "DEFIANT eats your debuffs.$"

SnowRoute14_Text_VexDefeat:
	.string "SHIFTRY's TANGA BERRY burned\n"
	.string "on the wrong turn.$"

SnowRoute14_Text_VexPostBattle:
	.string "SHIFTRY's SD at plus two\n"
	.string "swept my last three turns.\p"
	.string "You cut it off first.$"

@ R14-8 Marek (Sailor) - TAG DOUBLE partner A. Rain team lead half.

SnowRoute14_Text_MarekIntro:
	.string "MAREK. Partner's HALDEN.\p"
	.string "Eight mons. Rain theme.\n"
	.string "R14 PEAK.$"

SnowRoute14_Text_MarekDefeat:
	.string "HALDEN. We regroup.$"

SnowRoute14_Text_MarekPostBattle:
	.string "CLOYSTER's SKILL LINK in rain\n"
	.string "fires five-hit ICICLE SPEAR\l"
	.string "and RAZOR SHELL.\p"
	.string "You walled both.$"

@ R14-9 Halden (Sailor) - TAG DOUBLE partner B. Disruption/explosion/cleanup half.

SnowRoute14_Text_HaldenIntro:
	.string "HALDEN.\p"
	.string "ELECTRODE has a CUSTAP BERRY.\n"
	.string "Priority EXPLOSION.\p"
	.string "Sacrifice play.$"

SnowRoute14_Text_HaldenDefeat:
	.string "STARMIE's RECOVER wasn't\n"
	.string "enough.$"

SnowRoute14_Text_HaldenPostBattle:
	.string "Eight mons between us. Three\n"
	.string "disruption layers.\p"
	.string "You still enter R15 with more\n"
	.string "HP than expected.\p"
	.string "Take it to AUTUMN.$"
