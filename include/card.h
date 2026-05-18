#ifndef CARD_H
#define CARD_H

#include "game.h"

typedef struct Card Card;
typedef struct Deck Deck;

struct Card {
    char name[20];
    int cost;
    void (*effect)(Card *self, Deck *deck, Player *player, Enemy *enemy);
    char description[100];
};

typedef enum {
    CARD_STRIKE,
    CARD_DEFEND,
    CARD_BLOODLETTING,
    CARD_TYPE_COUNT,
} CardType;

void strike_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);
void defend_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);
void bloodletting_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);

extern Card cards[CARD_TYPE_COUNT];

void play_card(Card *card, Deck *deck, Player *player, Enemy *enemy);

typedef enum {
    CARD_IN_DRAW_PILE,
    CARD_IN_HAND,
    CARD_IN_DISCARD,
} CardStatus;

struct Deck {
    Card *cards;
    CardStatus *status;
    int size;
    int cards_in_draw_pile;
    int cards_in_hand;
    int cards_in_discard;
};

void init_deck(Deck *deck, CardType *card_types, int size);
void draw_cards(Deck *deck, int count);
Card *find_card_in_hand(Deck *deck, int index);
void shuffle_deck(Deck *deck);
void discard_card(Deck *deck, int index);
void discard_all(Deck *deck);
void free_deck(Deck *deck);

#endif
