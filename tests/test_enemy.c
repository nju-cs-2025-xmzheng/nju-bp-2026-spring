#include "enemy.h"
#include <assert.h>
#include <string.h>

static void test_enemy_default_state(void) {
    Enemy enemy = {{40, 40, 0}};

    assert(enemy.turn == 0);
    assert(enemy.phase == ENEMY_PHASE_ONE);
    assert(enemy.intent == INTENT_DEF_6);
}

static void test_enemy_intent_definitions(void) {
    assert(INTENT_COUNT == 6);

    assert(strcmp(enemy_intents[INTENT_DEF_6].description,
                  "adds 6 blocks to itself") == 0);
    assert(strcmp(enemy_intents[INTENT_ATK_8].description,
                  "deals 8 damage to the player") == 0);
    assert(strcmp(enemy_intents[INTENT_ATK_5_DEF_10].description,
                  "deals 5 damage to the player and adds 10 blocks to itself") ==
           0);
    assert(strcmp(enemy_intents[INTENT_ATK_16].description,
                  "deals 16 damage to the player") == 0);
    assert(strcmp(enemy_intents[INTENT_DEF_10].description,
                  "adds 10 blocks to itself") == 0);
    assert(strcmp(enemy_intents[INTENT_ATK_12].description,
                  "deals 12 damage to the player") == 0);

    for (int i = 0; i < INTENT_COUNT; i++) {
        assert(enemy_intents[i].effect != NULL);
    }
}

static void test_defense_intents_add_block_to_enemy(void) {
    Player player = {{80, 80, 0}, 3, 3};
    Enemy enemy = {{40, 40, 0}};

    enemy_intents[INTENT_DEF_6].effect(&player, &enemy);
    assert(enemy.base.block == 6);
    assert(player.base.health == 80);

    enemy_intents[INTENT_DEF_10].effect(&player, &enemy);
    assert(enemy.base.block == 16);
    assert(player.base.health == 80);
}

static void test_attack_intents_respect_player_block(void) {
    Player player = {{80, 80, 3}, 3, 3};
    Enemy enemy = {{40, 40, 0}};

    enemy_intents[INTENT_ATK_8].effect(&player, &enemy);

    assert(player.base.health == 75);
    assert(player.base.block == 0);
    assert(enemy.base.block == 0);
}

static void test_attack_intents_do_not_make_health_negative(void) {
    Player player = {{80, 4, 1}, 3, 3};
    Enemy enemy = {{40, 40, 0}};

    enemy_intents[INTENT_ATK_16].effect(&player, &enemy);

    assert(player.base.health == 0);
    assert(player.base.block == 0);
}

static void test_attack_and_defense_intent_combines_both_effects(void) {
    Player player = {{80, 80, 2}, 3, 3};
    Enemy enemy = {{40, 40, 4}};

    enemy_intents[INTENT_ATK_5_DEF_10].effect(&player, &enemy);

    assert(player.base.health == 77);
    assert(player.base.block == 0);
    assert(enemy.base.block == 14);
}

int main(void) {
    test_enemy_default_state();
    test_enemy_intent_definitions();
    test_defense_intents_add_block_to_enemy();
    test_attack_intents_respect_player_block();
    test_attack_intents_do_not_make_health_negative();
    test_attack_and_defense_intent_combines_both_effects();
}
