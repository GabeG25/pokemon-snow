SnowRoute11_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ F14 ASHER — R11 Brightbloom Meadow, his first Veil-era fight
@ ═══════════════════════════════════════════════════════════════
@ Per v17 cast: Works for Veil F14–F21. F14 is the first fight
@ where the player sees him wearing the uniform (or whatever Veil
@ signal). Team introduces the Persian/Breloom/Cloyster core that
@ persists through F21/F30. LOCALID 7. Starter-keyed A/B/C.

SnowRoute11_EventScript_AsherF14::
	lock
	faceplayer
	msgbox SnowRoute11_Text_AsherF14Intro, MSGBOX_DEFAULT
	closemessage
	compare VAR_STARTER_MON, 0
	goto_if_eq SnowRoute11_EventScript_AsherF14VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq SnowRoute11_EventScript_AsherF14VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq SnowRoute11_EventScript_AsherF14VariantC
	release
	end

SnowRoute11_EventScript_AsherF14VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F14_ASHER_A, SnowRoute11_Text_AsherF14Defeat
	goto SnowRoute11_EventScript_AsherF14AfterBattle

SnowRoute11_EventScript_AsherF14VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F14_ASHER_B, SnowRoute11_Text_AsherF14Defeat
	goto SnowRoute11_EventScript_AsherF14AfterBattle

SnowRoute11_EventScript_AsherF14VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F14_ASHER_C, SnowRoute11_Text_AsherF14Defeat
	goto SnowRoute11_EventScript_AsherF14AfterBattle

SnowRoute11_EventScript_AsherF14AfterBattle::
	setflag FLAG_SNOW_BEAT_F14_ASHER
	msgbox SnowRoute11_Text_AsherF14PostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 7, SnowRoute11_Movement_AsherF14Depart
	waitmovement 0
	setflag FLAG_SNOW_HIDE_ASHER_R11
	removeobject 7
	release
	end

SnowRoute11_Movement_AsherF14Depart:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SnowRoute11_Text_AsherF14Intro:
	.string "ASHER: {PLAYER}.\p"
	.string "You're looking at me like\n"
	.string "you don't recognize this\l"
	.string "crest.\p"
	.string "It's TEAM VEIL. I work for\n"
	.string "TYRELL now.\p"
	.string "Before you say anything,\n"
	.string "save it. I know what\l"
	.string "EVERGREEN thinks. I know\l"
	.string "what PRIYO says.\p"
	.string "They don't know what TYRELL\n"
	.string "is BUILDING.\p"
	.string "KYUREM isn't a weapon. It's\n"
	.string "a correction.\p"
	.string "Fight me, {PLAYER}. Convince\n"
	.string "me you belong on the side\l"
	.string "that stops it.$"

SnowRoute11_Text_AsherF14Defeat:
	.string "ASHER: ...Shut up.$"

SnowRoute11_Text_AsherF14PostBattle:
	.string "ASHER: You're still ahead of\n"
	.string "me. Fine.\p"
	.string "Doesn't change what I\n"
	.string "decided. I'm not turning\l"
	.string "around.\p"
	.string "TYRELL said you'd show up\n"
	.string "at Facility BETA eventually.\p"
	.string "He's right.\p"
	.string "I'll be there when you do.$"

SnowRoute11_EventScript_Vera::
	trainerbattle_single TRAINER_SNOW_R11_1_VERA, SnowRoute11_Text_VeraIntro, SnowRoute11_Text_VeraDefeat
	msgbox SnowRoute11_Text_VeraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Tucker::
	trainerbattle_single TRAINER_SNOW_R11_2_TUCKER, SnowRoute11_Text_TuckerIntro, SnowRoute11_Text_TuckerDefeat
	msgbox SnowRoute11_Text_TuckerPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Cypress::
	trainerbattle_single TRAINER_SNOW_R11_3_CYPRESS, SnowRoute11_Text_CypressIntro, SnowRoute11_Text_CypressDefeat
	msgbox SnowRoute11_Text_CypressPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Nina::
	trainerbattle_single TRAINER_SNOW_R11_4_NINA, SnowRoute11_Text_NinaIntro, SnowRoute11_Text_NinaDefeat
	msgbox SnowRoute11_Text_NinaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Cade::
	trainerbattle_single TRAINER_SNOW_R11_5_CADE, SnowRoute11_Text_CadeIntro, SnowRoute11_Text_CadeDefeat
	msgbox SnowRoute11_Text_CadePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute11_EventScript_Odette::
	trainerbattle_single TRAINER_SNOW_R11_6_ODETTE, SnowRoute11_Text_OdetteIntro, SnowRoute11_Text_OdetteDefeat
	msgbox SnowRoute11_Text_OdettePostBattle, MSGBOX_AUTOCLOSE
	end

