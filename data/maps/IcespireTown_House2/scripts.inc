IcespireTown_House2_MapScripts::
	.byte 0

IcespireTown_House2_EventScript_Father::
	lock
	faceplayer
	msgbox IcespireTown_House2_Text_Father, MSGBOX_DEFAULT
	release
	end

IcespireTown_House2_EventScript_Son::
	lock
	faceplayer
	msgbox IcespireTown_House2_Text_Son, MSGBOX_DEFAULT
	release
	end

IcespireTown_House2_Text_Father:
	.string "FATHER: Welcome in, trainer.\p"
	.string "My boy's been copying his\n"
	.string "school chants around the house\l"
	.string "all week. Proud as a CUBCHOO.\p"
	.string "His teacher gave him a pin.\n"
	.string "Little silver VEIL symbol. He\l"
	.string "won't take it off.\p"
	.string "I used to work the rail line\n"
	.string "down to PINEGROVE. When the\l"
	.string "snow came in, the rail closed.\l"
	.string "I worried at first.\p"
	.string "Then the DIRECTOR'S people set\n"
	.string "up a relief office. I get a\l"
	.string "check every month now. For\l"
	.string "doing NOTHING.\p"
	.string "Tell me that's not kindness.$"

IcespireTown_House2_Text_Son:
	.string "BOY: Hi hi hi! Are you a\n"
	.string "trainer?\p"
	.string "I'm going to be a trainer when\n"
	.string "I'm nine. That's what MOM says.\p"
	.string "My favorite is DIRECTOR TYRELL.\n"
	.string "My teacher says he's not a\l"
	.string "trainer but he's SPECIAL.\p"
	.string "We sing about him every morning!\n"
	.string "The snow is kind, the snow is\l"
	.string "CLEAN!\p"
	.string "The DIRECTOR LOVES us, the\n"
	.string "DIRECTOR KEEPS us!\p"
	.string "Do you know the rest? I can\n"
	.string "teach you!$"
