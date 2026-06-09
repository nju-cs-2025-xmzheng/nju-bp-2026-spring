#ifndef GAME_H
#define GAME_H

typedef enum {
    STATE_EXIT,
    STATE_MENU,
    STATE_GAMEPLAY,
} GameState;

GameState show_main_menu();
GameState start_gameplay();

typedef struct {
    const int max_health;
    int health;
    int block;
} Entity;

typedef struct {
    Entity base;
    const int initial_energy;
    int energy;
} Player;

typedef enum {
    INTENT_DEF_6,
    INTENT_ATK_8,
    INTENT_ATK_5_DEF_10,
    INTENT_ATK_16,
    INTENT_DEF_10,
    INTENT_ATK_12,
    INTENT_COUNT,
} EnemyIntentType;

typedef struct {
    Entity base;
    EnemyIntentType intent;
} Enemy;

void draw_hud(Player player, Enemy enemy);

void deal_damage(Entity *target, int damage);

#endif
