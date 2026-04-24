PowderpathVillage_House1_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ TM04 RETURN — old man gifts the TM; moved here from House3
@ so the gift lives with the couple who earned it together.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House1_EventScript_TM04OldTimer::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_TM04_RETURN, PowderpathVillage_House1_EventScript_TM04AlreadyGot
	msgbox PowderpathVillage_House1_Text_TM04Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM04
	compare VAR_RESULT, FALSE
	goto_if_eq PowderpathVillage_House1_EventScript_TM04BagFull
	setflag FLAG_SNOW_GOT_TM04_RETURN
	msgbox PowderpathVillage_House1_Text_TM04Outro, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House1_EventScript_TM04BagFull::
	msgbox PowderpathVillage_House1_Text_TM04BagFull, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House1_EventScript_TM04AlreadyGot::
	msgbox PowderpathVillage_House1_Text_TM04Return, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Old Lady — flavor, wife of the TM04 old man
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House1_EventScript_OldLady::
	lock
	faceplayer
	msgbox PowderpathVillage_House1_Text_OldLady, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House1_Text_TM04Intro:
	.string "OLD MAN: Old man, leaning on a\n"
	.string "shovel.\p"
	.string "Been watching you walk your team\n"
	.string "through town. They're close to\l"
	.string "you. I can tell.\p"
	.string "It's a particular way the small\n"
	.string "ones trail behind. Like they're\l"
	.string "still talking to you even when\l"
	.string "they're in their balls.\p"
	.string "That bond - I mean the real\n"
	.string "thing, the thing between you and\l"
	.string "them - that's what no one can\l"
	.string "freeze.\p"
	.string "Not the weather. Not the grey\n"
	.string "masks. Not anyone.\p"
	.string "Take this. It's older than I am.$"

PowderpathVillage_House1_Text_TM04Outro:
	.string "OLD MAN: RETURN gets stronger\n"
	.string "the more your POKEMON likes you.\p"
	.string "Simple as that. Good ones usually\n"
	.string "are.\p"
	.string "Keep that bond tight, {PLAYER}.\n"
	.string "You'll need it, up the mountain.$"

PowderpathVillage_House1_Text_TM04BagFull:
	.string "OLD MAN: Make room in your bag\n"
	.string "first. I'll hold it for you.\p"
	.string "No rush. I'm not going anywhere.$"

PowderpathVillage_House1_Text_TM04Return:
	.string "OLD MAN: Use it on the one that\n"
	.string "walks closest.\p"
	.string "You'll know which one.\p"
	.string "They always walk closest.$"

PowderpathVillage_House1_Text_OldLady:
	.string "OLD LADY: Oh - is he giving his\n"
	.string "speech again?\p"
	.string "Let him. He means every word of\n"
	.string "it. Fifty winters and still the\l"
	.string "same one.\p"
	.string "His FURRET used to sit right\n"
	.string "where you're standing, you know.\p"
	.string "Watched everybody who came in.\n"
	.string "Decided whether she liked them\l"
	.string "before they took their coats off.\p"
	.string "...\p"
	.string "She liked most people. She was\n"
	.string "kinder than he is.$"
