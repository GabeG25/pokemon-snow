IcespireTown_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ Asher F4 — Post-Gym 1 rematch
@ Compounding frustration, starts sensing something is wrong
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_AsherF4::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F4_ASHER, IcespireTown_EventScript_AsherF4Defeated
	msgbox IcespireTown_Text_AsherF4Intro, MSGBOX_DEFAULT
	compare VAR_STARTER_MON, 0
	goto_if_eq IcespireTown_EventScript_AsherF4VariantA
	compare VAR_STARTER_MON, 1
	goto_if_eq IcespireTown_EventScript_AsherF4VariantB
	compare VAR_STARTER_MON, 2
	goto_if_eq IcespireTown_EventScript_AsherF4VariantC
	end

IcespireTown_EventScript_AsherF4VariantA::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_A, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4VariantB::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_B, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4VariantC::
	trainerbattle_no_intro TRAINER_SNOW_F4_ASHER_C, IcespireTown_Text_AsherF4Defeat
	goto IcespireTown_EventScript_AsherF4AfterBattle
	end

IcespireTown_EventScript_AsherF4AfterBattle::
	setflag FLAG_SNOW_BEAT_F4_ASHER
	msgbox IcespireTown_Text_AsherF4PostBattle, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_AsherF4Defeated::
	msgbox IcespireTown_Text_AsherF4PostDefeat, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Wide Lens NPC gift
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_WideLensNPC::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_GOT_WIDE_LENS, IcespireTown_EventScript_WideLensDone
	msgbox IcespireTown_Text_WideLensIntro, MSGBOX_DEFAULT
	giveitem ITEM_WIDE_LENS, 1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_SNOW_GOT_WIDE_LENS
	msgbox IcespireTown_Text_WideLensGiven, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_WideLensDone::
	msgbox IcespireTown_Text_WideLensPost, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Roughneck Move Tutor — single move (Body Slam), 2000 yen
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_RoughneckTutor::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE01_GET, IcespireTown_EventScript_RoughneckLocked
	msgbox IcespireTown_Text_RoughneckIntro, MSGBOX_DEFAULT
	msgbox IcespireTown_Text_RoughneckOffer, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq IcespireTown_EventScript_RoughneckTeach
	msgbox IcespireTown_Text_RoughneckDecline, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckTeach::
	checkmoney 2000
	compare VAR_RESULT, FALSE
	goto_if_eq IcespireTown_EventScript_RoughneckNoMoney
	removemoney 2000
	setvar VAR_0x8005, MOVE_BODY_SLAM
	special ChooseMonForMoveTutor
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq IcespireTown_EventScript_RoughneckCancel
	msgbox IcespireTown_Text_RoughneckTaught, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckCancel::
	msgbox IcespireTown_Text_RoughneckDecline, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckNoMoney::
	msgbox IcespireTown_Text_RoughneckNoMoney, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_RoughneckLocked::
	msgbox IcespireTown_Text_RoughneckLocked, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Pro-Veil citizen — Beautiful Lie, moved to walkable tile
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_ProVeilCitizen::
	lock
	faceplayer
	msgbox IcespireTown_Text_CitizenPraise, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Ice Cream Stand vendor — warm, disconnected from politics
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_IceCreamVendor::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_ICESPIRE_FREE_CONE, IcespireTown_EventScript_IceCreamRegular
	msgbox IcespireTown_Text_IceCreamIntro, MSGBOX_DEFAULT
	setflag FLAG_SNOW_ICESPIRE_FREE_CONE
	msgbox IcespireTown_Text_IceCreamGiven, MSGBOX_DEFAULT
	release
	end

IcespireTown_EventScript_IceCreamRegular::
	msgbox IcespireTown_Text_IceCreamRegular, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ School kid — innocent cult chant
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_SchoolKid::
	lock
	faceplayer
	msgbox IcespireTown_Text_SchoolKidChant, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Doubter elder — memory-loss hint, late-game breadcrumb
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_DoubterElder::
	lock
	faceplayer
	msgbox IcespireTown_Text_DoubterElder, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Fanatic preacher — full-cult Veil true believer
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_FanaticPreacher::
	lock
	faceplayer
	msgbox IcespireTown_Text_FanaticPreacher, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Signs
@ ═══════════════════════════════════════════════════════════