@ R11 Brightbloom Meadow - flower route before Dragonforge.
@ Mid-game breather. 6 trainers, last pre-Dragonforge approach.

@ R11-1 Lass Vera - Nidorina/Roselia/Vulpix/Glaceon flower team.
@ Voice: cheerful, meadow-wandering, flower-themed.

SnowRoute11_Text_VeraIntro:
	.string "Picked the perfect spot for a\n"
	.string "battle, didn't you?\p"
	.string "The flowers open at noon.\n"
	.string "Let's finish before then.$"

SnowRoute11_Text_VeraDefeat:
	.string "GLACEON froze, then thawed.\n"
	.string "You chose your moment.$"

SnowRoute11_Text_VeraPostBattle:
	.string "ROSELIA's TOXIC SPIKES stayed\n"
	.string "on the field.\p"
	.string "Your next switch paid the\n"
	.string "price.$"

@ R11-2 Sailor Tucker - Staraptor/Breloom/Ampharos. Mach Punch + Spore.
@ Voice: confident sailor, rotating power hitters.

SnowRoute11_Text_TuckerIntro:
	.string "STARAPTOR Intimidates. BRELOOM\n"
	.string "Spores. AMPHAROS cleans up.\p"
	.string "Standard Sailor rotation.$"

SnowRoute11_Text_TuckerDefeat:
	.string "COTTON GUARD didn't save me.\n"
	.string "Respect.$"

SnowRoute11_Text_TuckerPostBattle:
	.string "BRELOOM's COBA BERRY survived\n"
	.string "one Flying hit. The second\l"
	.string "killed it.\p"
	.string "Tight math.$"

@ R11-3 Bug Catcher Cypress - Larvesta/Scolipede/Drapion/Yanmega.
@ Voice: older than Miles or Wren, studied entomologist energy.

SnowRoute11_Text_CypressIntro:
	.string "Bug-type has grown up.\n"
	.string "Four fully evolved threats.\p"
	.string "SCOLIPEDE leads Swords Dance.$"

SnowRoute11_Text_CypressDefeat:
	.string "YANMEGA's SPEED BOOST didn't\n"
	.string "snowball in time.$"

SnowRoute11_Text_CypressPostBattle:
	.string "DRAPION's BATTLE ARMOR blocked\n"
	.string "your crit gambles.\p"
	.string "Boralyss doubles crits. You\n"
	.string "know that.$"

@ R11-4 Lass Nina - 1 mon Mawile Sheer Force SD sweeper.
@ Voice: tiny, direct, Brenna-adjacent endurance wall.

SnowRoute11_Text_NinaIntro:
	.string "MAWILE.\p"
	.string "Steel-Fairy. Nine resistances.\n"
	.string "Good luck.$"

SnowRoute11_Text_NinaDefeat:
	.string "Fire or Ground.\n"
	.string "You had the answer.$"

SnowRoute11_Text_NinaPostBattle:
	.string "SHEER FORCE makes her IRON HEAD\n"
	.string "hit 156 BP.\p"
	.string "PLAY ROUGH hits 175. You raced\n"
	.string "the SWORDS DANCE.$"

@ R11-5 Dragon Tamer Cade - Seadra Sniper crit engine + Tropius/Lapras.
@ Voice: younger than Zara, less polished, crit-hunter vibe.

SnowRoute11_Text_CadeIntro:
	.string "SEADRA's FOCUS ENERGY. SNIPER.\n"
	.string "Scope Lens. Guaranteed triple\l"
	.string "crits.\p"
	.string "Just watch.$"

SnowRoute11_Text_CadeDefeat:
	.string "The crits landed on MY side.$"

SnowRoute11_Text_CadePostBattle:
	.string "LAPRAS is a classic. She\n"
	.string "SINGS, then freezes.\p"
	.string "Didn't get there.$"

@ R11-6 Lady Odette - Kirlia Eviolite + Alolan Vulpix Encore/Disable + Fearow.
@ Voice: refined, older than Vivian, Helena-continuation arc.

SnowRoute11_Text_OdetteIntro:
	.string "KIRLIA refused to evolve.\n"
	.string "I respect her choice.\p"
	.string "EVIOLITE makes up the stats.$"

SnowRoute11_Text_OdetteDefeat:
	.string "ENCORE and DISABLE should have\n"
	.string "trapped you.\p"
	.string "You switched.$"

SnowRoute11_Text_OdettePostBattle:
	.string "The next route's MEMORIA\n"
	.string "PASSAGE. Everything past\l"
	.string "there runs full EVs.\p"
	.string "You're about to feel it.$"
