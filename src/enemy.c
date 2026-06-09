#include "enemy.h"

EnemyIntent enemy_intents[INTENT_COUNT] = {
    {"Add 6 blocks to self", intent_def_6_effect},
    {"Deal 8 damage to player", intent_atk_8_effect},
    {"Deal 5 damage to player and add 10 blocks to self",
     intent_atk_5_def_10_effect},
    {"Deal 16 damage to player", intent_atk_16_effect},
    {"Add 10 blocks to self", intent_def_10_effect},
    {"Deal 12 damage to player", intent_atk_12_effect},
};
