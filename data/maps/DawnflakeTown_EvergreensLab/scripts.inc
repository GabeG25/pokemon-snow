DawnflakeTown_EvergreensLab_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Prof. Evergreen — full starter cutscene:
@ intro → choose starter → Pokedex → Asher F1 in-lab battle →
@ Asher despawn → Autumn pitch (revealed) → Autumn runs out →
@ Evergreen gives TM01 Work Up and sends player to Route 1.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_Evergreen::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_STARTER_CUTSCENE_DONE, DawnflakeTown_EvergreensLab_EventScript_EvergreenPost
	goto_if_set FLAG_SYS_POKEMON_GET, DawnflakeTown_EvergreensLab_EventScript_EvergreenAfterStarter
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenIntro, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter, MSGBOX_DEFAULT
	@ Give Pokedex
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_SNOW_GOT_POKEDEX_DAWNFLAKE
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenPokedex, MSGBOX_DEFAULT
	@ Reveal Asher and trigger F1 battle inside the lab
	clearflag FLAG_SNOW_HIDE_ASHER_LAB
	addobject 3
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherApproach
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AsherChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantC
	end

DawnflakeTown_EvergreensLab_EventScript_AsherVariantA::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_A, DawnflakeTown_EvergreensLab_Text_AsherDefeat
	goto DawnflakeTown_EvergreensLab_EventScript_AsherAfterBattle

DawnflakeTown_EvergreensLab_EventScript_AsherVariantB::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_B, DawnflakeTown_EvergreensLab_Text_AsherDefeat
	goto DawnflakeTown_EvergreensLab_EventScript_AsherAfterBattle

DawnflakeTown_EvergreensLab_EventScript_AsherVariantC::
	trainerbattle_no_intro TRAINER_SNOW_F1_ASHER_C, DawnflakeTown_EvergreensLab_Text_AsherDefeat
	goto DawnflakeTown_EvergreensLab_EventScript_AsherAfterBattle

DawnflakeTown_EvergreensLab_EventScript_AsherAfterBattle::
	setflag FLAG_SNOW_BEAT_F1_ASHER
	msgbox DawnflakeTown_EvergreensLab_Text_AsherPostBattle, MSGBOX_DEFAULT
	closemessage
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherLeave
	waitmovement 0
	setflag FLAG_SNOW_HIDE_ASHER_LAB
	removeobject 3
	@ Autumn pitch
	clearflag FLAG_SNOW_HIDE_AUTUMN_LAB
	addobject 4
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnApproach
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	closemessage
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnLeave
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	removeobject 4
	@ Evergreen final: TM01 Work Up, clear starter gate
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_WORK_UP
	setflag FLAG_SNOW_GOT_TM01_WORK_UP
	setflag FLAG_SNOW_STARTER_CUTSCENE_DONE
	setflag FLAG_SNOW_HIDE_STARTER_GATE
	clearflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	release
	end

DawnflakeTown_EvergreensLab_EventScript_EvergreenAfterStarter::
	@ Recovery: player got starter but full cutscene didn't finish
	@ (crash, power loss, or lost to Asher and whited out).
	@ Silently fix Pokedex state (setflag is idempotent).
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_SNOW_GOT_POKEDEX_DAWNFLAKE
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EvergreensLab_EventScript_ResumePostAsher
	@ Asher not yet beaten — resume from battle
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenReady, MSGBOX_DEFAULT
	clearflag FLAG_SNOW_HIDE_ASHER_LAB
	addobject 3
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherApproach
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AsherChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantC
	end

DawnflakeTown_EvergreensLab_EventScript_ResumePostAsher::
	@ Beat Asher but Autumn pitch / TM01 portion didn't complete.
	clearflag FLAG_SNOW_HIDE_AUTUMN_LAB
	addobject 4
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnApproach
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	closemessage
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnLeave
	waitmovement 0
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	removeobject 4
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_WORK_UP
	setflag FLAG_SNOW_GOT_TM01_WORK_UP
	setflag FLAG_SNOW_STARTER_CUTSCENE_DONE
	setflag FLAG_SNOW_HIDE_STARTER_GATE
	clearflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	release
	end

