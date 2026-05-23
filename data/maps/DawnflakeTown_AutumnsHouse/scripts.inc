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
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AutumnsHouse_Text_AutumnsMomUpstairs:
	.string "AUTUMN'S MOM: Oh - {PLAYER}!\p"
	.string "AUTUMN's been pacing upstairs\n"
	.string "all morning, wound tight as a\l"
	.string "spring about today.\p"
	.string "Go on up. She'll be ready to\n"
	.string "fly out the door the moment\l"
	.string "she sees you.$"

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
	.string "AUTUMN'S MOM: Oh, {PLAYER}!\p"
	.string "AUTUMN was just here a minute\n"
	.string "ago. Mumbled something about\l"
	.string "you and ROUTE 1 and ran right\l"
	.string "back out.\p"
	.string "She wants to teach you how to\n"
	.string "catch a POKEMON. She's been\l"
	.string "practicing the speech in the\l"
	.string "kitchen all morning.\p"
	.string "Go on. She'll be waiting.$"

DawnflakeTown_AutumnsHouse_Text_AutumnsDad:
	.string "AUTUMN'S DAD: Shh - I'm reviewing\n"
	.string "her latest field notes.\p"
	.string "She's already spotted a behavior\n"
	.string "in the local SENTRET population\l"
	.string "that isn't in any of the books.\p"
	.string "Thermoregulation through the\n"
	.string "tail. Fascinating, really.$"

