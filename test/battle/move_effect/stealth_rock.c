#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_STEALTH_ROCK) == EFFECT_STEALTH_ROCK);
}

SINGLE_BATTLE_TEST("Stealth Rock damage on switch in based on typing")
{
    u32 species, divisor;

    PARAMETRIZE { species = SPECIES_HO_OH; divisor = 2; } // Fire / Flying
    PARAMETRIZE { species = SPECIES_PIDGEOT; divisor = 4; } // Flying
    PARAMETRIZE { species = SPECIES_RATICATE; divisor = 8; } // Normal dmg
    PARAMETRIZE { species = SPECIES_GOLEM; divisor = 16; } // Ground not very effective
    PARAMETRIZE { species = SPECIES_STEELIX; divisor = 32; } // Ground/Steel not very effective

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_STEALTH_ROCK); }
        TURN { SWITCH(opponent, 1); }
    } SCENE {
        s32 maxHP = GetMonData(&OPPONENT_PARTY[1], MON_DATA_MAX_HP);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STEALTH_ROCK, player);
        // MESSAGE("2 sent out species!");
        HP_BAR(opponent, damage: maxHP / divisor);
    }
}

SINGLE_BATTLE_TEST("Stealth Rock damages the correct pokemon when Eject Button is triggered")
{
    GIVEN {
        PLAYER(SPECIES_METAPOD) { Item(ITEM_EJECT_BUTTON); }
        PLAYER(SPECIES_METAPOD);
        OPPONENT(SPECIES_JOLTEON);
    } WHEN {
        TURN { MOVE(opponent, MOVE_STEALTH_ROCK); MOVE(player, MOVE_HARDEN); }
        TURN { MOVE(opponent, MOVE_QUICK_ATTACK); MOVE(player, MOVE_HARDEN); SEND_OUT(player, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STEALTH_ROCK, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HARDEN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, opponent);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_HARDEN, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        SEND_IN_MESSAGE("Metapod");
        HP_BAR(player);
    } THEN {
        EXPECT_EQ(opponent->hp, opponent->maxHP);
    }
}

DOUBLE_BATTLE_TEST("Stealth Rock damages the correct pokemon when Eject Button is triggered in double battle")
{
    GIVEN {
        PLAYER(SPECIES_METAPOD) { Item(ITEM_EJECT_BUTTON); }
        PLAYER(SPECIES_METAPOD) { Item(ITEM_EJECT_BUTTON); }
        PLAYER(SPECIES_METAPOD);
        OPPONENT(SPECIES_JOLTEON);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_STEALTH_ROCK); MOVE(opponentRight, MOVE_SCRATCH, target: playerLeft); SEND_OUT(playerLeft, 2); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STEALTH_ROCK, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponentRight);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, playerLeft);
        SEND_IN_MESSAGE("Metapod");
        HP_BAR(playerLeft);
    } THEN {
        EXPECT_EQ(opponentLeft->hp, opponentLeft->maxHP);
    }
}

SINGLE_BATTLE_TEST("Stealth Rock damage terastalized mons with the correct amount of damage", s16 damage)
{
    u32 tera;

    PARAMETRIZE { tera = FALSE; }
    PARAMETRIZE { tera = TRUE; }

    GIVEN {
        PLAYER(SPECIES_CHARIZARD) { TeraType(TYPE_NORMAL); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        if (tera == TRUE)
            TURN { MOVE(opponent, MOVE_STEALTH_ROCK); MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_TERA); }
        else
            TURN { MOVE(opponent, MOVE_STEALTH_ROCK); MOVE(player, MOVE_CELEBRATE); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STEALTH_ROCK, opponent);
        HP_BAR(player);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}
