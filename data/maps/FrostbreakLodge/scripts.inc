FrostbreakLodge_MapScripts::
	.byte 0

FrostbreakLodge_EventScript_ShellBellNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_SHELL_BELL, FrostbreakLodge_EventScript_ShellBellDone
	msgbox FrostbreakLodge_Text_ShellBellIntro, MSGBOX_DEFAULT
	giveitem ITEM_SHELL_BELL, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_SHELL_BELL
	msgbox FrostbreakLodge_Text_ShellBellGiven, MSGBOX_DEFAULT
	release
	end

FrostbreakLodge_EventScript_ShellBellDone::
	msgbox FrostbreakLodge_Text_ShellBellPost, MSGBOX_DEFAULT
	release
	end

FrostbreakLodge_Text_ShellBellIntro:
	.string "MOUNTAINEER: I found this on the\n"
	.string "peak last winter.\p"
	.string "Every time my POKEMON lands a hit,\n"
	.string "this bell chimes and they perk\l"
	.string "right up.\p"
	.string "I've got my own recovery methods\n"
	.string "up here - you take it for the\l"
	.string "road ahead.$"

FrostbreakLodge_Text_ShellBellGiven:
	.string "{PLAYER} received the SHELL BELL!$"

FrostbreakLodge_Text_ShellBellPost:
	.string "MOUNTAINEER: Stay warm out there.$"
