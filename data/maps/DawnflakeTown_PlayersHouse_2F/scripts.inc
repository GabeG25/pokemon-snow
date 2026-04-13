DawnflakeTown_PlayersHouse_2F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ PC — vanilla player PC flow
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_EventScript_PC::
	lockall
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_PlayersHouse_2F_EventScript_PCLive
	msgbox DawnflakeTown_PlayersHouse_2F_Text_PCOff, MSGBOX_SIGN
	releaseall
	end

DawnflakeTown_PlayersHouse_2F_EventScript_PCLive::
	setvar VAR_0x800B, 0
	playse SE_PC_LOGIN
	msgbox DawnflakeTown_PlayersHouse_2F_Text_BootedUp, MSGBOX_DEFAULT
	special PlayerPC
	waitstate
	releaseall
	end

DawnflakeTown_PlayersHouse_2F_EventScript_WallClock::
	msgbox DawnflakeTown_PlayersHouse_2F_Text_WallClock, MSGBOX_SIGN
	end

DawnflakeTown_PlayersHouse_2F_EventScript_Bed::
	msgbox DawnflakeTown_PlayersHouse_2F_Text_Bed, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_2F_Text_PCOff:
	.string "A small desktop PC.\p"
	.string "The screen is dark. There isn't\n"
	.string "much to store in it yet.$"

DawnflakeTown_PlayersHouse_2F_Text_BootedUp:
	.string "{PLAYER} booted up the PC.$"

DawnflakeTown_PlayersHouse_2F_Text_WallClock:
	.string "A wooden wall clock.\p"
	.string "Quarter past eight.\n"
	.string "The morning's already moving\l"
	.string "without you.$"

DawnflakeTown_PlayersHouse_2F_Text_Bed:
	.string "Your bed. Still warm.\p"
	.string "The blanket smells like\n"
	.string "pine smoke and Mom's cooking.$"
