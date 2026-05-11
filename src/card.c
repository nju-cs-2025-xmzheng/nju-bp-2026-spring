#include "card.h"
#include "game.h"
#include <assert.h>

void strike_effect(Player *player, Enemy *enemy) {
    deal_damage(&enemy->base, 6);
    return;
}

void defend_effect(Player *player, Enemy *enemy) {
    player->base.block += 5;
    return;
}

void bloodletting_effect(Player *player, Enemy *enemy) {
    deal_damage(&player->base, 3);
    player->energy += 1;
    return;
}

void play_card(CardType type, Player *player, Enemy *enemy) {
    assert(type >= 0 && type < CARD_TYPE_COUNT);
    Card *card = &cards[type];
    assert(player->energy >= card->cost);
    player->energy -= card->cost;
    card->effect(player, enemy);
}
