#include "card.h"
#include "game.h"
#include "sts_io.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
    sts_println("You attack for %d damage!", damage);
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

void init_deck(Deck *deck, CardType *card_types, int size) {
    deck->cards = malloc(sizeof(Card) * size);
    deck->status = malloc(sizeof(CardStatus) * size);
    deck->size = size;
    for (int i = 0; i < size; i++) {
        deck->cards[i] = cards[card_types[i]];
        Card *template = &cards[card_types[i]];
        if (template->data) {
            deck->cards[i].data = malloc(sizeof(int) * template->data_cnt);
            memcpy(deck->cards[i].data, template->data,
                   sizeof(int) * template->data_cnt);
        }
        deck->status[i] = CARD_IN_DRAW_PILE;
    }
    deck->cards_in_draw_pile = size;
    deck->cards_in_hand = 0;
    deck->cards_in_discard = 0;
}

void draw_cards(Deck *deck, int count) {
    assert(deck->size >= count);
    for (int i = 0; count > 0; i++) {
        if (deck->cards_in_draw_pile == 0) {
            shuffle_deck(deck);
        }
        if (i >= deck->size) {
            i = 0;
        }
        if (deck->status[i] == CARD_IN_DRAW_PILE) {
            deck->status[i] = CARD_IN_HAND;
            deck->cards_in_draw_pile--;
            deck->cards_in_hand++;
            count--;
        }
    }
}

Card *find_card_in_hand(Deck *deck, int index) {
    assert(index >= 0 && index < deck->cards_in_hand);
    for (int i = 0, j = 0; i < deck->size; i++) {
        if (deck->status[i] == CARD_IN_HAND) {
            if (j++ == index) {
                return &deck->cards[i];
            }
        }
    }
    return NULL;
}

void shuffle_deck(Deck *deck) {
    for (int i = 0; i < deck->size; i++) {
        if (deck->status[i] == CARD_IN_DISCARD) {
            deck->status[i] = CARD_IN_DRAW_PILE;
        }
    }
    deck->cards_in_draw_pile = deck->cards_in_discard;
    deck->cards_in_discard = 0;
}

void discard_card(Deck *deck, int index) {
    assert(index >= 0 && index < deck->cards_in_hand);
    assert(deck->cards_in_hand > 0);
    for (int i = 0, j = 0; i < deck->size; i++) {
        if (deck->status[i] == CARD_IN_HAND) {
            if (j++ == index) {
                deck->status[i] = CARD_IN_DISCARD;
                deck->cards_in_hand--;
                deck->cards_in_discard++;
                return;
            }
        }
    }
}

void discard_all(Deck *deck) {
    for (int i = 0; i < deck->size; i++) {
        if (deck->status[i] == CARD_IN_HAND) {
            deck->status[i] = CARD_IN_DISCARD;
        }
    }
    deck->cards_in_discard += deck->cards_in_hand;
    deck->cards_in_hand = 0;
}

void free_deck(Deck *deck) {
    for (int i = 0; i < deck->size; i++) {
        if (deck->cards[i].data) {
            free(deck->cards[i].data);
        }
    }
    free(deck->cards);
    free(deck->status);
}
