FacilityAlpha_MapScripts::
	.byte 0

@ ═══════════════════════════════════════════════════════════════
@ FACILITY ALPHA — F27 TYRELL #2 + KYUREM DEATH CUTSCENE
@ ═══════════════════════════════════════════════════════════════
@ Per v17: Tyrell dies at the end of F27. Kyurem (held at the
@ facility) turns on him after the fight. Player witnesses this
@ in a scripted cutscene, then FLAG_SNOW_BEAT_F27_TYRELL is set,
@ which (a) unlocks the post-game Kyurem encounter in Ironfrost
@ Cave B2B3 and (b) advances the level cap cascade per caps.c.
@
@ This is a STUB implementation: Facility Alpha is a single-room
@ map reusing Devon Corp 2F layout. Full v17 §18 Alpha design
@ calls for 4 floors, 31 grunts, and F24 Crash + F25 Mika + F26
@ Xenon gating F27. Those are CEO-creative work (DECISIONS.md
@ grunt-team locks). This stub gives the story a working endpoint
@ until the full facility ships.

FacilityAlpha_EventScript_Tyrell::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox FacilityAlpha_Text_TyrellDesperate, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SNOW_F27_TYRELL, FacilityAlpha_Text_TyrellDefeat
	msgbox FacilityAlpha_Text_TyrellGrappling, MSGBOX_DEFAULT
	closemessage
	@ Death cutscene: fade to black, Kyurem roars, Tyrell screams offscreen.
	playse SE_BOO
	delay 30
	fadescreenspeed FADE_TO_BLACK, 12
	delay 60
	msgbox FacilityAlpha_Text_KyuremTurns, MSGBOX_DEFAULT
	closemessage
	delay 60
	msgbox FacilityAlpha_Text_TyrellEnd, MSGBOX_DEFAULT
	closemessage
	delay 60
	setflag FLAG_SNOW_BEAT_F27_TYRELL
	@ Remove Tyrell's object — his body is gone when player fades in
	removeobject 1
	fadescreenspeed FADE_FROM_BLACK, 12
	delay 30
	msgbox FacilityAlpha_Text_Aftermath, MSGBOX_DEFAULT
	closemessage
	@ Warp player out to Dragonforge — facility is collapsing
	warp MAP_DRAGONFORGE_CITY, 255, 25, 4
	waitstate
	releaseall
	end

FacilityAlpha_Text_TyrellDesperate:
	.string "TYRELL: {PLAYER}.\p"
	.string "You shouldn't have come this\n"
	.string "far.\p"
	.string "The operation is almost\n"
	.string "complete. BORALYSS will accept\l"
	.string "my winter as inevitable.\p"
	.string "I will not watch years of\n"
	.string "work unmade by a child and\l"
	.string "their starter.\p"
	.string "KYUREM. SHOW THEM.$"

FacilityAlpha_Text_TyrellDefeat:
	.string "TYRELL: This isn't...\n"
	.string "possible.$"

FacilityAlpha_Text_TyrellGrappling:
	.string "TYRELL: No. No no no.\p"
	.string "I was right. I know I was\n"
	.string "right.\p"
	.string "The region NEEDED this. I was\n"
	.string "giving them strength. Forging\l"
	.string "them through hardship.\p"
	.string "You don't understand what\n"
	.string "you've stopped.\p"
	.string "...KYUREM. Get up.\n"
	.string "Get up, I command you!$"

FacilityAlpha_Text_KyuremTurns:
	.string "KYUREM rose.\p"
	.string "But it did not look at you.$"

FacilityAlpha_Text_TyrellEnd:
	.string "TYRELL: Wait.\n"
	.string "Wait, I -\p"
	.string "The roar filled the facility.\n"
	.string "And then there was nothing\l"
	.string "left of TYRELL to hear it.$"

FacilityAlpha_Text_Aftermath:
	.string "The chamber is empty.\p"
	.string "KYUREM has gone. Facility\n"
	.string "ALPHA is venting. The air\l"
	.string "is already warming.\p"
	.string "Better to leave.$"
