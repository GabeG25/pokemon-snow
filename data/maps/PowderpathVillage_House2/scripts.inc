PowderpathVillage_House2_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Shopkeep — middle-aged man sitting at his kitchen table,
@ morning tea, quiet observations about travelers.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House2_EventScript_Shopkeep::
	lock
	faceplayer
	msgbox PowderpathVillage_House2_Text_Shopkeep, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House2_Text_Shopkeep:
	.string "MAN: Oh - hello. Come on in.\n"
	.string "Mind the boots.\p"
	.string "Just sitting with my tea. Watching\n"
	.string "the trail.\p"
	.string "I used to run a little shop out\n"
	.string "of the front window. Cold-brewed\l"
	.string "cider, mostly.\p"
	.string "Kids from DAWNFLAKE used to stop\n"
	.string "in on their way up.\p"
	.string "Haven't had a batch go in years.\n"
	.string "Trainers don't come through like\l"
	.string "they used to.\p"
	.string "You're the first this month.\p"
	.string "Take that as a compliment. Or a\n"
	.string "warning. Your choice.$"
