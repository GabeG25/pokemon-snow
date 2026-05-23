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
	.string "GRANDMA: Oh, hello {PLAYER},\n"
	.string "sorry I didn't know you were\l"
	.string "stopping by.\p"
	.string "Come closer, dear. Let an old\n"
	.string "woman look at you.\p"
	.string "...Yes. You've got kind eyes,\n"
	.string "{PLAYER}.\l"
	.string "Asher used to have kind eyes too.\p"
	.string "He's out somewhere. He's always\n"
	.string "out somewhere, these days.\p"
	.string "Be patient with him, won't you?\n"
	.string "The boy is carrying more than\l"
	.string "any child should.$"

DawnflakeTown_AshersHouse_Text_GrandmaPostRival:
	.string "GRANDMA: Oh, hello {PLAYER}!\p"
	.string "I saw Asher come through just\n"
	.string "a minute ago to gather the\l"
	.string "rest of his things.\p"
	.string "The kid has finally left the\n"
	.string "nest.\p"
	.string "I know it's kind of selfish,\n"
	.string "but I am sad to see him go.\p"
	.string "Once he leaves, I will be\n"
	.string "all alone.\p"
	.string "But that is just the way\n"
	.string "things are sometimes.\p"
	.string "Time stops for no-one and\n"
	.string "nothing lasts forever,\p"
	.string "so I am just happy to have\n"
	.string "spent the time I did with him\l"
	.string "when he was still a sweet\l"
	.string "little boy.\p"
	.string "Safe travels, {PLAYER}.$"

DawnflakeTown_AshersHouse_Text_Photo:
	.string "A framed photograph.\p"
	.string "It's 3 people standing in\n"
	.string "front of a snowy hill.\p"
	.string "The boy in the middle looks\n"
	.string "happy. However, the two adults\l"
	.string "beside him seem as if they\l"
	.string "are faking a smile.$"
