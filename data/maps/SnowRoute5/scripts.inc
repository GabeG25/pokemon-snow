SnowRoute5_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════
@ R5 Ironfrost Cave — Gauntlet
@ 2 trainers + 4 Veil grunts (named) + Crash F7 boss
@ All grunts are true believers who love the winter
@ Escalating ideology, Director Tyrell reverence
@ ═══════════════════════════════════════════════════════════

SnowRoute5_EventScript_Knox::
	trainerbattle_single TRAINER_SNOW_R5_1_KNOX, SnowRoute5_Text_KnoxIntro, SnowRoute5_Text_KnoxDefeat
	msgbox SnowRoute5_Text_KnoxPostBattle, MSGBOX_AUTOCLOSE
	end

SnowRoute5_EventScript_Lina::
	trainerbattle_single TRAINER_SNOW_R5_2_LINA, SnowRoute5_Text_LinaIntro, SnowRoute5_Text_LinaDefeat
	msgbox SnowRoute5_Text_LinaPostBattle, MSGBOX_AUTOCLOSE
	end

@ ===== Veil Grunt Bran (R5-3) — explains the "mining operation" =====
SnowRoute5_EventScript_Grunt1::
	trainerbattle_single TRAINER_SNOW_R5_3_GRUNT, SnowRoute5_Text_BranIntro, SnowRoute5_Text_BranDefeat
	msgbox SnowRoute5_Text_BranPostBattle, MSGBOX_AUTOCLOSE
	end

@ ===== Veil Grunt Nyla (R5-4) — the true believer speech =====
SnowRoute5_EventScript_Grunt2::
	trainerbattle_single TRAINER_SNOW_R5_4_GRUNT, SnowRoute5_Text_NylaIntro, SnowRoute5_Text_NylaDefeat
	msgbox SnowRoute5_Text_NylaPostBattle, MSGBOX_AUTOCLOSE
	end

@ ===== Veil Grunt Orin (R5-5) — Director reverence =====
SnowRoute5_EventScript_Grunt3::
	trainerbattle_single TRAINER_SNOW_R5_5_GRUNT, SnowRoute5_Text_OrinIntro, SnowRoute5_Text_OrinDefeat
	msgbox SnowRoute5_Text_OrinPostBattle, MSGBOX_AUTOCLOSE
	end

@ ===== Veil Grunt Lira (R5-6) — angry zealot =====
SnowRoute5_EventScript_Grunt4::
	trainerbattle_single TRAINER_SNOW_R5_6_GRUNT, SnowRoute5_Text_LiraIntro, SnowRoute5_Text_LiraDefeat
	msgbox SnowRoute5_Text_LiraPostBattle, MSGBOX_AUTOCLOSE
	end

@ ===== Crash F7 boss — Veil Admin, true-believer-devoted =====
SnowRoute5_EventScript_Crash::
	lock
	faceplayer
	goto_if_set FLAG_SNOW_BEAT_F7_CRASH, SnowRoute5_EventScript_CrashDefeated
	msgbox SnowRoute5_Text_CrashIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SNOW_F7_CRASH, SnowRoute5_Text_CrashDefeat
	setflag FLAG_SNOW_BEAT_F7_CRASH
	msgbox SnowRoute5_Text_CrashPostBattle, MSGBOX_DEFAULT
	release
	end

SnowRoute5_EventScript_CrashDefeated::
	msgbox SnowRoute5_Text_CrashPostDefeat, MSGBOX_DEFAULT
	release
	end

@ ═══════════════════════════════════════════════════════════
@ Route trainer text
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_KnoxIntro:
	.string "I mine this cave for a living.\n"
	.string "These rocks don't give up easy -\n"
	.string "neither will my Pokemon!$"

SnowRoute5_Text_KnoxDefeat:
	.string "Hah! A good swing!$"

SnowRoute5_Text_KnoxPostBattle:
	.string "Watch yourself further in.\n"
	.string "Those Team Veil folks have\l"
	.string "been acting strange lately.$"

