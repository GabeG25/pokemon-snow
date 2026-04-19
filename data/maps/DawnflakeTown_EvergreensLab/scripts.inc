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
	@ FRLG-style gate: all three rivals must be present before the
	@ ceremony fires. Player has to go fetch Autumn from her bedroom
	@ first; she clearflag's FLAG_SNOW_HIDE_AUTUMN_LAB on her way out.
	goto_if_unset FLAG_SNOW_TOLD_AUTUMN, DawnflakeTown_EvergreensLab_EventScript_EvergreenWaitForAutumn
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenIntro, MSGBOX_DEFAULT
	@ HGSS-style direct pick — no Birch satchel UI, no grass background.
	@ Two-stage: first the multichoice menu, then a per-starter blurb +
	@ confirm so the player has more detail before committing. After
	@ they commit, givemon + nickname prompt before returning to the
	@ main ceremony flow.
	msgbox DawnflakeTown_EvergreensLab_Text_StarterPrompt, MSGBOX_DEFAULT
	goto DawnflakeTown_EvergreensLab_EventScript_StarterMenu

DawnflakeTown_EvergreensLab_EventScript_StarterMenu::
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, DawnflakeTown_EvergreensLab_Text_StarterTreecko, DawnflakeTown_EvergreensLab_Text_StarterTorchic, DawnflakeTown_EvergreensLab_Text_StarterMudkip
	copyvar VAR_STARTER_MON, VAR_RESULT
	compare VAR_STARTER_MON, 0
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_PreviewTreecko
	compare VAR_STARTER_MON, 1
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_PreviewTorchic
	compare VAR_STARTER_MON, 2
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_PreviewMudkip
	end

DawnflakeTown_EvergreensLab_EventScript_PreviewTreecko::
	msgbox DawnflakeTown_EvergreensLab_Text_TreeckoBlurb, MSGBOX_DEFAULT
	msgbox DawnflakeTown_EvergreensLab_Text_StarterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterMenu
	goto DawnflakeTown_EvergreensLab_EventScript_GiveTreecko

DawnflakeTown_EvergreensLab_EventScript_PreviewTorchic::
	msgbox DawnflakeTown_EvergreensLab_Text_TorchicBlurb, MSGBOX_DEFAULT
	msgbox DawnflakeTown_EvergreensLab_Text_StarterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterMenu
	goto DawnflakeTown_EvergreensLab_EventScript_GiveTorchic

DawnflakeTown_EvergreensLab_EventScript_PreviewMudkip::
	msgbox DawnflakeTown_EvergreensLab_Text_MudkipBlurb, MSGBOX_DEFAULT
	msgbox DawnflakeTown_EvergreensLab_Text_StarterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterMenu
	goto DawnflakeTown_EvergreensLab_EventScript_GiveMudkip

DawnflakeTown_EvergreensLab_EventScript_GiveTreecko::
	bufferspeciesname STR_VAR_1, SPECIES_TREECKO
	givemon SPECIES_TREECKO, 5
	@ Set met location to "Fateful Encounter" so the starter's
	@ summary doesn't read DAWNFLAKE TOWN — these are gift POKEMON
	@ from a warmer region, narratively outside the regional dex.
	setmonmetlocation 0, 0xFF        @ METLOC_FATEFUL_ENCOUNTER
	goto DawnflakeTown_EvergreensLab_EventScript_NicknameAndContinue

DawnflakeTown_EvergreensLab_EventScript_GiveTorchic::
	bufferspeciesname STR_VAR_1, SPECIES_TORCHIC
	givemon SPECIES_TORCHIC, 5
	setmonmetlocation 0, 0xFF        @ METLOC_FATEFUL_ENCOUNTER
	goto DawnflakeTown_EvergreensLab_EventScript_NicknameAndContinue

DawnflakeTown_EvergreensLab_EventScript_GiveMudkip::
	bufferspeciesname STR_VAR_1, SPECIES_MUDKIP
	givemon SPECIES_MUDKIP, 5
	setmonmetlocation 0, 0xFF        @ METLOC_FATEFUL_ENCOUNTER
	goto DawnflakeTown_EvergreensLab_EventScript_NicknameAndContinue

DawnflakeTown_EvergreensLab_EventScript_NicknameAndContinue::
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterAccepted
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto DawnflakeTown_EvergreensLab_EventScript_StarterAccepted

