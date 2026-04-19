DawnflakeTown_AutumnsHouse_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Autumn's Mom — warm, proud, encouraging
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_EventScript_AutumnsMom::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_AutumnsHouse_EventScript_AutumnsMomPostRival
	goto_if_set FLAG_SNOW_TOLD_AUTUMN, DawnflakeTown_AutumnsHouse_EventScript_AutumnsMomAtLab
	msgbox DawnflakeTown_AutumnsHouse_Text_AutumnsMomUpstairs, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_AutumnsHouse_EventScript_AutumnsMomAtLab::
	msgbox DawnflakeTown_AutumnsHouse_Text_AutumnsMomAtLab, MSGBOX_DEFAULT
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

DawnflakeTown_AutumnsHouse_Text_AutumnsMomUpstairs:
	.string "AUTUMN'S MOM: Oh - {PLAYER}!\p"
	.string "AUTUMN's been pacing upstairs\n"
	.string "all morning, wound tight as a\l"
	.string "spring about today.\p"
	.string "Go on up. She'll calm down\n"
	.string "the moment she sees you.$"

DawnflakeTown_AutumnsHouse_Text_AutumnsMomAtLab:
	.string "AUTUMN'S MOM: Did you see her\n"
	.string "fly past on your way down?\p"
	.string "Out the door before I could\n"
	.string "say a word. Off to PROF.\l"
	.string "EVERGREEN's lab.\p"
	.string "She's been waiting all winter\n"
	.string "for her first POKEMON.\p"
	.string "Don't keep her standing\n"
	.string "around, will you?$"

DawnflakeTown_AutumnsHouse_Text_AutumnsMomPostRival:
	.string "AUTUMN'S MOM: She ran past\n"
	.string "again on her way out of town.\p"
	.string "Said she's meeting you on\n"
	.string "ROUTE 1 for field data.\p"
	.string "She's wanted to be a researcher\n"
	.string "since she was four years old.\p"
	.string "Cataloguing bugs in our garden\n"
	.string "by color, before she could\l"
	.string "spell 'thermometer.'\p"
	.string "Look out for her out there.\n"
	.string "Both of you.$"

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
