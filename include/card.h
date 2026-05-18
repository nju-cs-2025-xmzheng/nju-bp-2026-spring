#ifndef CARD_H
#define CARD_H

#include "game.h"
#include "sts_io.h"

#define card_data(...)                                                         \
    .data_cnt = sizeof((int[]){__VA_ARGS__}) / sizeof(int), .data = (int[]) {  \
        __VA_ARGS__                                                            \
    }
#define card_data_empty .data_cnt = 0, .data = NULL

typedef struct Card Card;
typedef struct Deck Deck;

struct Card {
    char name[20];
    int cost;
    void (*effect)(Card *self, Deck *deck, Player *player, Enemy *enemy);
    int data_cnt;
    int *data;
    char description[100];
};

typedef enum {
    CARD_STRIKE,
    CARD_DEFEND,
    CARD_BLOODLETTING,
    CARD_RAMPAGE,
    CARD_TYPE_COUNT,
} CardType;

void strike_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);
void defend_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);
void bloodletting_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);
void rampage_effect(Card *self, Deck *deck, Player *player, Enemy *enemy);

extern Card cards[CARD_TYPE_COUNT];

void print_card(Card *card);
void play_card(Card *card, Deck *deck, Player *player, Enemy *enemy);

#ifdef sts_print_selector
#undef sts_print_selector
#define sts_print_selector(x)                                                  \
    _Generic((x),                                                              \
        char *: sts_print_str,                                                 \
        const char *: sts_print_str,                                           \
        int: sts_print_int,                                                    \
        long: sts_print_long,                                                  \
        long long: sts_print_long_long,                                        \
        unsigned int: sts_print_uint,                                          \
        unsigned long: sts_print_ulong,                                        \
        unsigned long long: sts_print_ulong_long,                              \
        double: sts_print_double,                                              \
        float: sts_print_float,                                                \
        char: sts_print_char,                                                  \
        _Bool: sts_print_bool,                                                 \
        Card *: print_card,                                                    \
        default: sts_print_int)
#endif

#endif
