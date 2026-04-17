DragonforgeCity_DepartmentStore_5F_MapScripts::
	.byte 0

@ Evolution clerk uses the shared Snow_DeptStore_5F_EventScript_Clerk (snow_mart.inc).

DragonforgeCity_DepartmentStore_5F_EventScript_EvoFan::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStore_5F_Text_EvoFan, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStore_5F_Text_EvoFan:
	.string "LITTLE GIRL: The LINKING CORD\n"
	.string "evolves trade POKEMON.\p"
	.string "Mom says that used to need a\n"
	.string "friend with another GAME BOY.\p"
	.string "I'm glad we live in the future!$"
