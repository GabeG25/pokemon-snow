PowderpathVillage_PokemonCenter_1F_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Nurse Joy — custom inline heal with full animation.
@ Replicates the nurse-turn + heal-field-effect + nurse-bow
@ from Common_EventScript_PkmnCenterNurse, but skips the
@ Gold-Card / Pokerus / Cable-Club branches that were
@ race-conditioning the dialogue boxes on second-talk.
@ Nurse is object index 0 in map.json => local_id 1.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	msgbox gText_WouldYouLikeToRestYourPkmn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PowderpathVillage_PokemonCenter_1F_EventScript_NurseHeal
	msgbox gText_WeHopeToSeeYouAgain, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_PokemonCenter_1F_EventScript_NurseHeal::
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

@ ═══════════════════════════════════════════════════════════
@ Boarder — mountain trainer flavor, warns about the climb
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_PokemonCenter_1F_EventScript_Boarder::
	lock
	faceplayer
	msgbox PowderpathVillage_PokemonCenter_1F_Text_Boarder, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_PokemonCenter_1F_Text_Boarder:
	.string "BOARDER: Coming up out of\n"
	.string "DAWNFLAKE? Good.\p"
	.string "Heads up - the climb to ICESPIRE\n"
	.string "eats trainers who don't top off\l"
	.string "here first.\p"
	.string "Board's waxed. Party's full.\n"
	.string "I'm waiting on the wind to turn.\p"
	.string "You'll want a FIRE type up there,\n"
	.string "if you can swing it. And a REPEL.\l"
	.string "And a lot of patience.$"

@ ═══════════════════════════════════════════════════════════
@ Lass — young trainer flavor, early game excitement
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_PokemonCenter_1F_EventScript_Lass::
	lock
	faceplayer
	msgbox PowderpathVillage_PokemonCenter_1F_Text_Lass, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_PokemonCenter_1F_Text_Lass:
	.string "LASS: My ZIGZAGOON fainted TWICE\n"
	.string "on the way here.\p"
	.string "I'm gonna rest up and then go\n"
	.string "catch a SNORUNT. That's my plan.\p"
	.string "Have you caught anything yet?\n"
	.string "I heard there's a VANILLITE vendor\l"
	.string "in the plaza.\p"
	.string "She's got a good setup. Painted\n"
	.string "the canopy herself, they say.$"
