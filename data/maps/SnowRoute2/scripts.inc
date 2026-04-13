SnowRoute2_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ R2 Route Trainers — four distinct voices
@ Brett: angry kid / Finn: tourist out of depth
@ Mila: Veil-curious civilian / Gus: hardened mountaineer
@ ═══════════════════════════════════════════════════════════

SnowRoute2_EventScript_Brett::
	trainerbattle_single TRAINER_SNOW_R2_1_BRETT, SnowRoute2_Text_BrettIntro, SnowRoute2_Text_BrettDefeat
	msgbox SnowRoute2_Text_BrettPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Finn::
	trainerbattle_single TRAINER_SNOW_R2_2_FINN, SnowRoute2_Text_FinnIntro, SnowRoute2_Text_FinnDefeat
	msgbox SnowRoute2_Text_FinnPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Mila::
	trainerbattle_single TRAINER_SNOW_R2_3_MILA, SnowRoute2_Text_MilaIntro, SnowRoute2_Text_MilaDefeat
	msgbox SnowRoute2_Text_MilaPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute2_EventScript_Gus::
	trainerbattle_single TRAINER_SNOW_R2_4_GUS, SnowRoute2_Text_GusIntro, SnowRoute2_Text_GusDefeat
	msgbox SnowRoute2_Text_GusPostBattle, MSGBOX_AUTOCLOSE
	end

@ ═══════════════════════════════════════════════════════════
@ TM02 Hone Claws — dropped on the frozen bridge
@ ═══════════════════════════════════════════════════════════

SnowRoute2_EventScript_TM02HoneClaws::
	finditem ITEM_TM02
	setflag FLAG_SNOW_GOT_TM02_HONE_CLAWS
	end

@ ═══════════════════════════════════════════════════════════
@ Flavor NPCs
@ ═══════════════════════════════════════════════════════════

SnowRoute2_EventScript_Mountaineer::
	lock
	faceplayer
	msgbox SnowRoute2_Text_Mountaineer, MSGBOX_DEFAULT
	release
	end

SnowRoute2_EventScript_LostTourist::
	lock
	faceplayer
	msgbox SnowRoute2_Text_LostTourist, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

SnowRoute2_EventScript_PassWarningSign::
	msgbox SnowRoute2_Text_PassWarningSign, MSGBOX_SIGN
	end

SnowRoute2_EventScript_FrozenStreamSign::
	msgbox SnowRoute2_Text_FrozenStreamSign, MSGBOX_SIGN
	end

SnowRoute2_EventScript_IcespireTownSign::
	msgbox SnowRoute2_Text_IcespireTownSign, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

@ Brett -----------------------------------------------------
SnowRoute2_Text_BrettIntro:
	.string "Hey! HEY!\p"
	.string "You can't just walk past me!\p"
	.string "I've been standing out here in\n"
	.string "the snow for HOURS waiting for\l"
	.string "a fight!$"

SnowRoute2_Text_BrettDefeat:
	.string "No fair! You got a lucky hit!$"

SnowRoute2_Text_BrettPostBattle:
	.string "My mom says I have to go home\n"
	.string "when my nose gets numb.\p"
	.string "My nose is REALLY numb.$"

@ Finn ------------------------------------------------------
SnowRoute2_Text_FinnIntro:
	.string "Oh! Another person!\p"
	.string "I thought I was the only one\n"
	.string "stupid enough to come up here.\p"
	.string "The brochure said 'scenic route.'\n"
	.string "It did NOT say 'perpetual blizzard.'\p"
	.string "Battle me? Maybe if I win I'll\n"
	.string "feel like less of an idiot.$"

SnowRoute2_Text_FinnDefeat:
	.string "I should have stayed in LILYCOVE...$"

SnowRoute2_Text_FinnPostBattle:
	.string "My fingers stopped working two\n"
	.string "hours ago. Is that normal?\p"
	.string "Don't answer that.$"

@ Mila ------------------------------------------------------
SnowRoute2_Text_MilaIntro:
	.string "You saw them too, didn't you?\n"
	.string "The ones in the grey hoods.\p"
	.string "They came through last week\n"
	.string "and then the stream froze\l"
	.string "solid. Overnight.\p"
	.string "I want to follow them, but I\n"
	.string "need to know I'm strong enough\l"
	.string "first.\p"
	.string "Battle me. Prove the pass is\n"
	.string "passable.$"

SnowRoute2_Text_MilaDefeat:
	.string "You're ready. I'm not.\n"
	.string "Not yet.$"

SnowRoute2_Text_MilaPostBattle:
	.string "If you catch up to them, don't\n"
	.string "look them in the eyes.\p"
	.string "That's what the old-timers in\n"
	.string "POWDERPATH say, anyway.$"

@ Gus -------------------------------------------------------
SnowRoute2_Text_GusIntro:
	.string "Forty winters on this pass.\p"
	.string "I know every rock by name.\n"
	.string "Rocks don't move. You do.\p"
	.string "That makes you the interesting\n"
	.string "one.\p"
	.string "Let's see what you're made of.$"

SnowRoute2_Text_GusDefeat:
	.string "Hmph. Good form.$"

SnowRoute2_Text_GusPostBattle:
	.string "Keep your pack dry and your\n"
	.string "claws sharp, kid.\p"
	.string "That TM up by the old bridge?\n"
	.string "Somebody dropped it crossing.\l"
	.string "Finders keepers, in the pass.$"

@ Mountaineer ----------------------------------------------
SnowRoute2_Text_Mountaineer:
	.string "ICESPIRE PASS.\p"
	.string "Three hours on foot, four if\n"
	.string "the wind picks up.\p"
	.string "Watch your footing on the bridge.\n"
	.string "Folks used to say the stream\l"
	.string "below ran loud enough to drown\l"
	.string "out a SNOVER's BLIZZARD.\p"
	.string "Now it just... doesn't.$"

@ Lost tourist ---------------------------------------------
SnowRoute2_Text_LostTourist:
	.string "Is this ICESPIRE yet? Please\n"
	.string "tell me this is ICESPIRE.\p"
	.string "I can see a roof down there.\n"
	.string "I'm gonna cry when I reach\l"
	.string "that roof.$"

@ Signs ----------------------------------------------------
SnowRoute2_Text_PassWarningSign:
	.string "ICESPIRE PASS\p"
	.string "Elevation climbs sharply ahead.\n"
	.string "Dress warm. Travel in daylight.\p"
	.string "Do not stop on the bridge.$"

SnowRoute2_Text_FrozenStreamSign:
	.string "THE LONGCREEK\p"
	.string "A running creek until last winter.\n"
	.string "Frozen solid since the DIRECTOR\l"
	.string "came through.\p"
	.string "- POWDERPATH Trail Authority$"

SnowRoute2_Text_IcespireTownSign:
	.string "ICESPIRE TOWN - just ahead\p"
	.string "Home of Gym Leader SILVAN.\n"
	.string "POKEMON CENTER open all hours.$"
