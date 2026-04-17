InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
	.byte 0

InsideOfTruck_OnLoad:
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
	end

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

@ ═══════════════════════════════════════════════════════════
@ Snow intro — redirects vanilla truck-exit to Dawnflake Town
@ instead of Littleroot Town and seeds Snow's hide flags.
@ VAR_LITTLEROOT_INTRO_STATE is pushed past the vanilla state
@ machine so none of the Littleroot in-house cutscenes fire.
@ ═══════════════════════════════════════════════════════════

InsideOfTruck_EventScript_SetIntroFlags::
	lockall
	setflag FLAG_HIDE_MAP_NAME_POPUP
	@ Push vanilla intro state past all scripted cutscenes so
	@ LittlerootTown and Brendan/May house scripts stay dormant.
	setvar VAR_LITTLEROOT_INTRO_STATE, 8
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 4
	@ Dump truck exit → Dawnflake Town, tile just south of the
	@ Player's House door (which is the painted door at 15,7).
	setdynamicwarp MAP_DAWNFLAKE_TOWN, 15, 8
	@ Snow-specific hide flags — NPCs that only appear during
	@ cutscene stages start hidden.
	setflag FLAG_SNOW_HIDE_AUTUMN_LAB
	setflag FLAG_SNOW_HIDE_AUTUMN_RUN_OUT_LAB
	setflag FLAG_SNOW_HIDE_MOM_RUNNING_SHOES
	setflag FLAG_SNOW_HIDE_ASHER_LAB
	@ Whiteout respawn → Mom in Player's House 1F. Override vanilla
	@ default so pre-Pokemon-Center losses don't ship to Petalburg.
	setrespawn HEAL_LOCATION_DAWNFLAKE_TOWN_PLAYERS_HOUSE_2F
	releaseall
	end

InsideOfTruck_EventScript_MovingBox::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with a POKéMON logo.\p"
	.string "It's a POKéMON brand moving and\n"
	.string "delivery service.$"
