SnowRoute11_MapScripts::
	.byte 0

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
