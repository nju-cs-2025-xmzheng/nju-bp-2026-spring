#include "card.h"
#include "game.h"
#include "sts_io.h"
#include <assert.h>
#include <stdlib.h>

void strike_effect(Card *self, Deck *deck, Player *player, Enemy *enemy) {
    deal_damage(&enemy->base, 6);
    sts_println("You attack for 6 damage!");
}

void defend_effect(Card *self, Deck *deck, Player *player, Enemy *enemy) {
    player->base.block += 5;
    sts_println("You gain 5 block!");
}

void bloodletting_effect(Card *self, Deck *deck, Player *player, Enemy *enemy) {
    player->base.health -= 3;
    if (player->base.health < 0)
        player->base.health = 0;
    sts_println("You lose 3 health and gain 1 energy!");
}

void rampage_effect(Card *self, Deck *deck, Player *player, Enemy *enemy) {
    int damage = self->data[0];
    deal_damage(&enemy->base, damage);
    self->data[0] += 5;
    sts_printf("You attack for %d damage!\n", damage);
}

Card cards[CARD_TYPE_COUNT] = {
    {"Strike", .cost = 1, strike_effect, card_data_empty,
     "Costs 1 Energy; deals 6 Damage to the enemy"},
    {"Defend", .cost = 1, defend_effect, card_data_empty,
     "Costs 1 Energy; gains 5 Block to yourself"},
    {"Bloodletting", .cost = -1, bloodletting_effect, card_data_empty,
     "Gains 1 Energy; loses 3 Health"},
    {"Rampage", .cost = 1, rampage_effect, card_data(8),
     "Costs 1 Energy; deals % Damage to the enemy; increases damage by 5 each "
     "time it's played"},
};

void print_card(Card *card) {
    int *data = card->data;
    for (char *p = card->description; *p; p++) {
        if (*p == '%')
            sts_print(*data++);
        else
            sts_print(*p);
    }
}

void play_card(Card *card, Deck *deck, Player *player, Enemy *enemy) {
    assert(player->energy >= card->cost);
    player->energy -= card->cost;
    card->effect(card, deck, player, enemy);
}
