#include "card.h"
#include "game.h"
#include <assert.h>
#include <string.h>

static void test_card_definitions(void) {
    assert(CARD_TYPE_COUNT == 3);

    assert(strcmp(cards[CARD_STRIKE].name, "Strike") == 0);
    assert(cards[CARD_STRIKE].cost == 1);
    assert(cards[CARD_STRIKE].effect == strike_effect);

    assert(strcmp(cards[CARD_DEFEND].name, "Defend") == 0);
    assert(cards[CARD_DEFEND].cost == 1);
    assert(cards[CARD_DEFEND].effect == defend_effect);

    assert(strcmp(cards[CARD_BLOODLETTING].name, "Bloodletting") == 0);
    assert(cards[CARD_BLOODLETTING].cost == -1);
    assert(cards[CARD_BLOODLETTING].effect == bloodletting_effect);
}

static void test_play_card_applies_cost_and_effect(void) {
    Player p = {{80, 80, 0}, 3, 3};
    Enemy e = {{40, 40, 0}};

    play_card(&cards[CARD_STRIKE], NULL, &p, &e);
    assert(p.energy == 2);
    assert(e.base.health == 34);

    play_card(&cards[CARD_DEFEND], NULL, &p, &e);
    assert(p.energy == 1);
    assert(p.base.block == 5);

    play_card(&cards[CARD_BLOODLETTING], NULL, &p, &e);
    assert(p.energy == 2);
    assert(p.base.health == 77);
    assert(p.base.block == 5);
}

static void test_bloodletting_does_not_make_health_negative(void) {
    Player p = {{80, 2, 0}, 3, 0};
    Enemy e = {{40, 40, 0}};

    play_card(&cards[CARD_BLOODLETTING], NULL, &p, &e);
    assert(p.energy == 1);
    assert(p.base.health == 0);
    assert(e.base.health == 40);
}

int main(void) {
    test_card_definitions();
    test_play_card_applies_cost_and_effect();
    test_bloodletting_does_not_make_health_negative();
}
