IcespireTown_PokemonCenter_1F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Nurse Joy — custom inline heal with full animation.
@ Replicates the nurse-turn + heal-field-effect + nurse-bow
@ from Common_EventScript_PkmnCenterNurse, but skips the
@ Gold-Card / Pokerus / Cable-Club branches that race-condition
@ the dialogue boxes and produce blank text on second-talk.
@ Same fix as PowderpathVillage_PokemonCenter_1F_EventScript_Nurse.
@ Nurse is object index 0 in map.json => local_id 1.
@ ═══════════════════════════════════════════════════════════

IcespireTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq IcespireTown_PokemonCenter_1F_EventScript_NurseHeal
	msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
	release
	end

IcespireTown_PokemonCenter_1F_EventScript_NurseHeal::
	setvar VAR_0x800B, 1
	incrementgamestat GAME_STAT_USED_POKECENTER
	message gText_IllTakeYourPkmn
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Turn
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	message gText_RestoredPkmnToFullHealth
	waitmessage
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
	release
	end

IcespireTown_PokemonCenter_1F_EventScript_ShakenTrainer::
	lock
	faceplayer
	msgbox IcespireTown_PokemonCenter_1F_Text_ShakenTrainer, MSGBOX_DEFAULT
	release
	end

IcespireTown_PokemonCenter_1F_Text_ShakenTrainer:
	.string "SHAKEN TRAINER: SILVAN'S PIPLUP\n"
	.string "is faster than my starter.\p"
	.string "How is that even POSSIBLE? My\n"
	.string "POKEMON is fully evolved!\p"
	.string "...\p"
	.string "Something about the hail.\n"
	.string "Something about his ABILITY.\p"
	.string "Whatever it is, it's not fair.$"
