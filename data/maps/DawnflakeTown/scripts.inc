DawnflakeTown_MapScripts::
	.byte 0

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
@ Starter Gate Elder — blocks south exit until player has starter
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_StarterGateElder::
	lock
	faceplayer
	msgbox DawnflakeTown_Text_StarterGateElder, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Mom Running Shoes cutscene
@ Fires once when player approaches the south exit post-starter.
@ ═══════════════════════════════════════════════════════════

@ ═══════════════════════════════════════════════════════════
@ South-exit trigger — unified handler for all y=18 tiles.
@ Priority 1: block passage if starter cutscene not done.
@ Priority 2: Mom running shoes cutscene if post-rival.
@ Priority 3: pass through silently.
@ ═══════════════════════════════════════════════════════════

DawnflakeTown_EventScript_MomRunningShoesTrigger::
	lockall
	goto_if_unset FLAG_SNOW_STARTER_CUTSCENE_DONE, DawnflakeTown_EventScript_StarterGateBlock
	goto_if_set FLAG_SNOW_MOM_RUNNING_SHOES_DONE, DawnflakeTown_EventScript_MomRunningShoesEnd
	goto_if_unset FLAG_SNOW_BEAT_F1_ASHER, DawnflakeTown_EventScript_MomRunningShoesEnd
	applymovement OBJ_EVENT_ID_PLAYER, DawnflakeTown_Movement_PlayerFaceUp
	waitmovement 0
	msgbox DawnflakeTown_Text_MomRunningShoes, MSGBOX_DEFAULT
	setflag FLAG_SYS_B_DASH
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SNOW_MOM_RUNNING_SHOES_DONE
	setflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	removeobject 3
	releaseall
	end

DawnflakeTown_EventScript_StarterGateBlock::
	msgbox DawnflakeTown_Text_StarterGateBlock2, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, DawnflakeTown_Movement_PlayerPushBack
	waitmovement 0
	releaseall
	end

DawnflakeTown_EventScript_MomRunningShoesEnd::
	releaseall
	end

@ Interacting directly with Mom (before she approaches) runs the same scene.
DawnflakeTown_EventScript_MomRunningShoes::
	lockall
	faceplayer
	goto DawnflakeTown_EventScript_MomRunningShoesTrigger

DawnflakeTown_Movement_PlayerFaceUp:
	walk_in_place_faster_up
	step_end

DawnflakeTown_Movement_PlayerPushBack:
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

DawnflakeTown_Text_StarterGateElder:
	.string "ELDER: Hey there, kid.\p"
	.string "Head to EVERGREEN's lab first -\n"
	.string "you're not leaving DAWNFLAKE\l"
	.string "without a POKEMON.\p"
	.string "The trails south don't forgive\n"
	.string "travellers who wander in empty-\l"
	.string "handed.$"

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
