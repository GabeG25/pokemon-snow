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
	@ main ceremony flow. The KARANAGA introduction in EvergreenIntro
	@ already names all three species, so StarterPrompt is skipped.
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
	@ Small delay lets the dynmultichoice menu finish closing before the
	@ sprite bubble pops in, otherwise the menu close + bubble open
	@ overlap and look choppy.
	delay 12
	showmonpic SPECIES_TREECKO, 10, 3
	msgbox DawnflakeTown_EvergreensLab_Text_TreeckoBlurb, MSGBOX_DEFAULT
	hidemonpic
	@ And again — let the bubble fully close before the YES/NO opens.
	delay 12
	msgbox DawnflakeTown_EvergreensLab_Text_StarterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterMenu
	goto DawnflakeTown_EvergreensLab_EventScript_GiveTreecko

DawnflakeTown_EvergreensLab_EventScript_PreviewTorchic::
	delay 12
	showmonpic SPECIES_TORCHIC, 10, 3
	msgbox DawnflakeTown_EvergreensLab_Text_TorchicBlurb, MSGBOX_DEFAULT
	hidemonpic
	delay 12
	msgbox DawnflakeTown_EvergreensLab_Text_StarterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_StarterMenu
	goto DawnflakeTown_EvergreensLab_EventScript_GiveTorchic

DawnflakeTown_EvergreensLab_EventScript_PreviewMudkip::
	delay 12
	showmonpic SPECIES_MUDKIP, 10, 3
	msgbox DawnflakeTown_EvergreensLab_Text_MudkipBlurb, MSGBOX_DEFAULT
	hidemonpic
	delay 12
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
	@ Evergreen reacts first — understated, the adult in the room.
	applymovement 1, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenPostBattleWin, MSGBOX_DEFAULT
	closemessage
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

@ ═══════════════════════════════════════════════════════════
@ Post-ceremony Evergreen — offers a POKEDEX rating check.
@ 10-tier evenly-divided scale across the 317-species dex.
@ Full dex (10/10) gifts a HIDDEN ABILITY CHARM (one-time).
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EvergreensLab_EventScript_EvergreenPost::
	lock
	faceplayer
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenPokedexIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DawnflakeTown_EvergreensLab_EventScript_EvergreenPokedexDecline
	@ Regional dex count is loaded into VAR_0x8006 by ScriptGetPokedexInfo.
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, ScriptGetPokedexInfo
	buffernumberstring STR_VAR_1, VAR_0x8006
	@ Tier thresholds: every 10% of the 317-species dex, full dex required for 10/10.
	compare VAR_0x8006, 317
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating10
	compare VAR_0x8006, 285
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating9
	compare VAR_0x8006, 254
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating8
	compare VAR_0x8006, 222
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating7
	compare VAR_0x8006, 190
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating6
	compare VAR_0x8006, 159
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating5
	compare VAR_0x8006, 127
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating4
	compare VAR_0x8006, 95
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating3
	compare VAR_0x8006, 64
	goto_if_ge DawnflakeTown_EvergreensLab_EventScript_PokedexRating2
	goto DawnflakeTown_EvergreensLab_EventScript_PokedexRating1

DawnflakeTown_EvergreensLab_EventScript_EvergreenPokedexDecline::
	msgbox DawnflakeTown_EvergreensLab_Text_EvergreenPokedexDecline, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating1::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating1, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating2::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating2, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating3::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating3, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating4::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating4, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating5::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating5, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating6::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating6, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating7::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating7, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating8::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating8, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating9::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating9, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating10::
	goto_if_set FLAG_SNOW_GOT_HA_CHARM, DawnflakeTown_EvergreensLab_EventScript_PokedexRating10Repeat
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating10Initial, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox DawnflakeTown_EvergreensLab_Text_HAReceived, MSGBOX_DEFAULT
	setflag FLAG_SNOW_GOT_HA_CHARM
	release
	end

