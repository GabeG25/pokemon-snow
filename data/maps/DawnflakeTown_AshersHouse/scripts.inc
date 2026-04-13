DawnflakeTown_AshersHouse_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Asher's Grandma — the elder who remembers, the guilt vector
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AshersHouse_EventScript_Grandma::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_AshersHouse_EventScript_GrandmaPostRival
	msgbox DawnflakeTown_AshersHouse_Text_Grandma, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_AshersHouse_EventScript_GrandmaPostRival::
	msgbox DawnflakeTown_AshersHouse_Text_GrandmaPostRival, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Framed photo — family from before
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AshersHouse_EventScript_Photo::
	msgbox DawnflakeTown_AshersHouse_Text_Photo, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_AshersHouse_Text_Grandma:
	.string "GRANDMA: Oh. You must be the\n"
	.string "child Evergreen's waiting on.\p"
	.string "Come closer, dear. Let an old\n"
	.string "woman look at you.\p"
	.string "...Yes. You've got kind eyes.\n"
	.string "Asher used to have kind eyes too.\p"
	.string "He's out somewhere. He's always\n"
	.string "out somewhere, these days.\p"
	.string "Be patient with him, won't you?\n"
	.string "The boy is carrying more than\l"
	.string "any child should.$"

DawnflakeTown_AshersHouse_Text_GrandmaPostRival:
	.string "GRANDMA: He battled you?\p"
	.string "Good. He needs someone to push\n"
	.string "back against.\p"
	.string "...\p"
	.string "When the men in grey came asking\n"
	.string "about the mountain, his parents\l"
	.string "told them everything.\p"
	.string "They said it would keep us safe.\n"
	.string "They were frightened, {PLAYER}.\l"
	.string "People do ugly things when\l"
	.string "they're frightened.\p"
	.string "Asher saw their faces that day.\n"
	.string "He hasn't forgiven them.\p"
	.string "I don't think he's forgiven\n"
	.string "himself either, for being too\l"
	.string "small to stop them.$"

DawnflakeTown_AshersHouse_Text_Photo:
	.string "A framed family photo.\p"
	.string "Five people smiling in front\n"
	.string "of a mountain that isn't\l"
	.string "frozen yet.\p"
	.string "The boy in the middle looks\n"
	.string "nothing like Asher does now.$"