IcespireTown_EventScript_GymSign::
	msgbox IcespireTown_Text_GymSign, MSGBOX_SIGN
	end

IcespireTown_EventScript_MartSign::
	msgbox IcespireTown_Text_MartSign, MSGBOX_SIGN
	end

IcespireTown_EventScript_PCSign::
	msgbox IcespireTown_Text_PCSign, MSGBOX_SIGN
	end

IcespireTown_EventScript_TownSign::
	msgbox IcespireTown_Text_TownSign, MSGBOX_SIGN
	end

@ ═══════════════════════════════════════════════════════════
@ Text
@ ═══════════════════════════════════════════════════════════

IcespireTown_Text_AsherF4Intro:
	.string "ASHER: Of course.\p"
	.string "Of COURSE you beat Silvan first.\p"
	.string "I've been up here for days.\n"
	.string "Days. I know his rotation, his\l"
	.string "leads, his switches. I was\l"
	.string "THIS close to -\p"
	.string "...\p"
	.string "You know what? Forget it.\p"
	.string "Everyone in this town keeps\n"
	.string "telling me how GRATEFUL I\l"
	.string "should be. For the cold. For\l"
	.string "the snow. For the DIRECTOR.\p"
	.string "I'm not grateful. I'm TIRED.\n"
	.string "And I'm taking it out on you.$"

IcespireTown_Text_AsherF4Defeat:
	.string "ASHER: No. No no no.$"

IcespireTown_Text_AsherF4PostBattle:
	.string "ASHER: ...\p"
	.string "I'm supposed to be stronger\n"
	.string "than this.\p"
	.string "I train. I PLAN. I study type\n"
	.string "charts until my eyes burn.\p"
	.string "And you just... show up.\p"
	.string "...\p"
	.string "Forget it. You didn't ask for\n"
	.string "my problems.\p"
	.string "Just - watch yourself out there,\n"
	.string "{PLAYER}. Something about this\l"
	.string "town isn't right. I can't tell\l"
	.string "you what. I just feel it.\p"
	.string "I'll see you at Gym 2.$"

IcespireTown_Text_AsherF4PostDefeat:
	.string "ASHER: Still here? Still winning?\p"
	.string "Whatever. I'm heading down to\n"
	.string "PINEGROVE. Try to keep up.$"

IcespireTown_Text_WideLensIntro:
	.string "WORN-OUT TRAINER: That gym nearly\n"
	.string "did me in.\p"
	.string "Silvan's team - the hail, the\n"
	.string "evasion, his PIPLUP's SPEED...\p"
	.string "My POKEMON just couldn't land\n"
	.string "a hit.\p"
	.string "Here. I picked this up on R2\n"
	.string "but I'm done battling for a\l"
	.string "while.\p"
	.string "Maybe it'll help you land more\n"
	.string "attacks than I did.$"

IcespireTown_Text_WideLensGiven:
	.string "{PLAYER} received the WIDE LENS!$"

IcespireTown_Text_WideLensPost:
	.string "WORN-OUT TRAINER: I think I'm\n"
	.string "going to retire and open a\l"
	.string "little cafe. Somewhere warm.$"

IcespireTown_Text_RoughneckIntro:
	.string "ROUGHNECK: Hey, you. Yeah, you.\p"
	.string "I've watched trainers come and\n"
	.string "go through this gym for years.\p"
	.string "The ones who make it big all\n"
	.string "have the same thing in common -\l"
	.string "they don't JUST rely on type\l"
	.string "charts.\p"
	.string "They hit hard. They hit dirty.\n"
	.string "They SCRAP.\p"
	.string "I didn't learn to fight in any\n"
	.string "gym. You want me to teach your\l"
	.string "POKEMON how to actually brawl?$"

IcespireTown_Text_RoughneckOffer:
	.string "ROUGHNECK: I can teach BODY SLAM\n"
	.string "for 2000 yen.\p"
	.string "Big heavy hit. Might paralyze.\n"
	.string "Changes fights.\p"
	.string "Interested?$"

IcespireTown_Text_RoughneckDecline:
	.string "ROUGHNECK: Think about it.\n"
	.string "Door's always open.$"

IcespireTown_Text_RoughneckNoMoney:
	.string "ROUGHNECK: You're short. Come\n"
	.string "back when your wallet isn't.$"

