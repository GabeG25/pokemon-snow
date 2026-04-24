PowderpathVillage_House3_2F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Daughter — little girl in her upstairs bedroom, dreams of
@ being a trainer, shows off her paper badges.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_House3_2F_EventScript_Daughter::
	lock
	faceplayer
	msgbox PowderpathVillage_House3_2F_Text_Daughter, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House3_2F_Text_Daughter:
	.string "GIRL: Oh WOW!\p"
	.string "A REAL trainer! In MY room!\p"
	.string "I'm gonna be one too. When I'm\n"
	.string "ten. Mom said. It's like a\l"
	.string "PROMISE.\p"
	.string "Look, I already drew all my\n"
	.string "badges. There's eight. They're\l"
	.string "on the wall over there.\p"
	.string "See that green one? That's the\n"
	.string "GRASS one. I colored it extra\l"
	.string "green.\p"
	.string "And my POKEBALL is papier-mache,\n"
	.string "but it's MINE.\p"
	.string "I already know what I'm gonna\n"
	.string "name my first one.\p"
	.string "KASSIE.\p"
	.string "...\p"
	.string "Don't tell Mom. It's a secret.$"
