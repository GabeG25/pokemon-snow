SnowRoute9_MapScripts::
	.byte 0

SnowRoute9_EventScript_Jonas::
	trainerbattle_single TRAINER_SNOW_R9_1_JONAS, SnowRoute9_Text_JonasIntro, SnowRoute9_Text_JonasDefeat
	msgbox SnowRoute9_Text_JonasPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Sterling::
	trainerbattle_single TRAINER_SNOW_R9_2_STERLING, SnowRoute9_Text_SterlingIntro, SnowRoute9_Text_SterlingDefeat
	msgbox SnowRoute9_Text_SterlingPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Vince::
	trainerbattle_single TRAINER_SNOW_R9_3_VINCE, SnowRoute9_Text_VinceIntro, SnowRoute9_Text_VinceDefeat
	msgbox SnowRoute9_Text_VincePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Burke::
	trainerbattle_single TRAINER_SNOW_R9_4_BURKE, SnowRoute9_Text_BurkeIntro, SnowRoute9_Text_BurkeDefeat
	msgbox SnowRoute9_Text_BurkePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Marsh::
	trainerbattle_single TRAINER_SNOW_R9_5_MARSH, SnowRoute9_Text_MarshIntro, SnowRoute9_Text_MarshDefeat
	msgbox SnowRoute9_Text_MarshPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Iris::
	trainerbattle_single TRAINER_SNOW_R9_6_IRIS, SnowRoute9_Text_IrisIntro, SnowRoute9_Text_IrisDefeat
	msgbox SnowRoute9_Text_IrisPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Coral::
	trainerbattle_single TRAINER_SNOW_R9_7_CORAL, SnowRoute9_Text_CoralIntro, SnowRoute9_Text_CoralDefeat
	msgbox SnowRoute9_Text_CoralPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute9_EventScript_Troy::
	trainerbattle_single TRAINER_SNOW_R9_8_TROY, SnowRoute9_Text_TroyIntro, SnowRoute9_Text_TroyDefeat
	msgbox SnowRoute9_Text_TroyPostBattle, MSGBOX_AUTOCLOSE
	end

@ R9 Iceharbor Bay - coastal approach to Iceharbor (Gym 5 Marina Water).
@ 6 main trainers + 2 Surf-gated post-Gym-5 backtrack.

@ R9-1 Fisherman Jonas - Corsola/Stunfisk/Sharpedo opener.
@ Voice: salt-weathered, short sentences, respects the sea.

SnowRoute9_Text_JonasIntro:
	.string "Tide's in. My turn.\p"
	.string "CORSOLA walls you. STUNFISK\n"
	.string "carries the Ground. SHARPEDO\l"
	.string "ends it.$"

SnowRoute9_Text_JonasDefeat:
	.string "Fast learner.$"

SnowRoute9_Text_JonasPostBattle:
	.string "SHARPEDO's ROUGH SKIN bites\n"
	.string "back on every contact.\p"
	.string "You felt that.$"

@ R9-2 Tycoon Sterling - 5-mon class debut, rare species.
@ Voice: wealthy, deliberate, treats battles as asset appreciation.

SnowRoute9_Text_SterlingIntro:
	.string "Tycoon STERLING.\p"
	.string "CRADILY. PORYGON2. CARRACOSTA.\n"
	.string "DRAGONAIR. EELEKTROSS.\p"
	.string "Five rarities. One battle.\n"
	.string "Make it worth the spectacle.$"

SnowRoute9_Text_SterlingDefeat:
	.string "That was worth every credit.$"

SnowRoute9_Text_SterlingPostBattle:
	.string "EELEKTROSS LEVITATES.\n"
	.string "It has zero weaknesses.\p"
	.string "You beat it anyway. That's\n"
	.string "a rare thing.$"

@ R9-3 Fisherman Vince - 2-mon Cloyster Shell Smash + Starmie anchor.
@ Voice: quiet veteran, contrast to Jonas's gruffness.

