#ifndef GAME_H
#define GAME_H

typedef enum {
    STATE_EXIT,
    STATE_MENU,
    STATE_GAMEPLAY
} GameState;

GameState show_main_menu();
GameState start_gameplay();

#endif