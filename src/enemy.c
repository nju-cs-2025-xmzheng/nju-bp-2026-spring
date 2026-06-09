#include "enemy.h"

EnemyIntent enemy_intents[INTENT_COUNT] = {
    {"adds 6 blocks to itself", intent_def_6_effect},
    {"deals 8 damage to the player", intent_atk_8_effect},
    {"deals 5 damage to the player and adds 10 blocks to itself",
     intent_atk_5_def_10_effect},
    {"deals 16 damage to the player", intent_atk_16_effect},
    {"adds 10 blocks to itself", intent_def_10_effect},
    {"deals 12 damage to the player", intent_atk_12_effect},
};