SnowRoute5_Text_LinaIntro:
	.string "A trainer! Thank goodness.\n"
	.string "It's been so quiet in here.$"

SnowRoute5_Text_LinaDefeat:
	.string "Oh my!$"

SnowRoute5_Text_LinaPostBattle:
	.string "I study the cave's geology.\p"
	.string "Team Veil has been 'mining' for\n"
	.string "months, but I've never seen\l"
	.string "them haul anything out...$"

@ ═══════════════════════════════════════════════════════════
@ BRAN — R5-3 — First Veil grunt in cave
@ Cover story: mining operation for Director Tyrell's research
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_BranIntro:
	.string "BRAN: Oh, it's you.\p"
	.string "I heard about the trainer who\n"
	.string "made it past Kael on R3.\p"
	.string "Look - most of us here aren't\n"
	.string "looking for a fight.\p"
	.string "We're just miners. Ironfrost\n"
	.string "Cave has rare minerals that\l"
	.string "DIRECTOR TYRELL needs for his\l"
	.string "weather research.\p"
	.string "You know, the research that\n"
	.string "gave us all this beautiful\l"
	.string "winter?\p"
	.string "You're in our work zone, kid.\n"
	.string "Back off or battle.$"

SnowRoute5_Text_BranDefeat:
	.string "BRAN: Tch - tougher than you\n"
	.string "look.$"

SnowRoute5_Text_BranPostBattle:
	.string "BRAN: Fine. Pass through.\p"
	.string "But stay on the main corridor,\n"
	.string "understand?\p"
	.string "The side tunnels are dangerous -\n"
	.string "and the DIRECTOR'S research is\l"
	.string "sensitive.$"

@ ═══════════════════════════════════════════════════════════
@ NYLA — R5-4 — The true believer speech
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_NylaIntro:
	.string "NYLA: Another outsider poking\n"
	.string "around where they shouldn't be.\p"
	.string "Do you even UNDERSTAND what\n"
	.string "we've built here?\p"
	.string "The endless winter isn't a\n"
	.string "curse. It's a MIRACLE.\p"
	.string "Pokemon are happier. People\n"
	.string "are grateful. The air is clean.\l"
	.string "Crime is down.\p"
	.string "DIRECTOR TYRELL saved Boralyss\n"
	.string "from the chaos of seasons.\p"
	.string "And you're in here, in our\n"
	.string "mining operation, threatening\l"
	.string "to wreck everything he built.\p"
	.string "I won't let you pass without\n"
	.string "a fight.$"

SnowRoute5_Text_NylaDefeat:
	.string "NYLA: Impossible...$"

SnowRoute5_Text_NylaPostBattle:
	.string "NYLA: You don't understand\n"
	.string "what you're doing.\p"
	.string "When you finally see the\n"
	.string "DIRECTOR'S full vision -\p"
	.string "- you'll wish you'd stayed\n"
	.string "out of our way.$"

@ ═══════════════════════════════════════════════════════════
@ ORIN — R5-5 — Director reverence, partnered with Lira
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_OrinIntro:
	.string "ORIN: Stop right there, outsider.\p"
	.string "Bran and Nyla were soft on you.\n"
	.string "I won't be.\p"
	.string "My partner LIRA is just ahead -\n"
	.string "together we protect the deep\l"
	.string "tunnels where the DIRECTOR\l"
	.string "himself comes to observe.\p"
	.string "He trusts us, {PLAYER}. Do you\n"
	.string "understand how sacred that is?\p"
	.string "Let's see what your Pokemon\n"
	.string "can do against TRUE loyalty.$"

SnowRoute5_Text_OrinDefeat:
	.string "ORIN: No... I failed him.$"

SnowRoute5_Text_OrinPostBattle:
	.string "ORIN: Lira is next. She's faster\n"
	.string "than me. Angrier than me.\p"
	.string "Don't expect her to be as\n"
	.string "merciful.\p"
	.string "(...Though I shouldn't have\n"
	.string "been merciful at all.\l"
	.string "Forgive me, DIRECTOR.)$"

