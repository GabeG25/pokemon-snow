DawnflakeTown_PlayersHouse_1F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Mom interact — warm, worried, heals post-rival
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_PlayersHouse_1F_EventScript_MomHealIntro
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_PlayersHouse_1F_EventScript_MomPreRival
	msgbox DawnflakeTown_PlayersHouse_1F_Text_MomMorning, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_PlayersHouse_1F_EventScript_MomPreRival::
	msgbox DawnflakeTown_PlayersHouse_1F_Text_MomAfterStarter, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_PlayersHouse_1F_EventScript_MomHealIntro::
	msgbox DawnflakeTown_PlayersHouse_1F_Text_MomHealOffer, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	incrementgamestat GAME_STAT_RESTED_AT_HOME
	msgbox DawnflakeTown_PlayersHouse_1F_Text_MomHealAfter, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Bookshelf
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_1F_EventScript_Bookshelf::
	msgbox DawnflakeTown_PlayersHouse_1F_Text_Bookshelf, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_1F_Text_MomMorning:
	.string "MOM: Welcome home, sweetheart!\p"
	.string "How do you like the new place?\p"
	.string "Professor EVERGREEN called down\n"
	.string "from the lab twice already.\p"
	.string "He's a patient man. Don't make\n"
	.string "him be patient a third time.$"

DawnflakeTown_PlayersHouse_1F_Text_MomAfterStarter:
	.string "MOM: Oh - you've got one!\p"
	.string "Let me see... yes. Good.\p"
	.string "That's a brave little thing.\n"
	.string "It'll need you to be brave too.\p"
	.string "Be kind to Asher, {PLAYER}.\n"
	.string "Even when he isn't.$"

DawnflakeTown_PlayersHouse_1F_Text_MomHealOffer:
	.string "MOM: Let me look at you.\p"
	.string "Cold out there already, isn't it.\p"
	.string "Here - sit for a minute. I'll\n"
	.string "get your team back on their feet.$"

DawnflakeTown_PlayersHouse_1F_Text_MomHealAfter:
	.string "MOM: There. Good as new.\p"
	.string "The region's been strange lately,\n"
	.string "{PLAYER}. The winter came early,\l"
	.string "and it came wrong.\p"
	.string "Promise me you'll come home\n"
	.string "if you ever need to.$"

DawnflakeTown_PlayersHouse_1F_Text_Bookshelf:
	.string "A shelf of well-worn books.\p"
	.string "'A Field Guide to Boralyss.'\n"
	.string "'Weather and the Wild Heart.'\p"
	.string "The second one has a bookmark\n"
	.string "deep in a chapter titled\l"
	.string "'When Winter Won't Leave.'$"
