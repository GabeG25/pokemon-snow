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
	.string "An old and battered journal\n"
	.string "lies on the desk.\p"
	.string "It says:\p"
	.string "'I miss them. Sometimes I\n"
	.string "see them in the snow, and I\l"
	.string "can't tell if I should give\l"
	.string "up hope or if I already have.'\p"
	.string "...the rest of the page is\n"
	.string "ripped out.$"
