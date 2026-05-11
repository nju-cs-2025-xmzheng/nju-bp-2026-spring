#ifndef CARD_H
#define CARD_H

#include "game.h"

typedef struct {
    char name[20];
    int cost;
    void (*effect)(Player *player, Enemy *enemy);
} Card;

typedef enum {
    CARD_STRIKE,
    CARD_DEFEND,
    CARD_BLOODLETTING,
    CARD_TYPE_COUNT
} CardType;

void strike_effect(Player *player, Enemy *enemy);
void defend_effect(Player *player, Enemy *enemy);
void bloodletting_effect(Player *player, Enemy *enemy);

Card cards[CARD_TYPE_COUNT] = {
    {"Strike", 1, strike_effect},
    {"Defend", 1, defend_effect},
    {"Bloodletting", 0, bloodletting_effect},
};

void play_card(CardType type, Player *player, Enemy *enemy);

#endif
