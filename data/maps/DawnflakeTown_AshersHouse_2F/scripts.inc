DawnflakeTown_AshersHouse_2F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Unsent letter on the desk — ties Grandma's 1F beat
@ ("the boy is carrying more than any child should") to a
@ visible moment in Asher's bedroom.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AshersHouse_2F_EventScript_UnsentLetter::
	msgbox DawnflakeTown_AshersHouse_2F_Text_UnsentLetter, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AshersHouse_2F_Text_UnsentLetter:
	.string "A half-written letter on ASHER's\n"
	.string "desk, in a careful hand.\p"
	.string "The first line reads:\p"
	.string "'Mom, Dad - I don't know who\n"
	.string "you were before that day,\l"
	.string "but -'\p"
	.string "The rest is crossed out so\n"
	.string "hard the paper tore.$"
