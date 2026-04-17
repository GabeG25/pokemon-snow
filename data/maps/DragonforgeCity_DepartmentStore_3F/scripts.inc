DragonforgeCity_DepartmentStore_3F_MapScripts::
	.byte 0

@ TM clerk uses the shared Snow_DeptStore_3F_EventScript_Clerk (snow_mart.inc).

DragonforgeCity_DepartmentStore_3F_EventScript_TMCollector::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStore_3F_Text_TMCollector, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStore_3F_Text_TMCollector:
	.string "SCHOOL KID: I'm collecting every\n"
	.string "TM in BORALYSS.\p"
	.string "Only six sold here, but the\n"
	.string "rest drop from trainers and\l"
	.string "the LEAGUE.\p"
	.string "Almost got them all.$"
