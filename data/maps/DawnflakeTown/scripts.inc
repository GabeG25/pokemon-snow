DawnflakeTown_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DawnflakeTown_OnFrame
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Frame table — Mom Running Shoes auto-cutscene
@ Fires on the first frame of every Dawnflake map load. The
@ setvar VAR_TEMP_1 guard prevents re-fire within this map
@ session; VAR_TEMP_1 resets to 0 on each map load so the
@ check re-runs on every entry (flag gate still prevents
@ firing after the cutscene has already run).
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_OnFrame:
	map_script_2 VAR_TEMP_1, 0, DawnflakeTown_EventScript_MaybeMomLabExit
	.2byte 0

DawnflakeTown_EventScript_MaybeMomLabExit::
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_SNOW_HIDE_MOM_RUNNING_SHOES, DawnflakeTown_EventScript_MomLabExit
	end

@ ═══════════════════════════════════════════════════════════
@ Ambient villager
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_Villager::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EventScript_VillagerPostRival
	msgbox DawnflakeTown_Text_Villager, MSGBOX_DEFAULT
	release
	end

DawnflakeTown_EventScript_VillagerPostRival::
	msgbox DawnflakeTown_Text_VillagerPostRival, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ South-exit starter gate — y=18 row.
@ Blocks Route 1 passage until the starter cutscene is done.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_SouthExitStarterGate::
	lockall
	goto_if_unset FLAG_SNOW_STARTER_CUTSCENE_DONE, DawnflakeTown_EventScript_StarterGateBlock
	releaseall
	end

DawnflakeTown_EventScript_StarterGateBlock::
	msgbox DawnflakeTown_Text_StarterGateBlock2, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, DawnflakeTown_Movement_PlayerPushBack
	waitmovement 0
	releaseall
	end

@ ═══════════════════════════════════════════════════════════
@ Mom Running Shoes auto-cutscene.
@
@ Fires the first time the player arrives in Dawnflake after
@ the starter ceremony is complete (either win or loss path —
@ both clear FLAG_SNOW_HIDE_MOM_RUNNING_SHOES at the end of
@ the lab sequence).
@
@ Flow:
@   1. Player exited the lab; the door-exit animation auto-walks
@      them to (4,17) facing south.
@   2. Script turns player in place to guarantee facing south.
@   3. Mom (LOCALID 2) walks 1 south + 5 west from (9,17) to
@      (4,18), then face_up. Player at (4,17) facing south; Mom
@      at (4,18) facing north — face-to-face on column x=4, the
@      same pattern used for Autumn's R1 catching tutorial.
@   4. Running Shoes dialogue; B-dash + RECEIVED flags set.
@   5. Mom returns via x=9 column: 5 east to (9,18), 10 north to
@      (9,8), 4 east to (13,8). Clear of Autumn's doorstep and
@      the lab footprint.
@   6. Opendoor, Mom walks up onto the warp tile, removeobject.
@   7. DONE + HIDE flags set; player released facing south.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_MomLabExit::
	lockall
	applymovement LOCALID_PLAYER, DawnflakeTown_Movement_PlayerExitLab
	waitmovement 0
	applymovement 2, DawnflakeTown_Movement_MomApproachPlayer
	waitmovement 0
	msgbox DawnflakeTown_Text_MomRunningShoes, MSGBOX_DEFAULT
	setflag FLAG_SYS_B_DASH
	setflag FLAG_RECEIVED_RUNNING_SHOES
	closemessage
	applymovement 2, DawnflakeTown_Movement_MomReturnToHouse
	waitmovement 0
	opendoor 13, 7
	waitdooranim
	applymovement 2, DawnflakeTown_Movement_MomEnterDoor
	waitmovement 0
	removeobject 2
	closedoor 13, 7
	waitdooranim
	setflag FLAG_SNOW_MOM_RUNNING_SHOES_DONE
	setflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	releaseall
	end

@ ═══════════════════════════════════════════════════════════
@ Movements
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_Movement_PlayerPushBack:
	walk_up
	step_end

@ Player already auto-walked south to (4,17) as part of the
@ lab-exit door animation. Just ensure they're facing south
@ so Mom's approach from (4,18) lands face-to-face.
DawnflakeTown_Movement_PlayerExitLab:
	walk_in_place_faster_down
	step_end

@ Mom walks south 1 tile to (9,18), then 5 tiles west to (4,18),
@ then turns to face north. Same face-to-face pattern used by
@ Autumn's catching tutorial on Route 1.
DawnflakeTown_Movement_MomApproachPlayer:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

@ Mom's return path:
@   (4,18) -> (9,18)                     5 east
@   (9,18) -> (9,8)                      10 north
@   (9,8)  -> (13,8)                     4 east
@ Ends at (13,8), facing east. Next step walks up into the
@ Player's house door at (13,7).
DawnflakeTown_Movement_MomReturnToHouse:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

DawnflakeTown_Movement_MomEnterDoor:
	walk_up
	step_end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_Text_Villager:
	.string "VILLAGER: Morning, dear.\p"
	.string "First Pokemon today? Oh, how\n"
	.string "exciting. Mind the snow - it's\l"
	.string "been coming down strange lately.\p"
	.string "Strange, and early.$"

DawnflakeTown_Text_VillagerPostRival:
	.string "VILLAGER: Poor Asher.\p"
	.string "He used to laugh, that boy.\n"
	.string "Back before the mountain went\l"
	.string "quiet.$"

DawnflakeTown_Text_MomRunningShoes:
	.string "MOM: {PLAYER}! Wait, wait -\n"
	.string "don't leave yet!\p"
	.string "I knew you'd forget. Here -\n"
	.string "your RUNNING SHOES.\p"
	.string "The cold makes everything slow.\n"
	.string "These will help.\p"
	.string "Come home if you need to, okay?\n"
	.string "Promise me.$"

DawnflakeTown_Text_StarterGateBlock2:
	.string "The trail south looks rough.\p"
	.string "Better grab a POKEMON from\n"
	.string "PROF. EVERGREEN's lab first.$"