DawnflakeTown_EvergreensLab_EventScript_EvergreenPost::
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenHeadSouth, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Asher in-lab — only accessible during cutscene
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_AsherLab::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_AsherBrush, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Autumn in-lab
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_AutumnLab::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Aide
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_Aide::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_Aide, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Movements
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_Movement_AsherApproach:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_down
	step_end

DawnflakeTown_EvergreensLab_Movement_AsherLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

DawnflakeTown_EvergreensLab_Movement_AutumnApproach:
	walk_down
	walk_down
	walk_in_place_faster_down
	step_end

DawnflakeTown_EvergreensLab_Movement_AutumnLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_Text_EvergreenIntro:
	.string "PROF. EVERGREEN: {PLAYER}!\n"
	.string "You're finally here.\p"
	.string "Welcome to my lab. I've been\n"
	.string "studying how POKEMON adapt to\l"
	.string "BORALYSS's endless winter.\p"
	.string "But today is about you.\p"
	.string "Three POKEMON were shipped to me\n"
	.string "from a warmer region. They've\l"
	.string "never felt cold like ours.\p"
	.string "Go on - take a look.$"

DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Good choice.\p"
	.string "That one suits you.$"

DawnflakeTown_EvergreensLab_Text_EvergreenPokedex:
	.string "PROF. EVERGREEN: And here - my\n"
	.string "POKEDEX.\p"
	.string "Every POKEMON you meet, it will\n"
	.string "remember for you. Consider it\l"
	.string "a research favor.$"

DawnflakeTown_EvergreensLab_Text_AsherChallenge:
	.string "ASHER: Oh. You.\p"
	.string "EVERGREEN gave you one of the\n"
	.string "outsider POKEMON. Figures.\p"
	.string "I don't do friendship speeches.\n"
	.string "You're not my friend.\p"
	.string "My starter beats yours. I made\n"
	.string "sure of it.\p"
	.string "Let's go.$"

DawnflakeTown_EvergreensLab_Text_AsherDefeat:
	.string "ASHER: ...tch.$"

DawnflakeTown_EvergreensLab_Text_AsherPostBattle:
	.string "ASHER: ...\p"
	.string "Whatever. Beginner's luck.\p"
	.string "Don't get used to winning,\n"
	.string "{PLAYER}.$"

DawnflakeTown_EvergreensLab_Text_AsherBrush:
	.string "ASHER: Don't talk to me.$"

DawnflakeTown_EvergreensLab_Text_AutumnPitch:
	.string "AUTUMN: {PLAYER}! Oh my gosh,\n"
	.string "you got one!\p"
	.string "PROF - is the offer still good?\n"
	.string "Can I come along for the field\l"
	.string "data?\p"
	.string "I have to go grab my gear - meet\n"
	.string "me on ROUTE 1!$"

DawnflakeTown_EvergreensLab_Text_EvergreenTM:
	.string "PROF. EVERGREEN: One more thing.\p"
	.string "Take this TM. WORK UP.\p"
	.string "A training move. Raises your\n"
	.string "POKEMON's physical power.\p"
	.string "It'll help you both grow.\n"
	.string "Now go - AUTUMN is waiting.$"

DawnflakeTown_EvergreensLab_Text_EvergreenReady:
	.string "PROF. EVERGREEN: Good, you're\n"
	.string "back.\p"
	.string "Let's pick up where we left off.$"

DawnflakeTown_EvergreensLab_Text_EvergreenHeadSouth:
	.string "PROF. EVERGREEN: ROUTE 1 is south\n"
	.string "of town. That's where your journey\l"
	.string "really begins.\p"
	.string "Take care of yourself out there.$"

DawnflakeTown_EvergreensLab_Text_Aide:
	.string "AIDE: Professor EVERGREEN has\n"
	.string "been working nonstop lately.\p"
	.string "Ever since the weather changed,\n"
	.string "he's been obsessed with\l"
	.string "documenting the adaptations.$"
