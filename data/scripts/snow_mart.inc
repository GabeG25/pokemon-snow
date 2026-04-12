@ Snow Poké Mart — Universal badge-gated inventory (v17 §17)
@ Included from event_scripts.s. Referenced by all Snow Pokémon Center clerks.
@ Badge ceiling at 4 (18 items). No additions Badges 5-8.

Snow_PokeMart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_BADGE04_GET, Snow_PokeMart_EventScript_Badge4
	goto_if_set FLAG_BADGE03_GET, Snow_PokeMart_EventScript_Badge3
	goto_if_set FLAG_BADGE02_GET, Snow_PokeMart_EventScript_Badge2
	goto_if_set FLAG_BADGE01_GET, Snow_PokeMart_EventScript_Badge1
	pokemart Snow_PokeMart_Items_Badge0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Snow_PokeMart_EventScript_Badge1::
	pokemart Snow_PokeMart_Items_Badge1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Snow_PokeMart_EventScript_Badge2::
	pokemart Snow_PokeMart_Items_Badge2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Snow_PokeMart_EventScript_Badge3::
	pokemart Snow_PokeMart_Items_Badge3
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Snow_PokeMart_EventScript_Badge4::
	pokemart Snow_PokeMart_Items_Badge4
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

@ Badge 0 — Game Start (3 items)
	.align 2
Snow_PokeMart_Items_Badge0:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	pokemartlistend

@ Badge 1 — Post-Silvan (total 7)
	.align 2
Snow_PokeMart_Items_Badge1:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_ICE_HEAL
	pokemartlistend

@ Badge 2 — Post-Cedar (total 12)
	.align 2
Snow_PokeMart_Items_Badge2:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARLYZ_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	pokemartlistend

@ Badge 3 — Post-Copper (total 15)
	.align 2
Snow_PokeMart_Items_Badge3:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARLYZ_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ Badge 4 — Post-Fran (total 18) — MART CEILING
	.align 2
Snow_PokeMart_Items_Badge4:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_PARLYZ_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ ═══════════════════════════════════════════════════
@ Frostbreak Lodge Shop (v17 §16) — 8 items, no badge gate
@ ═══════════════════════════════════════════════════

Snow_FrostbreakLodge_EventScript_Clerk::
	lock
	faceplayer
	message Snow_FrostbreakLodge_Text_Welcome
	waitmessage
	pokemart Snow_FrostbreakLodge_Items
	msgbox Snow_FrostbreakLodge_Text_StaySafe, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_FrostbreakLodge_Items:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_LAVA_COOKIE
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_LUM_BERRY
	.2byte ITEM_LEPPA_BERRY
	.2byte ITEM_POKE_DOLL
	pokemartlistend

Snow_FrostbreakLodge_Text_Welcome:
	.string "Welcome to Frostbreak Lodge!\n"
	.string "We carry specialty supplies\l"
	.string "for the mountain trails.$"

Snow_FrostbreakLodge_Text_StaySafe:
	.string "Stay safe out there.\n"
	.string "The mountains don't forgive\l"
	.string "the unprepared.$"

@ ═══════════════════════════════════════════════════
@ Dragonforge Department Store (v17 §16) — 108 items, 5 floors + rooftop
@ Badge 6 gate on entrance
@ ═══════════════════════════════════════════════════

@ 2F — Poké Mart Plus (13 items)
Snow_DeptStore_2F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_2F_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_2F_Items:
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_MAX_REVIVE
	.2byte ITEM_MAX_ELIXIR
	.2byte ITEM_PP_UP
	pokemartlistend

@ 3F — TM Shop (6 TMs)
Snow_DeptStore_3F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_3F_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_3F_Items:
	.2byte ITEM_TM29
	.2byte ITEM_TM30
	.2byte ITEM_TM31
	.2byte ITEM_TM32
	.2byte ITEM_TM33
	.2byte ITEM_TM34
	pokemartlistend

