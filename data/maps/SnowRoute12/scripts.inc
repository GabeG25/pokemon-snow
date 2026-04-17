SnowRoute12_MapScripts::
	.byte 0

SnowRoute12_EventScript_Nyx::
	trainerbattle_single TRAINER_SNOW_R12_1_NYX, SnowRoute12_Text_NyxIntro, SnowRoute12_Text_NyxDefeat
	msgbox SnowRoute12_Text_NyxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Holtz::
	trainerbattle_single TRAINER_SNOW_R12_2_HOLTZ, SnowRoute12_Text_HoltzIntro, SnowRoute12_Text_HoltzDefeat
	msgbox SnowRoute12_Text_HoltzPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Belmont::
	trainerbattle_single TRAINER_SNOW_R12_3_BELMONT, SnowRoute12_Text_BelmontIntro, SnowRoute12_Text_BelmontDefeat
	msgbox SnowRoute12_Text_BelmontPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Bard::
	trainerbattle_single TRAINER_SNOW_R12_4_BARD, SnowRoute12_Text_BardIntro, SnowRoute12_Text_BardDefeat
	msgbox SnowRoute12_Text_BardPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Elara::
	trainerbattle_single TRAINER_SNOW_R12_5_ELARA, SnowRoute12_Text_ElaraIntro, SnowRoute12_Text_ElaraDefeat
	msgbox SnowRoute12_Text_ElaraPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Slade::
	trainerbattle_single TRAINER_SNOW_R12_6_SLADE, SnowRoute12_Text_SladeIntro, SnowRoute12_Text_SladeDefeat
	msgbox SnowRoute12_Text_SladePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute12_EventScript_Quinn::
	trainerbattle_single TRAINER_SNOW_R12_7_QUINN, SnowRoute12_Text_QuinnIntro, SnowRoute12_Text_QuinnDefeat
	msgbox SnowRoute12_Text_QuinnPostBattle, MSGBOX_AUTOCLOSE
	end

@ R12 Memoria Passage - Ghost/Psychic passage between Dragonforge and Solace.
@ FIRST EV ROUTE - all mons run 252/252/4 permanently from here.
@ Trainer names reference Nyx/Holtz/Belmont/Bard/Elara/Slade/Quinn literary figures.

@ R12-1 Special Agent Nyx - Mismagius/Honchkrow/Weavile, Tailwind closer.
@ Voice: Greek-night-goddess themed, brief, regal.

SnowRoute12_Text_NyxIntro:
	.string "NYX. Night goddess.\p"
	.string "MISMAGIUS floats. HONCHKROW\n"
	.string "carries Tailwind.\p"
	.string "WEAVILE doubles speed.\n"
	.string "You won't keep up.$"

SnowRoute12_Text_NyxDefeat:
	.string "Dawn caught me.$"

SnowRoute12_Text_NyxPostBattle:
	.string "The passage remembers every\n"
	.string "trainer who walked it.\p"
	.string "Now it remembers you.$"

@ R12-2 Scientist Holtz - Claydol/Espeon Light Screen + Calm Mind snowball.
@ Voice: Ghostbusters-named, nervous-academic, ghost-curious.

SnowRoute12_Text_HoltzIntro:
	.string "Scientist HOLTZ.\p"
	.string "The readings in this passage\n"
	.string "are... unusual.\p"
	.string "ESPEON boosts through the walls.$"

SnowRoute12_Text_HoltzDefeat:
	.string "Data corrupted.$"

SnowRoute12_Text_HoltzPostBattle:
	.string "LIGHT SCREEN halves special\n"
	.string "damage for five turns.\p"
	.string "ESPEON's CALM MIND needed\n"
	.string "three of those turns.$"

@ R12-3 Collector Belmont - Duosion/Musharna Trick Room synergy.
@ Voice: vampire-hunter-named, low-speed control wizard.

SnowRoute12_Text_BelmontIntro:
	.string "Collector BELMONT.\p"
	.string "Both my mons are base 30 speed.\n"
	.string "TRICK ROOM makes that optimal.$"

SnowRoute12_Text_BelmontDefeat:
	.string "Five turns wasn't enough.$"

SnowRoute12_Text_BelmontPostBattle:
	.string "DUOSION's MAGIC GUARD blocks\n"
	.string "everything indirect.\p"
	.string "You had to hit her directly.\n"
	.string "You did.$"

@ R12-4 Dragon Tamer Bard - Aggron Head Smash + Dragonite DD/ExtremeSpeed.
@ Voice: Tolkien-Bard-named, first-ever Dragonite trainer. Warrior-poet.

SnowRoute12_Text_BardIntro:
	.string "BARD.\p"
	.string "First DRAGONITE you'll face on\n"
	.string "the road. Extreme Speed hits\l"
	.string "through priority.\p"
	.string "AGGRON's HEAD SMASH has no\n"
	.string "recoil.$"

SnowRoute12_Text_BardDefeat:
	.string "The dragon was a weapon.\n"
	.string "You were a better one.$"

SnowRoute12_Text_BardPostBattle:
	.string "ROCK HEAD AGGRON throws 150\n"
	.string "BP Rock STAB without losing\l"
	.string "a single HP.\p"
	.string "You out-tempoed it.$"

@ R12-5 Scientist Elara - Sableye/Gardevoir/Magcargo/Umbreon. Dual setup threat.
@ Voice: named after Jupiter's moon, precise, setup-strategic.

SnowRoute12_Text_ElaraIntro:
	.string "ELARA.\p"
	.string "Burn team. GARDEVOIR Calm Minds.\n"
	.string "MAGCARGO Shell Smashes.\p"
	.string "Both preserved with WHITE HERB\n"
	.string "and SITRUS.$"

SnowRoute12_Text_ElaraDefeat:
	.string "UMBREON stalled too long.\n"
	.string "Your toxic built up first.$"

SnowRoute12_Text_ElaraPostBattle:
	.string "SABLEYE's FOUL PLAY uses your\n"
	.string "Attack stat against you.\p"
	.string "Physical setup sweepers\n"
	.string "are my favorite food.$"

@ R12-6/7 Special Agents Slade & Quinn - TAG DOUBLE route closer.
@ Voice: DC-named villains, team-coordinated, separate personalities.

SnowRoute12_Text_SladeIntro:
	.string "SLADE. Partner's QUINN.\p"
	.string "We don't lose doubles.$"

SnowRoute12_Text_SladeDefeat:
	.string "QUINN's lead broke.\n"
	.string "That's on me.$"

SnowRoute12_Text_SladePostBattle:
	.string "TOXICROAK's FAKE OUT was\n"
	.string "supposed to open with flinch.\p"
	.string "You switched.$"

SnowRoute12_Text_QuinnIntro:
	.string "QUINN.\p"
	.string "PRANKSTER Sleep Powder fires\n"
	.string "before your move.\p"
	.string "Figure THAT out.$"

SnowRoute12_Text_QuinnDefeat:
	.string "Huh.\n"
	.string "You figured it out.$"

SnowRoute12_Text_QuinnPostBattle:
	.string "BISHARP's DEFIANT punishes\n"
	.string "INTIMIDATE with plus two.\p"
	.string "If you led INTIMIDATE you\n"
	.string "fed her the buff.$"
