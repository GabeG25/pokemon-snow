IronfrostCaveB2B3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IronfrostCaveB2B3_OnTransition
	.byte 0

@ On every entry, reveal Kyurem if the player has defeated F27 Tyrell #2
@ (per v17: Kyurem flies back to IronfrostCave depths after Tyrell's
@ defeat and the Facility Alpha cataclysm). Pre-F27, Kyurem is absent.

IronfrostCaveB2B3_OnTransition::
	goto_if_set FLAG_SNOW_BEAT_F27_TYRELL, IronfrostCaveB2B3_EventScript_RevealKyurem
	end

IronfrostCaveB2B3_EventScript_RevealKyurem::
	goto_if_set FLAG_SNOW_BEAT_KYUREM, IronfrostCaveB2B3_EventScript_KeepHidden
	clearflag FLAG_SNOW_HIDE_KYUREM_CAVE
	end

IronfrostCaveB2B3_EventScript_KeepHidden::
	setflag FLAG_SNOW_HIDE_KYUREM_CAVE
	end

@ ═══════════════════════════════════════════════════════════════
@ KYUREM STATIC ENCOUNTER
@ ═══════════════════════════════════════════════════════════════
@ Post-F27 Tyrell #2, Kyurem has retreated to its lair at the
@ deepest floor of Ironfrost Cave. Player can optionally traverse
@ B1 → B2B3 to reach this chamber. Standard legendary encounter
@ pattern (modeled on SkyPillar_Top Rayquaza): moncry → setwildbattle
@ → BattleSetup_StartLegendaryBattle → branch on outcome. Player
@ gets ONE attempt regardless of result; FLAG_SNOW_BEAT_KYUREM
@ locks the encounter after any terminal outcome (caught, defeated,
@ or fled).

IronfrostCaveB2B3_EventScript_Kyurem::
	lockall
	msgbox IronfrostCaveB2B3_Text_KyuremApproach, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_KYUREM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_KYUREM, 90
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, IronfrostCaveB2B3_EventScript_KyuremCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, IronfrostCaveB2B3_EventScript_KyuremFled
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, IronfrostCaveB2B3_EventScript_KyuremFled
	@ Defeat / whiteout / tie — treat as one-shot encounter exhausted
	setflag FLAG_SNOW_BEAT_KYUREM
	setflag FLAG_SNOW_HIDE_KYUREM_CAVE
	removeobject 1
	releaseall
	end

IronfrostCaveB2B3_EventScript_KyuremCaught::
	setflag FLAG_SNOW_BEAT_KYUREM
	setflag FLAG_SNOW_HIDE_KYUREM_CAVE
	removeobject 1
	releaseall
	end

IronfrostCaveB2B3_EventScript_KyuremFled::
	@ Ran or teleported out — Kyurem stays in the chamber for another
	@ attempt. Flag NOT set so the object remains visible next entry.
	releaseall
	end

IronfrostCaveB2B3_Text_KyuremApproach:
	.string "A vast frozen form stirs in\n"
	.string "the chamber's dark.\p"
	.string "The ice forms a throne.\n"
	.string "It is KYUREM.\p"
	.string "It regards you, breath frosting\n"
	.string "the air between you.$"