SnowRoute9_Text_VinceIntro:
	.string "CLOYSTER opens.\n"
	.string "SHELL SMASH, plus-two.\p"
	.string "You have one turn.$"

SnowRoute9_Text_VinceDefeat:
	.string "Priority move. Figures.$"

SnowRoute9_Text_VincePostBattle:
	.string "STARMIE's RECOVER kept me alive\n"
	.string "four turns. Five was too many.$"

@ R9-4 Sailor Burke - 4-mon rain team class debut, Golurk ace.
@ Voice: booming, naval, leans into "my rain wins" braggadocio.

SnowRoute9_Text_BurkeIntro:
	.string "Sailor BURKE.\p"
	.string "PELIPPER brings the rain.\n"
	.string "KINGLER hits in it.\p"
	.string "Everything after is cleanup.$"

SnowRoute9_Text_BurkeDefeat:
	.string "GOLURK wasn't supposed to go\n"
	.string "first.$"

SnowRoute9_Text_BurkePostBattle:
	.string "GHOST-type closer in a rain\n"
	.string "team. Caught you thinking.\p"
	.string "Respect.$"

@ R9-5 Sailor Marsh - Tentacruel Liquid Ooze + Electrode ace.
@ Voice: shorter, meaner than Burke; engineer-sailor hybrid.

SnowRoute9_Text_MarshIntro:
	.string "Grass type? TENTACRUEL has\n"
	.string "LIQUID OOZE. Your drain moves\l"
	.string "hurt YOU.\p"
	.string "Surprise.$"

SnowRoute9_Text_MarshDefeat:
	.string "ELECTRODE was the last word.\n"
	.string "You wrote a longer sentence.$"

SnowRoute9_Text_MarshPostBattle:
	.string "AFTERMATH takes 25 percent of\n"
	.string "your HP on KO by contact.\p"
	.string "I hope you noticed.$"

@ R9-6 Painter Iris - Lanturn/Lampent/Hippowdon/Lilligant weather painter.
@ Voice: descriptive, color-coded moves, more abstract than Lumi.

SnowRoute9_Text_IrisIntro:
	.string "LANTURN for blue.\n"
	.string "LAMPENT for violet.\p"
	.string "HIPPOWDON stirs the canvas.\n"
	.string "LILLIGANT blooms through it.$"

SnowRoute9_Text_IrisDefeat:
	.string "Beautiful fight.\n"
	.string "Wrong colors.$"

SnowRoute9_Text_IrisPostBattle:
	.string "LILLIGANT's OWN TEMPO means\n"
	.string "PETAL DANCE never confuses her.\p"
	.string "Perfectly painted.$"

@ R9-7 Swimmer Coral - SURF-GATED. Relicanth/Alomomola/Beartic.
@ Voice: post-Surf gated, knows you came back for her.

SnowRoute9_Text_CoralIntro:
	.string "You came back with SURF.\p"
	.string "Good. RELICANTH hits like rock\n"
	.string "from ten thousand years ago.$"

SnowRoute9_Text_CoralDefeat:
	.string "BEARTIC's Swords Dance didn't\n"
	.string "land.\p"
	.string "Fair.$"

SnowRoute9_Text_CoralPostBattle:
	.string "ALOMOMOLA's WISH landed on the\n"
	.string "wrong turn.\p"
	.string "Timing kills teams.$"

@ R9-8 Swimmer Troy - SURF-GATED. Jellicent/Walrein/Seismitoad/Ludicolo.
@ Voice: strategy-minded, notes ace synergies explicitly.

SnowRoute9_Text_TroyIntro:
	.string "JELLICENT walls.\n"
	.string "WALREIN stalls.\p"
	.string "LUDICOLO ends. In rain.\n"
	.string "RAIN DANCE buys the sweep.$"

SnowRoute9_Text_TroyDefeat:
	.string "The rain didn't hold.$"

SnowRoute9_Text_TroyPostBattle:
	.string "SEISMITOAD's STEALTH ROCK put\n"
	.string "your switch-ins at 12 percent\l"
	.string "before they moved.\p"
	.string "And you still won.$"
