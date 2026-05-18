#ifndef DECK_H
#define DECK_H

#include "card.h"

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