DawnflakeTown_EvergreensLab_EventScript_PokedexRating10Repeat::
	msgbox DawnflakeTown_EvergreensLab_Text_PokedexRating10Repeat, MSGBOX_DEFAULT
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
	.string "PROF. EVERGREEN: There ya are!\p"
	.string "ASHER has been on his phone\n"
	.string "the whole time. Can ya\l"
	.string "believe that?\p"
	.string "Anyway, I drew all 3 of your\n"
	.string "names out of a hat.\p"
	.string "And {PLAYER} was the one I\n"
	.string "picked, so you'll get first\l"
	.string "pick.\p"
	.string "These 3 critters aren't like\n"
	.string "anything we've got here in\l"
	.string "BORALYSS.\p"
	.string "They come from a far-off region\n"
	.string "in the east called KARANAGA.\p"
	.string "Tropical, arid, and a long way\n"
	.string "from any winter.\p"
	.string "That means they're rare - the\n"
	.string "kind that can do big things\l"
	.string "in the right hands.\p"
	.string "So. Here they are.\p"
	.string "TREECKO, the WOOD GECKO POKEMON.\p"
	.string "TORCHIC, the FIRE CHICK POKEMON.\p"
	.string "And MUDKIP, the MUD FISH POKEMON.$"

DawnflakeTown_EvergreensLab_Text_EvergreenGotStarter:
	.string "PROF. EVERGREEN: Hm. Good.\n"
	.string "I think that one fits ya well.$"

DawnflakeTown_EvergreensLab_Text_EvergreenPokedex:
	.string "PROF. EVERGREEN: Looks like all 3\n"
	.string "of you are acquainted with your\l"
	.string "little beasts.\p"
	.string "Here is a brand new POKEDEX\n"
	.string "for each of you.\p"
	.string "Every POKEMON ya meet leaves\n"
	.string "a mark in there. The region's\l"
	.string "catalogue grows alongside ya.\p"
	.string "Consider it a small errand for\n"
	.string "me, and a helpful tool on the\l"
	.string "road ahead.$"

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
	.string "PROF. EVERGREEN: This here is\n"
	.string "TREECKO, the WOOD GECKO\l"
	.string "POKEMON. GRASS type.\p"
	.string "Sleeps in the high canopies\n"
	.string "of KARANAGA's jungles when\l"
	.string "the sun's at its worst.\p"
	.string "Got grip-pads on its hands\n"
	.string "and feet that stick to anything\l"
	.string "- glass, bark, even sheet ice.\p"
	.string "An adaptable and calculated\n"
	.string "fighter. Reads its opponent\l"
	.string "like a book before it ever\l"
	.string "throws a punch.$"

DawnflakeTown_EvergreensLab_Text_TorchicBlurb:
	.string "PROF. EVERGREEN: This here\n"
	.string "is TORCHIC, the FIRE CHICK\l"
	.string "POKEMON. FIRE type.\p"
	.string "Comes from the volcanic\n"
	.string "plateaus on the south edge\l"
	.string "of KARANAGA.\p"
	.string "Hatched in heat, and molded\n"
	.string "by the magma rock.\p"
	.string "Carries a fire sac in its belly\n"
	.string "that'll boil water right\l"
	.string "through the feathers.\p"
	.string "Imprints on its trainer like\n"
	.string "a chick on its mother. Loyal\l"
	.string "as they come.$"

DawnflakeTown_EvergreensLab_Text_MudkipBlurb:
	.string "PROF. EVERGREEN: And here\n"
	.string "we've got MUDKIP, the MUD FISH\l"
	.string "POKEMON. WATER type.\p"
	.string "Hatches in the mangrove swamps\n"
	.string "deep in KARANAGA, between\l"
	.string "patches of mud in the water\l"
	.string "that act as nests.\p"
	.string "The fin on its head feels every\n"
	.string "ripple in the water. Reads a\l"
	.string "storm coming a full day out.\p"
	.string "Slow to anger. But once that\n"
	.string "jaw closes - won't matter what -\l"
	.string "it ain't letting go.$"

DawnflakeTown_EvergreensLab_Text_StarterConfirm:
	.string "PROF. EVERGREEN: Is this the one?$"

