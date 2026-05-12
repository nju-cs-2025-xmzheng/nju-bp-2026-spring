#include "game.h"
#include <assert.h>

static void test_damage_without_block_reduces_health(void) {
    Entity target = {30, 30, 0};

    deal_damage(&target, 7);

    assert(target.health == 23);
    assert(target.block == 0);
}

static void test_block_absorbs_all_damage(void) {
    Entity target = {30, 30, 10};

    deal_damage(&target, 7);

    assert(target.health == 30);
    assert(target.block == 3);
}

static void test_partial_block_reduces_remaining_health(void) {
    Entity target = {30, 30, 4};

    deal_damage(&target, 7);

    assert(target.health == 27);
    assert(target.block == 0);
}

static void test_damage_does_not_make_health_negative(void) {
    Entity target = {30, 5, 2};

    deal_damage(&target, 20);

    assert(target.health == 0);
    assert(target.block == 0);
}

int main(void) {
    test_damage_without_block_reduces_health();
    test_block_absorbs_all_damage();
    test_partial_block_reduces_remaining_health();
    test_damage_does_not_make_health_negative();
}
