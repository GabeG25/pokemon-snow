DawnflakeTown_AutumnsHouse_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn's Mom — warm, proud, encouraging
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_EventScript_AutumnsMom::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_AutumnsHouse_EventScript_AutumnsMomPostRival
	msgbox DawnflakeTown_AutumnsHouse_Text_AutumnsMom, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_AutumnsHouse_EventScript_AutumnsMomPostRival::
	msgbox DawnflakeTown_AutumnsHouse_Text_AutumnsMomPostRival, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Autumn's Dad — academic, quietly proud
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_EventScript_AutumnsDad::
	lock
	faceplayer
	msgbox DawnflakeTown_AutumnsHouse_Text_AutumnsDad, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Field notebook — Autumn's messy research desk
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_EventScript_Notebook::
	msgbox DawnflakeTown_AutumnsHouse_Text_Notebook, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_Text_AutumnsMom:
	.string "AUTUMN'S MOM: Oh hello! You must\n"
	.string "be {PLAYER}.\p"
	.string "Autumn's talked about you all\n"
	.string "week. 'The new kid is finally\l"
	.string "getting a Pokemon, Mom, FINALLY!'\p"
	.string "She ran out of here at dawn with\n"
	.string "three notebooks and a thermos.\p"
	.string "If you see her, tell her to\n"
	.string "come home for dinner. She\l"
	.string "forgets.$"

DawnflakeTown_AutumnsHouse_Text_AutumnsMomPostRival:
	.string "AUTUMN'S MOM: Did you meet her\n"
	.string "out on the road? Isn't she a\l"
	.string "whirlwind?\p"
	.string "That girl has wanted to be a\n"
	.string "field researcher since she\l"
	.string "was four years old.\p"
	.string "Four! She used to catalogue the\n"
	.string "bugs in our garden by color.\p"
	.string "I'm so glad she has a friend\n"
	.string "her age out there.$"

DawnflakeTown_AutumnsHouse_Text_AutumnsDad:
	.string "AUTUMN'S DAD: Shh - I'm reviewing\n"
	.string "her latest field notes.\p"
	.string "She's already spotted a behavior\n"
	.string "in the local SENTRET population\l"
	.string "that isn't in any of the books.\p"
	.string "Thermoregulation through the\n"
	.string "tail. Fascinating, really.\p"
	.string "She's going to be published\n"
	.string "before she's sixteen at this\l"
	.string "rate. Don't tell her I said so.$"

DawnflakeTown_AutumnsHouse_Text_Notebook:
	.string "A messy desk covered in notebooks,\n"
	.string "charts, and thermometer readings.\p"
	.string "One page is headed:\n"
	.string "'THINGS THAT ARE WRONG WITH\l"
	.string "THIS WINTER (WORKING LIST)'\p"
	.string "The list is three pages long.\n"
	.string "Most of the entries are circled.$"
