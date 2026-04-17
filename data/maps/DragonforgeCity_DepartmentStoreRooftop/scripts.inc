DragonforgeCity_DepartmentStoreRooftop_MapScripts::
	.byte 0

@ Vending clerk uses the shared Snow_DeptStore_Roof_EventScript_Vending (snow_mart.inc).

DragonforgeCity_DepartmentStoreRooftop_EventScript_Watcher::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStoreRooftop_Text_Watcher, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStoreRooftop_Text_Watcher:
	.string "WOMAN: I can see Facility ALPHA\n"
	.string "from up here.\p"
	.string "The lights never go out.\n"
	.string "Day and night, something runs.\p"
	.string "TEAM VEIL calls it a research\n"
	.string "station. I call it a furnace.$"
