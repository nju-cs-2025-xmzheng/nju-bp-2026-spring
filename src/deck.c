#include "deck.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
