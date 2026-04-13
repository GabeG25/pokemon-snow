PowderpathVillage_House2_MapScripts::
	.byte 0

PowderpathVillage_House2_EventScript_Mother::
	lock
	faceplayer
	msgbox PowderpathVillage_House2_Text_Mother, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House2_EventScript_Kid::
	lock
	faceplayer
	msgbox PowderpathVillage_House2_Text_Kid, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_House2_Text_Mother:
	.string "Shoes off, please. The snow\n"
	.string "tracks.\p"
	.string "Kettle's on. It's always on.\p"
	.string "We owe a lot to DIRECTOR TYRELL\n"
	.string "in this house. Don't mind my boy -\l"
	.string "he's repeating what he hears.$"

PowderpathVillage_House2_Text_Kid:
	.string "When I grow up I'm joining\n"
	.string "TEAM VEIL.\p"
	.string "They have the coolest masks and\n"
	.string "they make it snow FOREVER and\l"
	.string "they're going to catch KYUREM!\p"
	.string "MOM says I have to eat\n"
	.string "vegetables first though.$"
