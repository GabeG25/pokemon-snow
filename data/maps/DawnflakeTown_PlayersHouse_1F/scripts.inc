DawnflakeTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DawnflakeTown_PlayersHouse_1F_OnFrame
	.byte 0

DawnflakeTown_PlayersHouse_1F_OnFrame:
	map_script_2 VAR_SNOW_INTRO_STATE, 1, DawnflakeTown_PlayersHouse_1F_EventScript_MomCutscene
	.2byte 0

@ ═══════════════════════════════════════════════════════════
@ Mom downstairs cutscene — auto-fires on first descent from
@ the bedroom.  VAR_SNOW_INTRO_STATE=1 after the wake-up; this
@ script advances it to 2 so the frame entry never re-matches.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_1F_EventScript_MomCutscene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement 1, DawnflakeTown_PlayersHouse_1F_Movement_MomFaceUp
	waitmovement 0
	msgbox DawnflakeTown_PlayersHouse_1F_Text_MomCutscene, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SNOW_INTRO_STATE, 2
	setflag FLAG_SNOW_INTRO_MOM_CUTSCENE_DONE
	releaseall
	end

DawnflakeTown_PlayersHouse_1F_Movement_MomFaceUp:
	walk_in_place_faster_up
	step_end

@ ═══════════════════════════════════════════════════════════
@ Mom interact — warm, worried, heals post-rival
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_MOM_RUNNING_SHOES_DONE, DawnflakeTown_PlayersHouse_1F_EventScript_MomHealIntro
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
	.string "MOM: Up and at 'em, sweetheart!\p"
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

DawnflakeTown_PlayersHouse_1F_Text_MomCutscene:
	.string "MOM: Oh! You're up!\p"
	.string "I heard you shuffling around\n"
	.string "upstairs. Sleep well?\p"
	.string "Professor EVERGREEN called\n"
	.string "down from the lab twice\l"
	.string "already.\p"
	.string "He's a patient man, honey.\n"
	.string "Don't make him be patient a\l"
	.string "third time.\p"
	.string "Head on over whenever you're\n"
	.string "ready.$"
