#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_TECHNO_BLAST) == EFFECT_CHANGE_TYPE_ON_ITEM);
    ASSUME(GetMoveEffectArg_HoldEffect(MOVE_TECHNO_BLAST) == HOLD_EFFECT_DRIVE);
}

SINGLE_BATTLE_TEST("Techno Blast changes type depending on the drive the user holds")
{
    u16 species;
    u16 item;

    PARAMETRIZE { species = SPECIES_TYPHLOSION; item = ITEM_DOUSE_DRIVE; }
    PARAMETRIZE { species = SPECIES_BLASTOISE; item = ITEM_SHOCK_DRIVE; }
    PARAMETRIZE { species = SPECIES_VENUSAUR; item = ITEM_BURN_DRIVE; }
    PARAMETRIZE { species = SPECIES_DRATINI; item = ITEM_CHILL_DRIVE; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(item); }
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_TECHNO_BLAST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TECHNO_BLAST, player);
        HP_BAR(opponent);
        MESSAGE("It's super effective!");
    }
}

TO_DO_BATTLE_TEST("Judgement changes type depending on the plate the user holds");
TO_DO_BATTLE_TEST("Multi Attack changes type depending on the memory the user holds");
