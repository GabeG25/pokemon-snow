PowderpathVillage_House3_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Mother — downstairs, keeps house, points player upstairs
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House3_EventScript_Mother::
	lock
	faceplayer
	msgbox PowderpathVillage_House3_Text_Mother, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House3_Text_Mother:
	.string "MOTHER: Oh - goodness, a trainer.\p"
	.string "Right in my living room.\p"
	.string "Don't mind the mess.\p"
	.string "My daughter's upstairs in her\n"
	.string "room. She pretends to be a\l"
	.string "trainer all day - paper POKEBALLS,\l"
	.string "drawn-on badges.\p"
	.string "Fair warning. She'll talk your\n"
	.string "ear off if you go up.\p"
	.string "Half an hour max, please.\n"
	.string "Dinner's at six.$"
