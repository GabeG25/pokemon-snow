#ifndef GUARD_CONSTANTS_TMS_HMS_H
#define GUARD_CONSTANTS_TMS_HMS_H

// Snow TM mapping (v17 §11): 51 TMs + 4 HMs
#define FOREACH_TM(F) \
    F(WORK_UP) \
    F(HONE_CLAWS) \
    F(ICY_WIND) \
    F(RETURN) \
    F(PROTECT) \
    F(TOXIC) \
    F(GIGA_DRAIN) \
    F(FACADE) \
    F(BRICK_BREAK) \
    F(FLASH_CANNON) \
    F(REFLECT) \
    F(LIGHT_SCREEN) \
    F(ICE_BEAM) \
    F(ACROBATICS) \
    F(DAZZLING_GLEAM) \
    F(CALM_MIND) \
    F(WILL_O_WISP) \
    F(REST) \
    F(SHADOW_BALL) \
    F(SCALD) \
    F(TAUNT) \
    F(BULK_UP) \
    F(POISON_JAB) \
    F(OVERHEAT) \
    F(U_TURN) \
    F(VOLT_SWITCH) \
    F(DRAGON_CLAW) \
    F(HIDDEN_POWER) \
    F(DRAGON_PULSE) \
    F(THUNDERBOLT) \
    F(DARK_PULSE) \
    F(SLUDGE_BOMB) \
    F(SWORDS_DANCE) \
    F(HYPER_BEAM) \
    F(PSYCHIC) \
    F(EARTHQUAKE) \
    F(X_SCISSOR) \
    F(ENERGY_BALL) \
    F(ROCK_SLIDE) \
    F(IRON_HEAD) \
    F(FIRE_BLAST) \
    F(SOLAR_BEAM) \
    F(FLAMETHROWER) \
    F(THUNDER) \
    F(SUNNY_DAY) \
    F(RAIN_DANCE) \
    F(HAIL) \
    F(DRAIN_PUNCH) \
    F(GIGA_IMPACT) \
    F(BLIZZARD) \
    F(STONE_EDGE)

#define FOREACH_HM(F) \
    F(CUT) \
    F(FLY) \
    F(SURF) \
    F(STRENGTH) \
    F(FLASH) \
    F(ROCK_SMASH) \
    F(WATERFALL) \
    F(DIVE)

#define FOREACH_TMHM(F) \
    FOREACH_TM(F) \
    FOREACH_HM(F)

#endif
