SnowRoute3_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ R3 Route Trainers — gauntlet (4) + Kael Veil grunt (5th)
@ Four distinct voices: cocky local kid / nerdy bug catcher /
@ earnest gym hopeful / burnt-out senior bug catcher
@ ═══════════════════════════════════════════════════════════

SnowRoute3_EventScript_Tate::
	trainerbattle_single TRAINER_SNOW_R3_1_TATE, SnowRoute3_Text_TateIntro, SnowRoute3_Text_TateDefeat
	msgbox SnowRoute3_Text_TatePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Liam::
	trainerbattle_single TRAINER_SNOW_R3_2_LIAM, SnowRoute3_Text_LiamIntro, SnowRoute3_Text_LiamDefeat
	msgbox SnowRoute3_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Faye::
	trainerbattle_single TRAINER_SNOW_R3_3_FAYE, SnowRoute3_Text_FayeIntro, SnowRoute3_Text_FayeDefeat
	msgbox SnowRoute3_Text_FayePostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute3_EventScript_Rowan::
	trainerbattle_single TRAINER_SNOW_R3_4_ROWAN, SnowRoute3_Text_RowanIntro, SnowRoute3_Text_RowanDefeat
	msgbox SnowRoute3_Text_RowanPostBattle, MSGBOX_AUTOCLOSE
	end

@ ═══════════════════════════════════════════════════════════
@ Kael — First Veil Contact (R3-5 grunt)
@ Polite, warm, terrifyingly sincere believer
@ ═══════════════════════════════════════════════════════════

SnowRoute3_EventScript_Kael::
	trainerbattle_single TRAINER_SNOW_R3_5_GRUNT, SnowRoute3_Text_KaelIntro, SnowRoute3_Text_KaelDefeat
	msgbox SnowRoute3_Text_KaelPostBattle, MSGBOX_AUTOCLOSE
	setflag FLAG_SNOW_KAEL_FIRST_VEIL_CONTACT
	end

@ ═══════════════════════════════════════════════════════════
@ Item balls
@ ═══════════════════════════════════════════════════════════

SnowRoute3_EventScript_TM05Protect::
	finditem ITEM_TM05
	setflag FLAG_SNOW_GOT_TM05_PROTECT
	end

SnowRoute3_EventScript_BrightPowder::
	finditem ITEM_BRIGHT_POWDER
	setflag FLAG_SNOW_GOT_BRIGHT_POWDER
	end

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

SnowRoute3_EventScript_PinehurstSign::
	msgbox SnowRoute3_Text_PinehurstSign, MSGBOX_SIGN
	end

SnowRoute3_EventScript_R4BranchSign::
	msgbox SnowRoute3_Text_R4BranchSign, MSGBOX_SIGN
	end

SnowRoute3_EventScript_VeilMonitorSign::
	msgbox SnowRoute3_Text_VeilMonitorSign, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

SnowRoute3_Text_TateIntro:
	.string "Whoa, an outsider! My dad said\n"
	.string "travelers come through here.\p"
	.string "I've NEVER lost a match in these\n"
	.string "woods. Not once!$"

SnowRoute3_Text_TateDefeat:
	.string "...huh?$"

SnowRoute3_Text_TatePostBattle:
	.string "Okay. Okay, that's fine.\n"
	.string "One loss doesn't mean anything.\p"
	.string "I just need more practice.\n"
	.string "That's all.$"

SnowRoute3_Text_LiamIntro:
	.string "Did you see the JOLTIK on the\n"
	.string "pine bark by the trail?\l"
	.string "Incredible!\p"
	.string "The bugs here are adapting to\n"
	.string "the cold in ways the field\l"
	.string "guides don't even mention.\p"
	.string "Let me show you what mine\n"
	.string "can do!$"

SnowRoute3_Text_LiamDefeat:
	.string "Ack! My notes!$"

SnowRoute3_Text_LiamPostBattle:
	.string "That was a great match. Your\n"
	.string "POKEMON fight smart.\p"
	.string "If you see a PINECO out here,\n"
	.string "don't startle it. Trust me.$"

