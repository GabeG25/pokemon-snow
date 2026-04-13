PowderpathVillage_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Vanillite Ice Cream Vendor — warm old-school, Kai callback
@ v17 §10: Vanillite counts as Nuzlocke encounter for Powderpath
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
	.string "Oh - a new face on the path.\p"
	.string "Fresh ice cream, frost-cured\n"
	.string "the old way. One scoop at a time.$"

PowderpathVillage_Text_VendorOffer:
	.string "Tell you what. I've got a little\n"
	.string "VANILLITE in the back cart.\p"
	.string "Five hundred yen and it's yours.\n"
	.string "It'll keep your cooler cold and\l"
	.string "your team warm. Deal?$"

PowderpathVillage_Text_VendorGaveVanillite:
	.string "{PLAYER} received a VANILLITE!\p"
	.string "Kid named KAI used to pass\n"
	.string "through here. He still talking\l"
	.string "about my ice cream?\p"
	.string "Figures. Tell him the vendor\n"
	.string "says to eat a vegetable.$"

PowderpathVillage_Text_VendorDecline:
	.string "Suit yourself. The path doesn't\n"
	.string "get warmer from here.$"

PowderpathVillage_Text_VendorNoMoney:
	.string "Five hundred yen, dear. Come back\n"
	.string "when you've got it rattling.$"

PowderpathVillage_Text_VendorReturn:
	.string "Keep that VANILLITE cold and it\n"
	.string "will keep you fed all winter.$"

@ ═══════════════════════════════════════════════════════════
@ TM04 Return — old-timer, bond theme, said plain
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_TM04OldTimer::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_TM04_RETURN, PowderpathVillage_EventScript_TM04AlreadyGot
	msgbox PowderpathVillage_Text_TM04Intro, MSGBOX_DEFAULT
	giveitem ITEM_TM04
	compare VAR_RESULT, FALSE
	goto_if_eq PowderpathVillage_EventScript_TM04BagFull
	setflag FLAG_SNOW_GOT_TM04_RETURN
	msgbox PowderpathVillage_Text_TM04Outro, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_EventScript_TM04BagFull::
	msgbox PowderpathVillage_Text_TM04BagFull, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_EventScript_TM04AlreadyGot::
	msgbox PowderpathVillage_Text_TM04Return, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_TM04Intro:
	.string "Old man, leaning on a shovel.\p"
	.string "Been watching you walk your team\n"
	.string "through town. They're close to you.\p"
	.string "That bond - I mean the real thing,\n"
	.string "the thing between you and them -\l"
	.string "that's what no one can freeze.\p"
	.string "Not the weather. Not the grey\n"
	.string "masks. Not anyone.\p"
	.string "Take this. It's older than I am.$"

PowderpathVillage_Text_TM04Outro:
	.string "RETURN gets stronger the more\n"
	.string "your POKEMON likes you.\p"
	.string "Simple as that. Good ones usually\n"
	.string "are.$"

PowderpathVillage_Text_TM04BagFull:
	.string "Make room in your bag first.\n"
	.string "I'll hold it for you.$"

PowderpathVillage_Text_TM04Return:
	.string "Use it on the one that walks\n"
	.string "closest. You'll know which one.$"

@ ═══════════════════════════════════════════════════════════
@ Pro-Veil citizen — disturbingly reasonable
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_ProVeilCitizen::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_CitizenPraise, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_CitizenPraise:
	.string "My tomatoes used to die in the\n"
	.string "summer. Every year.\p"
	.string "Then DIRECTOR TYRELL came through,\n"
	.string "and now it snows straight through\l"
	.string "August. I grow winter squash now.\p"
	.string "People call TEAM VEIL scary\n"
	.string "because of the masks. I say\l"
	.string "they know what they're doing.\p"
	.string "Safe region. Full pantry. Quiet\n"
	.string "kids. That's enough for me.$"

@ ═══════════════════════════════════════════════════════════
@ Seeds-of-doubt villager — quiet, specific, scared
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_DoubtVillager::
	lock
	faceplayer
	msgbox PowderpathVillage_Text_DoubtVillager, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_DoubtVillager:
	.string "Don't stare at the one in grey.\n"
	.string "Keep walking.\p"
	.string "My brother asked a question once.\n"
	.string "The polite kind. Just a question.\p"
	.string "He lives in PINEGROVE now. Doesn't\n"
	.string "come home for the festivals.\p"
	.string "I'm not saying anything. I'm just\n"
	.string "telling you - don't stare.$"

@ ═══════════════════════════════════════════════════════════
@ Team Veil observer — polite, not hostile, implies a file
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_VeilObserver::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_POWDERPATH_OBSERVER_SEEN, PowderpathVillage_EventScript_VeilObserverSecond
	msgbox PowderpathVillage_Text_VeilObserverFirst, MSGBOX_DEFAULT
	setflag FLAG_SNOW_POWDERPATH_OBSERVER_SEEN
	release
	end

PowderpathVillage_EventScript_VeilObserverSecond::
	msgbox PowderpathVillage_Text_VeilObserverSecond, MSGBOX_DEFAULT
	release
	end

PowderpathVillage_Text_VeilObserverFirst:
	.string "Good morning, {PLAYER}.\p"
	.string "No, we haven't met. You're on the\n"
	.string "intake list. New trainer out of\l"
	.string "DAWNFLAKE, starter class. Noted.\p"
	.string "Enjoy the village. The DIRECTOR\n"
	.string "appreciates young people who move\l"
	.string "with purpose.$"

PowderpathVillage_Text_VeilObserverSecond:
	.string "Still moving with purpose. Good.\p"
	.string "I'll make a note.$"

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

PowderpathVillage_EventScript_TownSign::
	msgbox PowderpathVillage_Text_TownSign, MSGBOX_SIGN
	end

PowderpathVillage_EventScript_MartSign::
	msgbox PowderpathVillage_Text_MartSign, MSGBOX_SIGN
	end

PowderpathVillage_EventScript_PCSign::
	msgbox PowderpathVillage_Text_PCSign, MSGBOX_SIGN
	end

PowderpathVillage_Text_TownSign:
	.string "POWDERPATH VILLAGE\p"
	.string "Where the first snow of winter\n"
	.string "meets the last snow of spring.$"

PowderpathVillage_Text_MartSign:
	.string "POWDERPATH POKEMON MART\n"
	.string "Stocked for the long climb.$"

PowderpathVillage_Text_PCSign:
	.string "POWDERPATH POKEMON CENTER\n"
	.string "Rest here. The mountains don't.$"
