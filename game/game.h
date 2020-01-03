//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_GAME_H
#define CBASEDOGLTETRIS_GAME_H

#include "tetromino.h"
#include "board.h"

typedef struct _game game;
struct _game
{
    int is_game_over;
    tetromino tetro;
    board game_board;
    struct _game *singleton;
};

game *game_constructor(void);
void game_init(void);
void game_reset(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void idle(void);

void game_over(void);
void run(int argc, char **argv);

#endif //CBASEDOGLTETRIS_GAME_H