DawnflakeTown_EvergreensLab_Text_EvergreenAllPicked:
	.string "PROF. EVERGREEN: All right then.\p"
	.string "Three trainers, three critters.\n"
	.string "The road takes it from here.\p"
	.string "Good luck too all of ya.$"

DawnflakeTown_EvergreensLab_Text_AutumnLabPreCeremony:
	.string "AUTUMN: {PLAYER}!! Finally!\p"
	.string "I'm so excited! I saw all 3\n"
	.string "POKEMON already, and they're\l"
	.string "all super adorable!\p"
	.string "Go go go - I want to see\n"
	.string "which one you pick!$"

DawnflakeTown_EvergreensLab_Text_AsherChallenge:
	.string "ASHER: Now that he's finally\n"
	.string "done.\p"
	.string "{PLAYER}, mine has the type\n"
	.string "advantage. I made sure of it.\p"
	.string "I've been ready for this,\n"
	.string "{PLAYER}.\p"
	.string "I hope you have too.\p"
	.string "Let's battle.$"

DawnflakeTown_EvergreensLab_Text_AsherDefeat:
	.string "ASHER: ...$"

DawnflakeTown_EvergreensLab_Text_AsherPostBattle:
	.string "ASHER: ...\p"
	.string "I prepped for this.\n"
	.string "But somehow you won anyway.\p"
	.string "Enjoy it while you can,\n"
	.string "{PLAYER}.$"

DawnflakeTown_EvergreensLab_Text_AsherPostBattleLoss:
	.string "ASHER: Hah.\p"
	.string "Told you I made sure, {PLAYER}.\p"
	.string "Don't worry though, EVERGREEN's\n"
	.string "right. You tried your best.\p"
	.string "Although it still wasn't enough.\p"
	.string "Alright, I'm out of here.$"

DawnflakeTown_EvergreensLab_Text_AsherVictoryInBattle:
	.string "ASHER: ...Scoff... That's it?$"

DawnflakeTown_EvergreensLab_Text_AsherBrush:
	.string "ASHER: I'm busy.$"

DawnflakeTown_EvergreensLab_Text_AutumnPitch:
	.string "AUTUMN: Oh my god, that was\n"
	.string "so cool.\p"
	.string "Both POKEMON fought so bravely,\n"
	.string "you should be proud, {PLAYER}!\p"
	.string "Anyway, {PLAYER}, meet me on\n"
	.string "ROUTE 1!\p"
	.string "I'm going to teach you how to\n"
	.string "catch a wild POKEMON, so bring\l"
	.string "your POKEDEX!$"

DawnflakeTown_EvergreensLab_Text_EvergreenWaitForAutumn:
	.string "PROF. EVERGREEN: Hm. Slow down\n"
	.string "a minute - AUTUMN's not here\l"
	.string "yet.\p"
	.string "She's at home sleeping like a\n"
	.string "SNORLAX, no doubt about it.\p"
	.string "{PLAYER}, would ya mind popping\n"
	.string "over there to wake her up for\l"
	.string "us?\p"
	.string "I don't want to be waiting\n"
	.string "another 2 hours.$"

DawnflakeTown_EvergreensLab_Text_EvergreenTM:
	.string "PROF. EVERGREEN: Well.\n"
	.string "That was something.\p"
	.string "Before ya head off, I got\n"
	.string "something to give ya. The TM\l"
	.string "for WORK UP.\p"
	.string "It's a one-time use item you\n"
	.string "can use to teach your POKEMON\l"
	.string "the move WORK UP.\p"
	.string "Trust me, it'll be mighty handy\n"
	.string "along the road ahead.\p"
	.string "All right then. Don't keep\n"
	.string "AUTUMN waiting, and good luck\l"
	.string "on your journey.$"

DawnflakeTown_EvergreensLab_Text_EvergreenReady:
	.string "PROF. EVERGREEN: Oh - you're\n"
	.string "finally back.\p"
	.string "Don't get too down on yourself,\n"
	.string "{PLAYER}.\p"
	.string "You tried your best, and that\n"
	.string "is what matters most.\p"
	.string "Remember that.$"