IcespireTown_Text_RoughneckLocked:
	.string "ROUGHNECK: Kid, come back with a\n"
	.string "badge. I don't waste lessons on\l"
	.string "trainers who can't prove they\l"
	.string "can take a hit.$"

IcespireTown_Text_RoughneckTaught:
	.string "ROUGHNECK: BODY SLAM taught. Now\n"
	.string "go hit something with it.$"

IcespireTown_Text_CitizenPraise:
	.string "CITIZEN: Beautiful day, isn't it?\p"
	.string "I moved here from SLATEPORT years\n"
	.string "ago. Couldn't stand the heat.\p"
	.string "Then DIRECTOR TYRELL and his\n"
	.string "researchers changed everything.\p"
	.string "This winter - it's a miracle.\n"
	.string "The air is clean, the POKEMON\l"
	.string "are thriving, crime is down.\p"
	.string "I don't know how he did it, but\n"
	.string "I trust him completely.\p"
	.string "DIRECTOR TYRELL saved BORALYSS.$"

IcespireTown_Text_IceCreamIntro:
	.string "VENDOR: Oh, a new face! Welcome\n"
	.string "to ICESPIRE, sweetheart.\p"
	.string "You look like you just climbed\n"
	.string "through the pass. First one's\l"
	.string "on the house.\p"
	.string "VANILLITE CREME - family recipe.\n"
	.string "Don't ask where the milk comes\l"
	.string "from.$"

IcespireTown_Text_IceCreamGiven:
	.string "{PLAYER} accepted a cone from\n"
	.string "the VENDOR.\p"
	.string "It tastes like a winter morning.$"

IcespireTown_Text_IceCreamRegular:
	.string "VENDOR: Come back any time,\n"
	.string "sweetheart.\p"
	.string "I don't care about DIRECTORS or\n"
	.string "BADGES or TEAMS.\p"
	.string "I just make cones, and the\n"
	.string "cold keeps them perfect.$"

IcespireTown_Text_SchoolKidChant:
	.string "SCHOOL KID: The snow is kind!\n"
	.string "The snow is clean!\p"
	.string "The DIRECTOR loves us!\n"
	.string "The DIRECTOR keeps us!\p"
	.string "I know the whole song! We sing\n"
	.string "it at recess.\p"
	.string "My teacher says if we're really\n"
	.string "good, the DIRECTOR might come\l"
	.string "visit our class again!$"

IcespireTown_Text_DoubterElder:
	.string "OLD WOMAN: Mmh. Another trainer.\p"
	.string "You know, I was born in this\n"
	.string "town. Long before the winter.\p"
	.string "It used to rain here. Real\n"
	.string "rain, the warm kind. My mother\l"
	.string "kept a garden by the south wall.\p"
	.string "I can't remember what was in\n"
	.string "it. I try, and the shape just...\l"
	.string "goes away.\p"
	.string "Everyone says the cold is a\n"
	.string "gift. I believe them.\p"
	.string "I just wish I could remember\n"
	.string "the garden.$"

IcespireTown_Text_FanaticPreacher:
	.string "MAN IN WHITE: Trainer! You walk\n"
	.string "in blessed air!\p"
	.string "Do you feel it? The HUSH. The\n"
	.string "PURITY. The DIRECTOR reached\l"
	.string "into the sky and FIXED it.\p"
	.string "Those who complain of the cold\n"
	.string "are complaining of a GIFT.\p"
	.string "Some say TEAM VEIL are just\n"
	.string "men. I say they are HANDS.\l"
	.string "The DIRECTOR'S hands.\p"
	.string "When KYUREM smiles upon us,\n"
	.string "all of BORALYSS will be free\l"
	.string "of summer forever.\p"
	.string "Praise the VEIL.$"

IcespireTown_Text_GymSign:
	.string "ICESHARD GYM\p"
	.string "LEADER: SILVAN\n"
	.string "KEEPER OF THE COLD$"

IcespireTown_Text_MartSign:
	.string "ICESPIRE POKEMON MART\n"
	.string "Warm hands. Cold prices.$"

IcespireTown_Text_PCSign:
	.string "ICESPIRE POKEMON CENTER\n"
	.string "Heal your team. Rest your soul.$"

IcespireTown_Text_TownSign:
	.string "ICESPIRE TOWN\p"
	.string "The first town kissed by the\n"
	.string "endless winter.$"