DawnflakeTown_EvergreensLab_EventScript_StarterAccepted::
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter, MSGBOX_DEFAULT
	@ Give Pokedex
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_SNOW_GOT_POKEDEX_DAWNFLAKE
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenPokedex, MSGBOX_DEFAULT
	@ Narrate Asher and Autumn making their picks (off-screen) so all
	@ three trainers leave the lab with a starter, FRLG-style.
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenAllPicked, MSGBOX_DEFAULT
	@ Asher steps around the table to (6, 7) — directly south of the
	@ player at (6, 5) with the research table at (6, 6) between them.
	@ Faces up. Player turns south to face him for the F1 battle.
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherApproach
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AsherChallenge, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq DawnflakeTown_EvergreensLab_EventScript_AsherVariantC
	end

@ Each variant uses trainerbattle_earlyrival with HEAL_AFTER so the
@ player isn't whited out on loss — Asher brags, leaves, story
@ continues regardless. Win/loss branches in EventScript_AsherAfterBattle.
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
	@ Reached only on player win (loss = whiteout via trainerbattle_no_intro;
	@ EventScript_EvergreenAfterStarter handles the post-whiteout recovery flow
	@ where Asher acknowledges his win and walks out with no rematch — FRLG
	@ vanilla rival pattern).
	setflag FLAG_SNOW_BEAT_F1_ASHER
	msgbox DawnflakeTown_EvergreensLab_Text_AsherPostBattle, MSGBOX_DEFAULT
	closemessage
	@ Asher walks out the (6, 12) door with a proper open/close anim.
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherToDoor
	waitmovement 0
	opendoor 6, 12
	waitdooranim
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor
	waitmovement 0
	removeobject 3
	setflag FLAG_SNOW_HIDE_ASHER_LAB
	closedoor 6, 12
	waitdooranim
	@ Player still faces south from the Asher fight — turn them back
	@ around so they're "listening" to Autumn and Evergreen.
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	@ Autumn pitches from her position (already at (5, 4) the whole
	@ ceremony) and walks out the west door (warp tile 6, 12).
	applymovement 4, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	closemessage
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnToDoor
	waitmovement 0
	opendoor 6, 12
	waitdooranim
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor
	waitmovement 0
	removeobject 4
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	closedoor 6, 12
	waitdooranim
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
	@ Recovery: player got starter but full cutscene didn't finish.
	@ Silently fix Pokedex state (setflag is idempotent).
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_SNOW_GOT_POKEDEX_DAWNFLAKE
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EvergreensLab_EventScript_ResumePostAsher
	@ Player whited out from F1 — story progresses anyway.
	@ Asher gloats from his standing position, walks out the door,
	@ then Autumn's pitch and Evergreen's TM proceed normally. No
	@ rematch — this is the "lost the rival fight in vanilla Pokemon"
	@ pattern: lose, mom heals, walk back, story moves on.
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenReady, MSGBOX_DEFAULT
	msgbox DawnflakeTown_EvergreensLab_Text_AsherPostBattleLoss, MSGBOX_DEFAULT
	closemessage
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_AsherToDoorFromStart
	waitmovement 0
	opendoor 6, 12
	waitdooranim
	applymovement 3, DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor
	waitmovement 0
	removeobject 3
	setflag FLAG_SNOW_HIDE_ASHER_LAB
	closedoor 6, 12
	waitdooranim
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement 4, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	closemessage
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnToDoor
	waitmovement 0
	opendoor 6, 12
	waitdooranim
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor
	waitmovement 0
	removeobject 4
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	closedoor 6, 12
	waitdooranim
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_WORK_UP
	setflag FLAG_SNOW_GOT_TM01_WORK_UP
	setflag FLAG_SNOW_STARTER_CUTSCENE_DONE
	setflag FLAG_SNOW_HIDE_STARTER_GATE
	clearflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	release
	end

DawnflakeTown_EvergreensLab_EventScript_ResumePostAsher::
	@ Beat Asher but Autumn pitch / TM01 portion didn't complete.
	@ Autumn is still standing at (5, 4) (FLAG_SNOW_HIDE_AUTUMN_LAB
	@ was cleared by her bedroom visit and never re-set on this path).
	applymovement 4, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnPitch, MSGBOX_DEFAULT
	closemessage
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_AutumnToDoor
	waitmovement 0
	opendoor 6, 12
	waitdooranim
	applymovement 4, DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor
	waitmovement 0
	removeobject 4
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	closedoor 6, 12
	waitdooranim
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

DawnflakeTown_EvergreensLab_EventScript_EvergreenWaitForAutumn::
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenWaitForAutumn, MSGBOX_DEFAULT
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
@ Autumn in-lab — only accessible during pre-ceremony window
@ (after she runs from her bedroom, before player triggers the
@ Evergreen ceremony). Different text from her post-Asher pitch.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_AutumnLab::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_AutumnLabPreCeremony, MSGBOX_DEFAULT
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

