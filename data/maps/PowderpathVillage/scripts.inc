PowderpathVillage_MapScripts::
	.byte 0

@ ===== Vanillite Ice Cream Vendor =====
@ Player can buy a Vanillite for 500 yen (v17 §10: counts as Nuzlocke encounter)

PowderpathVillage_EventScript_VanilliteVendor::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_VANILLITE, PowderpathVillage_EventScript_VendorAlreadyBought
	msgbox PowderpathVillage_Text_VendorIntro, MSGBOX_DEFAULT
	msgbox PowderpathVillage_Text_VendorOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq PowderpathVillage_EventScript_VendorBuy
	msgbox PowderpathVillage_Text_VendorDecline, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_EventScript_VendorBuy::
	checkmoney 500
	compare VAR_RESULT, FALSE
	goto_if_eq PowderpathVillage_EventScript_VendorNoMoney
	removemoney 500
	givemon SPECIES_VANILLITE, 5, ITEM_NONE
	msgbox PowderpathVillage_Text_VendorGaveVanillite, MSGBOX_DEFAULT
	setflag FLAG_SNOW_GOT_VANILLITE
	release
	end

PowderpathVillage_EventScript_VendorNoMoney::
	msgbox PowderpathVillage_Text_VendorNoMoney, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_EventScript_VendorAlreadyBought::
	msgbox PowderpathVillage_Text_VendorReturn, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_VendorIntro:
	.string "ICE CREAM VENDOR: Welcome!\n"
	.string "Fresh, frost-cured ice cream!\p"
	.string "Made the old way - one scoop at\n"
	.string "a time, slow and cold.$"

PowderpathVillage_Text_VendorOffer:
	.string "ICE CREAM VENDOR: Say, you look like\n"
	.string "a trainer! I have something special\l"
	.string "just for you.\p"
	.string "A little VANILLITE - one of nature's\n"
	.string "finest ice cream makers!\p"
	.string "Only 500 yen.\n"
	.string "Interested?$"

PowderpathVillage_Text_VendorBuy:
	.string "ICE CREAM VENDOR: Great choice!$"

PowderpathVillage_Text_VendorGaveVanillite:
	.string "You bought a VANILLITE for 500 yen!\p"
	.string "VENDOR: Take good care of it!\n"
	.string "It'll serve you well in battles.$"

PowderpathVillage_Text_VendorDecline:
	.string "ICE CREAM VENDOR: Suit yourself!\n"
	.string "Come back if you change your mind.$"

PowderpathVillage_Text_VendorNoMoney:
	.string "ICE CREAM VENDOR: Hmm, looks like\n"
	.string "you don't have enough yen.\p"
	.string "Come back when you can afford it!$"

PowderpathVillage_Text_VendorReturn:
	.string "ICE CREAM VENDOR: How's your\n"
	.string "VANILLITE doing? Keep it cool!$"