DawnflakeTown_EvergreensLab_Text_EvergreenPostBattleWin:
	.string "PROF. EVERGREEN: Well then!\p"
	.string "That was exhilarating, {PLAYER}.\p"
	.string "Ya really held your own there,\n"
	.string "and sometimes the trainer\l"
	.string "matters more than the matchup.\p"
	.string "Remember that.$"

DawnflakeTown_EvergreensLab_Text_EvergreenPokedexIntro:
	.string "PROF. EVERGREEN: Oh hello,\n"
	.string "{PLAYER}!\p"
	.string "I wasn't expecting ya to\n"
	.string "stop by.\p"
	.string "Do you want me to check your\n"
	.string "POKEDEX progress?$"

DawnflakeTown_EvergreensLab_Text_EvergreenPokedexDecline:
	.string "PROF. EVERGREEN: Suit yourself.\p"
	.string "Come back whenever you're\n"
	.string "ready.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating1:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "I'd score that a 1 out of 10.\p"
	.string "Plenty of road ahead. Keep\n"
	.string "your eyes open.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating2:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "2 out of 10.\p"
	.string "You're learning. Each new face\n"
	.string "teaches ya somethin' new.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating3:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "3 out of 10.\p"
	.string "Roughly a quarter of the region\n"
	.string "in there. Solid ground under\l"
	.string "your feet.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating4:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "4 out of 10.\p"
	.string "Coming along nicely. Some of\n"
	.string "these I had to chase for years.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating5:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "Halfway there. 5 out of 10.\p"
	.string "Plenty more to find. The rarer\n"
	.string "ones live in the harder places.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating6:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "6 out of 10.\p"
	.string "Most folks in BORALYSS never\n"
	.string "see this many in their whole\l"
	.string "lives.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating7:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "7 out of 10.\p"
	.string "Some of these I haven't even\n"
	.string "seen in person.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating8:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "8 out of 10.\p"
	.string "You're in rare air now. The\n"
	.string "last stretch is gonna test ya.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating9:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "9 out of 10. So close.\p"
	.string "A handful of species left,\n"
	.string "hiding in the most stubborn\l"
	.string "corners of BORALYSS.\p"
	.string "Go find 'em.$"

DawnflakeTown_EvergreensLab_Text_PokedexRating10Initial:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "...\p"
	.string "{STR_VAR_1} species in the dex.\p"
	.string "A perfect 10 out of 10.\p"
	.string "A complete BORALYSS POKEDEX.\p"
	.string "You've done what most folks\n"
	.string "in this region only dream\l"
	.string "about.\p"
	.string "Here. I've been hanging onto\n"
	.string "this for someone who could\l"
	.string "really earn it.\p"
	.string "The HIDDEN ABILITY CHARM.\p"
	.string "Wild POKEMON near ya will\n"
	.string "have a better chance of\l"
	.string "showing their rarer abilities.\p"
	.string "Take it. You've truly earned\n"
	.string "it, {PLAYER}.$"

DawnflakeTown_EvergreensLab_Text_HAReceived:
	.string "{PLAYER} received the\n"
	.string "HIDDEN ABILITY CHARM!$"

DawnflakeTown_EvergreensLab_Text_PokedexRating10Repeat:
	.string "PROF. EVERGREEN: Let me see\n"
	.string "what ya got.\p"
	.string "A complete POKEDEX. Still a\n"
	.string "perfect 10 out of 10.\p"
	.string "Hope that CHARM's been\n"
	.string "treating ya well.$"

DawnflakeTown_EvergreensLab_Text_Aide:
	.string "AIDE: Oh, hello child.\p"
	.string "Want to hear something funny?\p"
	.string "PROF. EVERGREEN is usually at\n"
	.string "the LAB more than his own\l"
	.string "house now.\p"
	.string "Although I guess it makes sense\n"
	.string "with the storm that's been\l"
	.string "going on the past 6 years.\p"
	.string "Even if it is a good thing,\n"
	.string "it's just not natural and\l"
	.string "needs to be studied.\p"
	.string "So I guess it's not that funny.$"