@ Asher walks south 3 then west 1 from (7, 4) -> (6, 7), facing UP at
@ the player who's at (6, 5). The research table at (6, 6) sits between
@ them — face-off across the desk, FRLG Oak-lab style. Scripted
@ applymovement bypasses the table's collision flag.
DawnflakeTown_EvergreensLab_Movement_AsherApproach:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

@ After F1 (player won), Asher walks from (6, 7) down to (6, 11) —
@ one tile north of the door warp at (6, 12). NpcEnterDoor finishes.
DawnflakeTown_EvergreensLab_Movement_AsherToDoor:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Loss-recovery path: player whited out and walked back, so Asher
@ never approached. He walks from his original (7, 4) tile straight
@ down + west to (6, 11), bypassing the table tiles (scripted
@ movements bypass collision flags).
DawnflakeTown_EvergreensLab_Movement_AsherToDoorFromStart:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

@ Autumn walks from (5, 4) south to (5, 11), then east to (6, 11),
@ same approach to the (6, 12) door (Asher's already been removeobject'd
@ by the time she walks through, so the path is clear).
DawnflakeTown_EvergreensLab_Movement_AutumnToDoor:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

@ Shared final step: NPC walks south once into the warp tile, then
@ removeobject'd while on it for clean door-exit visual.
DawnflakeTown_EvergreensLab_Movement_NpcEnterDoor:
	walk_down
	step_end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_Text_EvergreenIntro:
	.string "PROF. EVERGREEN: There you are.\p"
	.string "I was about to send AUTUMN out\n"
	.string "to find you, but she beat me\l"
	.string "to it. She usually does.\p"
	.string "We have three POKEMON here,\n"
	.string "sent up from a region that\l"
	.string "doesn't know cold the way ours\l"
	.string "does.\p"
	.string "Pick the one that holds your\n"
	.string "eye - that's yours.$"

DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Good. I think\n"
	.string "that one fits you well.\p"
	.string "Take a moment together. Names\n"
	.string "matter to POKEMON, even when\l"
	.string "they pretend otherwise.$"

DawnflakeTown_EvergreensLab_Text_EvergreenPokedex:
	.string "PROF. EVERGREEN: And here -\n"
	.string "a POKEDEX.\p"
	.string "Every POKEMON you meet leaves\n"
	.string "a mark in there. The region's\l"
	.string "catalogue grows alongside\l"
	.string "you.\p"
	.string "Consider it a small favor for\n"
	.string "me, for the road ahead.$"

DawnflakeTown_EvergreensLab_Text_StarterPrompt:
	.string "PROF. EVERGREEN: Take your time\n"
	.string "and look at each of them.\p"
	.string "Pick the one that holds your\n"
	.string "eye.$"

DawnflakeTown_EvergreensLab_Text_StarterTreecko:
	.string "TREECKO$"

DawnflakeTown_EvergreensLab_Text_StarterTorchic:
	.string "TORCHIC$"

DawnflakeTown_EvergreensLab_Text_StarterMudkip:
	.string "MUDKIP$"

DawnflakeTown_EvergreensLab_Text_TreeckoBlurb:
	.string "PROF. EVERGREEN: This is\n"
	.string "TREECKO, the WOOD GECKO\l"
	.string "POKEMON - a GRASS type.\p"
	.string "It tends to watch a thing for\n"
	.string "a long while before it touches\l"
	.string "anything new.\p"
	.string "Patient in battle and patient\n"
	.string "out of it - a useful tempera-\l"
	.string "ment in a region where the\l"
	.string "wind doesn't quit.\p"
	.string "Slow to forget the people who\n"
	.string "lose its trust, though.$"

DawnflakeTown_EvergreensLab_Text_TorchicBlurb:
	.string "PROF. EVERGREEN: This one is\n"
	.string "TORCHIC, the CHICK POKEMON.\p"
	.string "A FIRE type, and warmer than\n"
	.string "any thermometer I own. Our\l"
	.string "winter doesn't bother it in\l"
	.string "the slightest.\p"
	.string "It decides on its partner\n"
	.string "quickly and keeps that decision\l"
	.string "for life.\p"
	.string "Hard to lose, once it's chosen\n"
	.string "you.$"

DawnflakeTown_EvergreensLab_Text_MudkipBlurb:
	.string "PROF. EVERGREEN: And this is\n"
	.string "MUDKIP, the MUD FISH POKEMON,\l"
	.string "a WATER type.\p"
	.string "It reads rivers through the\n"
	.string "fin on its head, and trusts\l"
	.string "that fin more than its own\l"
	.string "eyes.\p"
	.string "Steady and stubborn. Once\n"
	.string "those feet plant themselves\l"
	.string "you'll need a crowbar to move\l"
	.string "it.\p"
	.string "A grounding presence, in a\n"
	.string "country where the snow takes\l"
	.string "its time melting.$"

