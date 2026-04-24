PowderpathVillage_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Vanillite Ice Cream Vendor — stands at (4,11) behind the
@ counter. Player approaches from (4,12) plaza, talks up.
@ v17 §10: Vanillite counts as Nuzlocke encounter for PP.
@ ═══════════════════════════════════════════════════════════

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
	.string "VENDOR: Oh - a new face on the\n"
	.string "path.\p"
	.string "Fresh snow still in your hair.\p"
	.string "Used to run this cart down in\n"
	.string "DAWNFLAKE, summers. Back when we\l"
	.string "had summers.\p"
	.string "People still want ice cream,\n"
	.string "winter or not.\p"
	.string "Funny thing, isn't it?$"

PowderpathVillage_Text_VendorOffer:
	.string "VENDOR: Tell you what, dear.\p"
	.string "I've got a little VANILLITE in\n"
	.string "the back cart. Came out of a\l"
	.string "drift up the trail.\p"
	.string "Five hundred yen and she's yours.\n"
	.string "She'll keep your cooler cold and\l"
	.string "your team warm.\p"
	.string "Deal?$"

PowderpathVillage_Text_VendorGaveVanillite:
	.string "{PLAYER} received a VANILLITE!\p"
	.string "VENDOR: Good. She's been looking\n"
	.string "for someone.\p"
	.string "Walk careful up the mountain,\n"
	.string "dear. Cold's got weight to it\l"
	.string "these past winters.\p"
	.string "You'll feel it in your bones\n"
	.string "before you feel it on your skin.$"

PowderpathVillage_Text_VendorDecline:
	.string "VENDOR: Suit yourself.\p"
	.string "The path doesn't get warmer from\n"
	.string "here, mind you.$"

PowderpathVillage_Text_VendorNoMoney:
	.string "VENDOR: Five hundred yen, dear.\p"
	.string "Come back when you've got it\n"
	.string "rattling.$"

PowderpathVillage_Text_VendorReturn:
	.string "VENDOR: Keep that VANILLITE cold\n"
	.string "and she'll keep you fed all winter.\p"
	.string "That's what a good POKEMON does.\n"
	.string "Keeps you.\p"
	.string "Longer than the weather will.$"

@ ═══════════════════════════════════════════════════════════
@ Pro-Veil citizen (south of PC) — tough-love supporter,
@ specific about what's changed in her life.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_ProVeilCitizen::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_CitizenPraise, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_CitizenPraise:
	.string "CITIZEN: Good afternoon.\p"
	.string "You look like someone who's going\n"
	.string "to ask me what I think about the\l"
	.string "DIRECTOR.\p"
	.string "My tomatoes used to die every\n"
	.string "summer. Too hot, too wet. I'd pull\l"
	.string "the whole row up by August.\p"
	.string "They don't die anymore.\p"
	.string "Kids sleep through the night.\n"
	.string "Pantry's full. Nobody comes\l"
	.string "banging on the door at midnight.\p"
	.string "Call me old-fashioned. A quiet\n"
	.string "winter and a full cellar suits me\l"
	.string "fine.\p"
	.string "Some things you don't question,\n"
	.string "dear.$"

@ ═══════════════════════════════════════════════════════════
@ Veil supporter (MAN_3, NW corner) — uninformed pro-Veil
@ townsfolk, not an actual member. Just likes the winter.
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_VeilObserver::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_VeilObserver, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_VeilObserver:
	.string "MAN: Morning. Nice day.\p"
	.string "Well - every day is a nice day\n"
	.string "now, I suppose. Same day, really.\p"
	.string "Snow and snow and more snow.\p"
	.string "I like it. Always have.\p"
	.string "My knees used to go in the summer\n"
	.string "heat. Now they don't. They say\l"
	.string "that's TEAM VEIL's doing.\p"
	.string "Don't really know what they're up\n"
	.string "to. Something with the big\l"
	.string "mountain, folks say.\p"
	.string "Doesn't concern me. They've kept\n"
	.string "things steady.\p"
	.string "That's more than the last lot\n"
	.string "managed.$"

@ ═══════════════════════════════════════════════════════════
@ Ice cream fan — kid loitering west of the vendor cart
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_IceCreamFan::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_IceCreamFan, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_IceCreamFan:
	.string "BOY: The lady sells ICE CREAM.\p"
	.string "In winter.\p"
	.string "I asked her why once. She said\n"
	.string "'cold stays cold, whether anyone's\l"
	.string "buying or not.'\p"
	.string "I don't know what that means.\p"
	.string "I just like the ice cream.\p"
	.string "...\p"
	.string "Mom says I can't have another\n"
	.string "scoop until next week.$"

@ ═══════════════════════════════════════════════════════════
@ Flower-lover — tends the FLOWERS beside the vendor's cart
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_FlowerLover::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_FlowerLover, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_FlowerLover:
	.string "WOMAN: They still bloom, you know.\p"
	.string "Under the snow.\p"
	.string "I planted these FLOWERS when\n"
	.string "POWDERPATH was warmer. Thought\l"
	.string "I'd have to dig them up when\l"
	.string "winter came and stayed.\p"
	.string "They just kept going. Quiet.\n"
	.string "Under the drifts.\p"
	.string "Like they were waiting for\n"
	.string "something the rest of us gave up\l"
	.string "on.\p"
	.string "That's why I tend them. Somebody\n"
	.string "ought to notice.$"

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_MartSign::
	msgbox PowderpathVillage_Text_MartSign, MSGBOX_SIGN
	end

PowderpathVillage_EventScript_PCSign::
	msgbox PowderpathVillage_Text_PCSign, MSGBOX_SIGN
	end

PowderpathVillage_Text_MartSign:
	.string "POWDERPATH POKEMON MART\p"
	.string "Stocked for the long climb\n"
	.string "ahead.\p"
	.string "Don't forget a REPEL.$"

PowderpathVillage_Text_PCSign:
	.string "POWDERPATH POKEMON CENTER\p"
	.string "Rest here.\p"
	.string "The mountains don't.$"
