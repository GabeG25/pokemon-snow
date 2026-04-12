PyrespireCity_MapScripts::
	.byte 0

PyrespireCity_EventScript_GymLeaderScorch::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F23_SCORCH, PyrespireCity_EventScript_ScorchDefeated
	goto_if_unset FLAG_BADGE07_GET, PyrespireCity_EventScript_ScorchNeedBadge
	msgbox PyrespireCity_Text_ScorchIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F23_SCORCH, PyrespireCity_Text_ScorchDefeat
	setflag FLAG_SNOW_BEAT_F23_SCORCH
	setflag FLAG_BADGE08_GET
	msgbox PyrespireCity_Text_ScorchPostBattle, MSGBOX_DEFAULT
	giveitem ITEM_TM43, 1
	msgbox PyrespireCity_Text_ScorchGiveTM, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_ScorchDefeated::
	msgbox PyrespireCity_Text_ScorchPostBattle, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_ScorchNeedBadge::
	msgbox PyrespireCity_Text_ScorchLocked, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_VolcanoHermitTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE08_GET, PyrespireCity_EventScript_HermitLocked
	msgbox PyrespireCity_Text_HermitIntro, MSGBOX_DEFAULT
	msgbox PyrespireCity_Text_HermitOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PyrespireCity_EventScript_HermitTeach
	msgbox PyrespireCity_Text_HermitDecline, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_HermitTeach::
	checkmoney 6000
	compare VAR_RESULT, FALSE
	goto_if_eq PyrespireCity_EventScript_HermitNoMoney
	removemoney 6000
	setvar VAR_0x8005, MOVE_SUPERPOWER
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq PyrespireCity_EventScript_HermitCancel
	msgbox PyrespireCity_Text_HermitTaught, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_HermitCancel::
	msgbox PyrespireCity_Text_HermitDecline, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_HermitNoMoney::
	msgbox PyrespireCity_Text_HermitNoMoney, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_HermitLocked::
	msgbox PyrespireCity_Text_HermitLocked, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_DragonScaleNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_DRAGON_SCALE, PyrespireCity_EventScript_DragonScaleDone
	msgbox PyrespireCity_Text_DragonScaleIntro, MSGBOX_DEFAULT
	giveitem ITEM_DRAGON_SCALE, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_DRAGON_SCALE
	msgbox PyrespireCity_Text_DragonScaleGiven, MSGBOX_DEFAULT
	release
	end

PyrespireCity_EventScript_DragonScaleDone::
	msgbox PyrespireCity_Text_DragonScalePost, MSGBOX_DEFAULT
	release
	end

PyrespireCity_Text_ScorchIntro:
	.string "SCORCH: The volcano calls to me,\n"
	.string "as fire calls to all who love it.\p"
	.string "Are you ready to burn?$"

PyrespireCity_Text_ScorchDefeat:
	.string "SCORCH: Even the fiercest flame\n"
	.string "can be quenched.$"

PyrespireCity_Text_ScorchPostBattle:
	.string "SCORCH: You've earned the\n"
	.string "EMBER BADGE - the final gym badge.$"

PyrespireCity_Text_ScorchGiveTM:
	.string "SCORCH: TM43 - FLAMETHROWER.\n"
	.string "The final lesson of the gyms.$"

PyrespireCity_Text_ScorchLocked:
	.string "SCORCH: Seven badges before you\n"
	.string "face the fire of PYRESPIRE.$"

PyrespireCity_Text_HermitIntro:
	.string "VOLCANO HERMIT: The mountain taught\n"
	.string "me everything.\p"
	.string "Heat, pressure, and time make\n"
	.string "diamonds - and unstoppable POKEMON.$"

PyrespireCity_Text_HermitOffer:
	.string "HERMIT: I can teach SUPERPOWER.\n"
	.string "Costs 6000 yen. Interested?$"

PyrespireCity_Text_HermitDecline:
	.string "HERMIT: The mountain is patient.$"

PyrespireCity_Text_HermitNoMoney:
	.string "HERMIT: Return with enough coin.$"

PyrespireCity_Text_HermitLocked:
	.string "HERMIT: Bring me eight badges first.$"

PyrespireCity_Text_HermitTaught:
	.string "HERMIT: SUPERPOWER taught.$"

PyrespireCity_Text_DragonScaleIntro:
	.string "DRAGON RESEARCHER: I've spent years\n"
	.string "studying the Kingdra specimens in\l"
	.string "the southern lagoon.\p"
	.string "This scale was shed by one of the\n"
	.string "largest I ever documented.\p"
	.string "It resonates with a SEADRA's\n"
	.string "draconic potential - if you have\l"
	.string "one, this scale will awaken it.$"

PyrespireCity_Text_DragonScaleGiven:
	.string "{PLAYER} received the DRAGON SCALE!$"

PyrespireCity_Text_DragonScalePost:
	.string "DRAGON RESEARCHER: Has your SEADRA\n"
	.string "evolved yet?$"
