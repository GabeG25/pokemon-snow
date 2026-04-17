IronfrostCity_Mart_MapScripts::
	.byte 0

@ Clerk NPC uses the shared Snow_PokeMart_EventScript_Clerk directly
@ (data/scripts/snow_mart.inc). Inventory auto-scales by badge count.

IronfrostCity_Mart_EventScript_Foreman::
	lock
	faceplayer
	msgbox IronfrostCity_Mart_Text_Foreman, MSGBOX_DEFAULT
	release
	end

IronfrostCity_Mart_Text_Foreman:
	.string "FOREMAN: Mine's shut down today.\n"
	.string "COPPER closed it after the\l"
	.string "incident.\p"
	.string "Something about the deep shaft\n"
	.string "having a 'guest' we can't name.\p"
	.string "Pay's docked. My crew's furious.$"