@ ═══════════════════════════════════════════════════════════
@ LIRA — R5-6 — Angry zealot, final grunt before Crash
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_LiraIntro:
	.string "LIRA: YOU.\p"
	.string "You beat ORIN?!\p"
	.string "Do you have any IDEA what you're\n"
	.string "doing? What you're INTERRUPTING?\p"
	.string "DIRECTOR TYRELL gave us PURPOSE.\n"
	.string "He gave us a world where Pokemon\l"
	.string "don't have to suffer hot summers\l"
	.string "or droughts or wildfire.\p"
	.string "He gave us a perfect, endless,\n"
	.string "beautiful WINTER.\p"
	.string "And you - some random CHILD -\n"
	.string "are trampling through our sacred\l"
	.string "work because, what, you want a\l"
	.string "gym badge?\p"
	.string "I'll scatter your team across\n"
	.string "this cave!$"

SnowRoute5_Text_LiraDefeat:
	.string "LIRA: AAARGH!$"

SnowRoute5_Text_LiraPostBattle:
	.string "LIRA: You... you...\p"
	.string "CRASH is up ahead. He's our\n"
	.string "ADMIN. He'll handle you.\p"
	.string "You think four grunts is a lot?\n"
	.string "Wait until you face someone\l"
	.string "who actually reports to the\l"
	.string "DIRECTOR in person.\p"
	.string "(Get him, CRASH. Don't let this\n"
	.string "one pass.)$"

@ ═══════════════════════════════════════════════════════════
@ CRASH F7 — Admin boss, "loud, devoted, not evil"
@ ═══════════════════════════════════════════════════════════

SnowRoute5_Text_CrashIntro:
	.string "CRASH: HEY! YOU!\p"
	.string "Did you really just walk through\n"
	.string "FOUR of my grunts?!\p"
	.string "Four people, {PLAYER}! FOUR!\p"
	.string "Bran - solid miner. Nyla - one\n"
	.string "of our best speakers. Orin and\l"
	.string "Lira - a GREAT tag team!\p"
	.string "You went through them like they\n"
	.string "were nothing!\p"
	.string "Look, I don't know who you are\n"
	.string "or what you want, but I can't\l"
	.string "let you embarrass the DIRECTOR\l"
	.string "like this.\p"
	.string "The name's CRASH. Team Veil\n"
	.string "Admin. Hand-picked by DIRECTOR\l"
	.string "TYRELL himself.\p"
	.string "I don't LOSE.\p"
	.string "Let's GO!$"

SnowRoute5_Text_CrashDefeat:
	.string "CRASH: WHAT?!$"

SnowRoute5_Text_CrashPostBattle:
	.string "CRASH: I... I LOST?\p"
	.string "To a KID?!\p"
	.string "No. No no no. This isn't\n"
	.string "supposed to happen.\p"
	.string "I've trained with TYRELL\n"
	.string "himself. He said I had the\l"
	.string "strongest team of the admins.\l"
	.string "Stronger than Mika. Stronger\l"
	.string "than XENON!\p"
	.string "And you just -\p"
	.string "...\p"
	.string "Fine. You got me. Walk on\n"
	.string "through. Go get your badge in\l"
	.string "IRONFROST CITY.\p"
	.string "But this isn't over, {PLAYER}.\n"
	.string "Not even close.\p"
	.string "I'll be there when the DIRECTOR\n"
	.string "reveals his full plan. And\l"
	.string "on that day - you'll wish you\l"
	.string "had never crossed me.$"

SnowRoute5_Text_CrashPostDefeat:
	.string "CRASH: Still here, huh?\p"
	.string "I'm not gonna fight you again.\n"
	.string "I need to train. HARD.\p"
	.string "Next time we meet, {PLAYER} -\n"
	.string "it won't be in some cave.$"
