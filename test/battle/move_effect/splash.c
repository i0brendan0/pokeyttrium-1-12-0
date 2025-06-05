#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_SPLASH) == EFFECT_SPLASH);
}

SINGLE_BATTLE_TEST("Splash does nothing if it's not raining")
{
    GIVEN {
        PLAYER(SPECIES_MAGIKARP);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SPLASH);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, player);
        MESSAGE("But nothing happened!");
    }
}

SINGLE_BATTLE_TEST("Splash does damage based off of the opponent's weight if it's raining", s16 damage)
{
    u16 opponentSpecies;
    PARAMETRIZE { opponentSpecies = SPECIES_WAILMER; }
    PARAMETRIZE { opponentSpecies = SPECIES_BUDEW; }
    GIVEN {
        PLAYER(SPECIES_MAGIKARP) { Moves(MOVE_SPLASH); }
        OPPONENT(opponentSpecies) { Ability(ABILITY_DRIZZLE);  }
    } WHEN {
        TURN { MOVE(player, MOVE_SPLASH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT(results[1].damage < results[0].damage);
    }
}
