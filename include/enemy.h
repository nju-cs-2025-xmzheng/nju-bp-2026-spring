#ifndef ENEMY_H
#define ENEMY_H

#include "game.h"

typedef struct {
    char description[100];
    void (*effect)(Player *player, Enemy *enemy);
} EnemyIntent;

extern EnemyIntent enemy_intents[INTENT_COUNT];

inline static void intent_def_6_effect(Player *player, Enemy *enemy) {
    enemy->base.block += 6;
}
inline static void intent_atk_8_effect(Player *player, Enemy *enemy) {
    player->base.health -= 8;
}
inline static void intent_atk_5_def_10_effect(Player *player, Enemy *enemy) {
    player->base.health -= 5;
    enemy->base.block += 10;
}
inline static void intent_atk_16_effect(Player *player, Enemy *enemy) {
    player->base.health -= 16;
}
inline static void intent_def_10_effect(Player *player, Enemy *enemy) {
    enemy->base.block += 10;
}
inline static void intent_atk_12_effect(Player *player, Enemy *enemy) {
    player->base.health -= 12;
}

#endif