SnowRoute3_Text_FayeIntro:
	.string "Hey! You're heading to\n"
	.string "PINEGROVE, right? To challenge\l"
	.string "CEDAR?\p"
	.string "Same! But I'm not going in there\n"
	.string "until I've beaten every trainer\l"
	.string "on this route. Starting with\l"
	.string "you.$"

SnowRoute3_Text_FayeDefeat:
	.string "Oh no...$"

SnowRoute3_Text_FayePostBattle:
	.string "You're actually ready. I can\n"
	.string "tell. I'm not - not yet.\p"
	.string "I'll train a few more days and\n"
	.string "then I'll catch up to you.$"

SnowRoute3_Text_RowanIntro:
	.string "ROWAN: Another kid with a\n"
	.string "backpack.\p"
	.string "I've been catching bugs in\n"
	.string "these woods since before the\l"
	.string "winter never ended. Long\l"
	.string "before.\p"
	.string "Something's off about this\n"
	.string "place lately. You feel it too?\p"
	.string "...Never mind. Let's battle.$"

SnowRoute3_Text_RowanDefeat:
	.string "ROWAN: Heh. Good.$"

SnowRoute3_Text_RowanPostBattle:
	.string "ROWAN: You're sharp. Listen -\p"
	.string "If you see anyone in a gray\n"
	.string "uniform down by the south exit,\l"
	.string "just keep walking. Don't talk\l"
	.string "to them. Don't ask questions.\p"
	.string "They don't like questions.$"

SnowRoute3_Text_KaelIntro:
	.string "KAEL: Hey - you. Stop right\n"
	.string "there.\p"
	.string "This area is under observation.\p"
	.string "...No, don't panic, traveler.\n"
	.string "TEAM VEIL isn't here to cause\l"
	.string "any trouble. We're just doing\l"
	.string "wildlife monitoring.\p"
	.string "Making sure the endless winter\n"
	.string "is treating the POKEMON well.\p"
	.string "DIRECTOR TYRELL takes that very\n"
	.string "seriously. It's beautiful work,\l"
	.string "really.\p"
	.string "...But I can't have outsiders\n"
	.string "wandering through my survey\l"
	.string "area.\p"
	.string "Tell you what - battle me.\n"
	.string "Win and I'll let you pass.\l"
	.string "Call it part of the study.$"

SnowRoute3_Text_KaelDefeat:
	.string "KAEL: Whoa! Easy there!$"

SnowRoute3_Text_KaelPostBattle:
	.string "KAEL: Hmph. You're strong.\p"
	.string "Your POKEMON adapt quickly -\n"
	.string "the kind of adaptation the\l"
	.string "research team will want to\l"
	.string "document.\p"
	.string "...\p"
	.string "Go on, then. Head south to\n"
	.string "PINEGROVE. Enjoy the winter.\p"
	.string "DIRECTOR TYRELL built it for\n"
	.string "all of us, you know. Even\l"
	.string "outsiders.\p"
	.string "...\p"
	.string "(Don't tell anyone I let you\n"
	.string "through. I'm supposed to\l"
	.string "report these encounters.)$"

SnowRoute3_Text_PinehurstSign:
	.string "PINEHURST WOODS\p"
	.string "The pines never shed their\n"
	.string "needles, even under the endless\l"
	.string "snow.\p"
	.string "- ICESPIRE PARKS COMMISSION$"

SnowRoute3_Text_R4BranchSign:
	.string "This path leads east to\n"
	.string "SNOW ROUTE 4.\p"
	.string "CLOSED - Hazardous winter\n"
	.string "conditions. Do not enter.\p"
	.string "- TEAM VEIL RESEARCH DIVISION$"

SnowRoute3_Text_VeilMonitorSign:
	.string "A small gray device is bolted\n"
	.string "to the pine trunk. A blinking\l"
	.string "light blinks twice, then goes\l"
	.string "still.\p"
	.string "A plaque reads:\p"
	.string "'WILDLIFE MONITORING STATION\n"
	.string "PROPERTY OF TEAM VEIL\l"
	.string "DO NOT TAMPER'$"