DawnflakeTown_EvergreensLab_Text_StarterConfirm:
	.string "PROF. EVERGREEN: That one?\n"
	.string "You're sure?$"

DawnflakeTown_EvergreensLab_Text_EvergreenAllPicked:
	.string "PROF. EVERGREEN: Good - all\n"
	.string "three of you have your\l"
	.string "POKEMON now.\p"
	.string "Take a minute together before\n"
	.string "you head out. The road from\l"
	.string "here gets long.$"

DawnflakeTown_EvergreensLab_Text_AutumnLabPreCeremony:
	.string "AUTUMN: {PLAYER}!! Finally!\p"
	.string "EVERGREEN's been waiting forever\n"
	.string "but he'll never tell you that.\p"
	.string "Go go go - I want to see\n"
	.string "which one you pick!$"

DawnflakeTown_EvergreensLab_Text_AsherChallenge:
	.string "ASHER: Done?\p"
	.string "Mine has the type advantage.\n"
	.string "I checked.\p"
	.string "Let's go.$"

DawnflakeTown_EvergreensLab_Text_AsherDefeat:
	.string "ASHER: ...$"

DawnflakeTown_EvergreensLab_Text_AsherPostBattle:
	.string "ASHER: ...\p"
	.string "You played that well.\p"
	.string "Won't last.$"

DawnflakeTown_EvergreensLab_Text_AsherPostBattleLoss:
	.string "ASHER: Hmph.\p"
	.string "Told you. Chart math.\p"
	.string "EVERGREEN. I'm out.$"

DawnflakeTown_EvergreensLab_Text_AsherVictoryInBattle:
	.string "ASHER: Hm.$"

DawnflakeTown_EvergreensLab_Text_AsherBrush:
	.string "ASHER: I'm busy.$"

DawnflakeTown_EvergreensLab_Text_AutumnPitch:
	.string "AUTUMN: Oh my GOSH that was\n"
	.string "incredible!\p"
	.string "PROF, you're not getting out\n"
	.string "of the field-data plan! You\l"
	.string "said yes already, no take-backs.\p"
	.string "{PLAYER} - meet me on ROUTE 1!\n"
	.string "Don't make me wait!\p"
	.string "And bring your POKEDEX, we've\n"
	.string "got pages to fill!$"

DawnflakeTown_EvergreensLab_Text_EvergreenWaitForAutumn:
	.string "PROF. EVERGREEN: Slow down a\n"
	.string "minute - AUTUMN's not here yet.\p"
	.string "She's at home wearing a hole\n"
	.string "in the floorboards, no doubt.\l"
	.string "I saw her run past my window\l"
	.string "twice this morning alone.\p"
	.string "Pop by and tell her I won't\n"
	.string "start without her.$"

DawnflakeTown_EvergreensLab_Text_EvergreenTM:
	.string "PROF. EVERGREEN: One more thing\n"
	.string "before you go - take TM01.\p"
	.string "WORK UP. A training move that\n"
	.string "builds physical strength.\p"
	.string "The ROUTE 1 trail isn't kind\n"
	.string "to soft beginnings, so put it\l"
	.string "to use early.\p"
	.string "AUTUMN's waiting on you. She\n"
	.string "wasn't made for standing still,\l"
	.string "so don't keep her.$"

DawnflakeTown_EvergreensLab_Text_EvergreenReady:
	.string "PROF. EVERGREEN: Oh, back\n"
	.string "already. Where were we?\p"
	.string "Right - ASHER had a point to\n"
	.string "make, and I imagine he still\l"
	.string "wants to make it.$"

DawnflakeTown_EvergreensLab_Text_EvergreenHeadSouth:
	.string "PROF. EVERGREEN: ROUTE 1 is\n"
	.string "south of town - the trail\l"
	.string "begins there.\p"
	.string "Keep moving. The cold won't\n"
	.string "stop just because you do.\p"
	.string "Take care of each other out\n"
	.string "there. Both of you.$"

DawnflakeTown_EvergreensLab_Text_Aide:
	.string "AIDE: PROF. EVERGREEN sleeps in\n"
	.string "the lab now. I'm not\l"
	.string "exaggerating either.\p"
	.string "There's a cot behind the file\n"
	.string "cabinet and a kettle that's\l"
	.string "always warm.\p"
	.string "He hasn't gone home since the\n"
	.string "weather went wrong.\p"
	.string "He won't say it out loud, but\n"
	.string "I know he's worried about\l"
	.string "what's causing this.\p"
	.string "And what'll happen if it\n"
	.string "doesn't stop.$"
