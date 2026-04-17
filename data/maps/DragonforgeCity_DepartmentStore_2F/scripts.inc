DragonforgeCity_DepartmentStore_2F_MapScripts::
	.byte 0

@ Main clerk uses the shared Snow_DeptStore_2F_EventScript_Clerk (snow_mart.inc).

DragonforgeCity_DepartmentStore_2F_EventScript_Browser::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStore_2F_Text_Browser, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStore_2F_Text_Browser:
	.string "BROWSER: DUSK BALLS work better\n"
	.string "in IRONFROST CAVE.\p"
	.string "NET BALLS are best on the docks\n"
	.string "in ICEHARBOR.\p"
	.string "Bring the right ball for the\n"
	.string "right zone. Save your RARE\l"
	.string "CANDY for the league.$"