@ 4F — Battle Items: Clerk A (east) — Held items + weather rocks + mints (35 items)
Snow_DeptStore_4F_EventScript_ClerkA::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_4F_Items_ClerkA
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_4F_Items_ClerkA:
	.2byte ITEM_MUSCLE_BAND
	.2byte ITEM_WISE_GLASSES
	.2byte ITEM_METRONOME
	.2byte ITEM_QUICK_CLAW
	.2byte ITEM_FOCUS_SASH
	.2byte ITEM_EVIOLITE
	.2byte ITEM_AIR_BALLOON
	.2byte ITEM_RED_CARD
	.2byte ITEM_WHITE_HERB
	.2byte ITEM_POWER_HERB
	.2byte ITEM_MENTAL_HERB
	.2byte ITEM_ICY_ROCK
	.2byte ITEM_HEAT_ROCK
	.2byte ITEM_DAMP_ROCK
	.2byte ITEM_SMOOTH_ROCK
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_NAIVE_MINT
	pokemartlistend

@ 4F — Battle Items: Clerk B (west) — Type gems + berries (38 items)
Snow_DeptStore_4F_EventScript_ClerkB::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_4F_Items_ClerkB
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_4F_Items_ClerkB:
	.2byte ITEM_NORMAL_GEM
	.2byte ITEM_FIRE_GEM
	.2byte ITEM_WATER_GEM
	.2byte ITEM_ELECTRIC_GEM
	.2byte ITEM_GRASS_GEM
	.2byte ITEM_ICE_GEM
	.2byte ITEM_FIGHTING_GEM
	.2byte ITEM_POISON_GEM
	.2byte ITEM_GROUND_GEM
	.2byte ITEM_FLYING_GEM
	.2byte ITEM_PSYCHIC_GEM
	.2byte ITEM_BUG_GEM
	.2byte ITEM_ROCK_GEM
	.2byte ITEM_GHOST_GEM
	.2byte ITEM_DRAGON_GEM
	.2byte ITEM_DARK_GEM
	.2byte ITEM_STEEL_GEM
	.2byte ITEM_FAIRY_GEM
	.2byte ITEM_OCCA_BERRY
	.2byte ITEM_PASSHO_BERRY
	.2byte ITEM_WACAN_BERRY
	.2byte ITEM_RINDO_BERRY
	.2byte ITEM_YACHE_BERRY
	.2byte ITEM_CHOPLE_BERRY
	.2byte ITEM_KEBIA_BERRY
	.2byte ITEM_SHUCA_BERRY
	.2byte ITEM_COBA_BERRY
	.2byte ITEM_PAYAPA_BERRY
	.2byte ITEM_TANGA_BERRY
	.2byte ITEM_CHARTI_BERRY
	.2byte ITEM_KASIB_BERRY
	.2byte ITEM_HABAN_BERRY
	.2byte ITEM_COLBUR_BERRY
	.2byte ITEM_BABIRI_BERRY
	.2byte ITEM_CHILAN_BERRY
	.2byte ITEM_ROSELI_BERRY
	.2byte ITEM_SITRUS_BERRY
	.2byte ITEM_LUM_BERRY
	pokemartlistend

@ 5F — Evolution & Specialty (13 items)
Snow_DeptStore_5F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_5F_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_5F_Items:
	.2byte ITEM_FIRE_STONE
	.2byte ITEM_WATER_STONE
	.2byte ITEM_THUNDER_STONE
	.2byte ITEM_LEAF_STONE
	.2byte ITEM_MOON_STONE
	.2byte ITEM_SHINY_STONE
	.2byte ITEM_SUN_STONE
	.2byte ITEM_DAWN_STONE
	.2byte ITEM_DUSK_STONE
	.2byte ITEM_ICE_STONE
	.2byte ITEM_LINKING_CORD
	.2byte ITEM_UPGRADE
	.2byte ITEM_AMULET_COIN
	pokemartlistend

@ Rooftop — Vending (3 items)
Snow_DeptStore_Roof_EventScript_Vending::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Snow_DeptStore_Roof_Items
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Snow_DeptStore_Roof_Items:
	.2byte ITEM_FRESH_WATER
	.2byte ITEM_SODA_POP
	.2byte ITEM_LEMONADE
	pokemartlistend
