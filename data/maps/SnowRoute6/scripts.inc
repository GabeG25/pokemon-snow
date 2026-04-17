SnowRoute6_MapScripts::
	.byte 0

SnowRoute6_EventScript_Nadia::
	trainerbattle_single TRAINER_SNOW_R6_1_NADIA, SnowRoute6_Text_NadiaIntro, SnowRoute6_Text_NadiaDefeat
	msgbox SnowRoute6_Text_NadiaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Reed::
	trainerbattle_single TRAINER_SNOW_R6_2_REED, SnowRoute6_Text_ReedIntro, SnowRoute6_Text_ReedDefeat
	msgbox SnowRoute6_Text_ReedPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Wade::
	trainerbattle_single TRAINER_SNOW_R6_3_WADE, SnowRoute6_Text_WadeIntro, SnowRoute6_Text_WadeDefeat
	msgbox SnowRoute6_Text_WadePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Clark::
	trainerbattle_single TRAINER_SNOW_R6_4_CLARK, SnowRoute6_Text_ClarkIntro, SnowRoute6_Text_ClarkDefeat
	msgbox SnowRoute6_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Miles::
	trainerbattle_single TRAINER_SNOW_R6_5_MILES, SnowRoute6_Text_MilesIntro, SnowRoute6_Text_MilesDefeat
	msgbox SnowRoute6_Text_MilesPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Helena::
	trainerbattle_single TRAINER_SNOW_R6_6_HELENA, SnowRoute6_Text_HelenaIntro, SnowRoute6_Text_HelenaDefeat
	msgbox SnowRoute6_Text_HelenaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Ivy::
	trainerbattle_single TRAINER_SNOW_R6_7_IVY, SnowRoute6_Text_IvyIntro, SnowRoute6_Text_IvyDefeat
	msgbox SnowRoute6_Text_IvyPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute6_EventScript_Hale::
	trainerbattle_single TRAINER_SNOW_R6_8_HALE, SnowRoute6_Text_HaleIntro, SnowRoute6_Text_HaleDefeat
	msgbox SnowRoute6_Text_HalePostBattle, MSGBOX_AUTOCLOSE
	end

@ R6-1 Skier Nadia — route opener. Alolan Vulpix / Snorunt / Sneasel.
@ Voice: carving-line confidence. Frost Breath = crit teaching moment.

SnowRoute6_Text_NadiaIntro:
	.string "Nadia. Five-time slalom gold.\n"
	.string "I race things colder than you.\p"
	.string "Frost doesn't miss twice.$"

SnowRoute6_Text_NadiaDefeat:
	.string "Huh. Warmer than I expected.$"

SnowRoute6_Text_NadiaPostBattle:
	.string "Watch for the crits, trainer.\n"
	.string "BORALYSS doubles them.$"

@ R6-2 Boarder Reed — Skill Link Shellder spam.
@ Voice: loud, mid-trick, half-listening.

SnowRoute6_Text_ReedIntro:
	.string "SHELLDER hits five times,\n"
	.string "rider! You ready?\p"
	.string "Bet you're not.$"

SnowRoute6_Text_ReedDefeat:
	.string "Okay. Okay. Respect.$"

SnowRoute6_Text_ReedPostBattle:
	.string "Next run's on you.$"

@ R6-3 Fisherman Wade — status gauntlet. Hypnosis + Wrap + Supersonic.
@ Voice: patient, almost cruel.

SnowRoute6_Text_WadeIntro:
	.string "You rush the lake, you lose.\p"
	.string "Sleep. Wrap. Confuse.\n"
	.string "That's the order.$"

SnowRoute6_Text_WadeDefeat:
	.string "You were ready.\n"
	.string "Most aren't.$"

SnowRoute6_Text_WadePostBattle:
	.string "The ice thinks in its own time.\n"
	.string "So should you.$"

@ R6-4 Fisherman Clark — Rain Dance + Staryu Recover anchor.
@ Voice: young, cocky, shorter-tempered than Wade.

SnowRoute6_Text_ClarkIntro:
	.string "WADE's boring. Watch this.\p"
	.string "RAIN DANCE. Full speed.\n"
	.string "See you at the finish.$"

SnowRoute6_Text_ClarkDefeat:
	.string "STARYU's supposed to recover.\n"
	.string "Not from that.$"

SnowRoute6_Text_ClarkPostBattle:
	.string "Tell WADE I said hi. From\n"
	.string "the bottom of the lake.$"

@ R6-5 Bug Catcher Miles — Compound Eyes Sleep Powder 97.5%.
@ Voice: wired, over-excited about mechanics.

SnowRoute6_Text_MilesIntro:
	.string "97.5 percent! That's my\n"
	.string "VENONAT's SLEEP POWDER!\p"
	.string "I ran the MATH!$"

SnowRoute6_Text_MilesDefeat:
	.string "You woke up the wrong mon...$"

SnowRoute6_Text_MilesPostBattle:
	.string "YANMA's SPEED BOOST means I\n"
	.string "only lose by a few turns.\p"
	.string "Next time!$"

@ R6-6 Lady Helena — 2-mon sustain. Kirlia Calm Mind + Roselia Toxic.
@ Voice: poised, condescending without being mean.

SnowRoute6_Text_HelenaIntro:
	.string "I brought two, dear. That\n"
	.string "is all I need.\p"
	.string "KIRLIA. CALM MIND. Shall we?$"

SnowRoute6_Text_HelenaDefeat:
	.string "Oh.\n"
	.string "Well played, dear.$"

SnowRoute6_Text_HelenaPostBattle:
	.string "When ROSELIA's TOXIC lands,\n"
	.string "time becomes the enemy.\p"
	.string "You beat the clock.$"

@ R6-7 Skier Ivy — tag-double partner, leads with Follow Me + Hustle fangs.
@ Voice: sharper than Nadia, tactical narrator.

SnowRoute6_Text_IvyIntro:
	.string "IVY.\p"
	.string "HALE and I don't lose doubles.\n"
	.string "Turn around now.$"

SnowRoute6_Text_IvyDefeat:
	.string "HALE. We rebuild.$"

SnowRoute6_Text_IvyPostBattle:
	.string "Follow Me redirects.\n"
	.string "Hustle hits.\p"
	.string "That was supposed to work.$"

@ R6-8 Boarder Hale — tag-double partner, Pachirisu/Delibird/Ursaring.
@ Voice: relaxed, trusts Ivy, lets her call it.

SnowRoute6_Text_HaleIntro:
	.string "IVY told you. I'm just here\n"
	.string "to swing URSARING.$"

SnowRoute6_Text_HaleDefeat:
	.string "Fair. That was fair.$"

SnowRoute6_Text_HalePostBattle:
	.string "GLACIER LAKE freezes over\n"
	.string "in a week.\p"
	.string "Take the RAZOR CLAW before it\n"
	.string "does.$"
