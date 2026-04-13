PowderpathVillage_House1_MapScripts::
	.byte 0

PowderpathVillage_House1_EventScript_Wife::
	lock
	faceplayer
	msgbox PowderpathVillage_House1_Text_Wife, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House1_Text_Wife:
	.string "My husband is out in the plaza\n"
	.string "again. He does that. Watches\l"
	.string "the trainers come through.\p"
	.string "He was one himself, you know.\n"
	.string "Long time ago. Had a FURRET that\l"
	.string "followed him everywhere.\p"
	.string "He still talks to it in his\n"
	.string "sleep.$"
