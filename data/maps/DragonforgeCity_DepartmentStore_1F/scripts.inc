DragonforgeCity_DepartmentStore_1F_MapScripts::
	.byte 0

DragonforgeCity_DepartmentStore_1F_EventScript_Greeter::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStore_1F_Text_Greeter, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStore_1F_EventScript_Shopper::
	lock
	faceplayer
	msgbox DragonforgeCity_DepartmentStore_1F_Text_Shopper, MSGBOX_DEFAULT
	release
	end

DragonforgeCity_DepartmentStore_1F_EventScript_FloorSign::
	msgbox DragonforgeCity_DepartmentStore_1F_Text_FloorSign, MSGBOX_SIGN
	end

DragonforgeCity_DepartmentStore_1F_Text_Greeter:
	.string "GREETER: Welcome to DRAGONFORGE\n"
	.string "DEPARTMENT STORE!\p"
	.string "1F - Lobby & Information\n"
	.string "2F - Poke Mart Plus\p"
	.string "3F - TM Shop\n"
	.string "4F - Battle Items\p"
	.string "5F - Evolution & Specialty\n"
	.string "Rooftop - Vending & Lounge$"

DragonforgeCity_DepartmentStore_1F_Text_Shopper:
	.string "SHOPPER: Been coming here every\n"
	.string "month for three years.\p"
	.string "Best selection in BORALYSS.\n"
	.string "Beats catching anything on\l"
	.string "DRIFTROCK.$"

DragonforgeCity_DepartmentStore_1F_Text_FloorSign:
	.string "DRAGONFORGE DEPARTMENT STORE\p"
	.string "1F - LOBBY\n"
	.string "2F - POKE MART PLUS\p"
	.string "3F - TM SHOP\n"
	.string "4F - BATTLE ITEMS\p"
	.string "5F - EVOLUTION STONES\n"
	.string "ROOFTOP - VENDING$"
