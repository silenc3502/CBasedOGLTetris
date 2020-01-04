//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_GAME_H
#define CBASEDOGLTETRIS_GAME_H

#include <stdbool.h>

#include "tetromino.h"
#include "board.h"

#define GT Game_T
typedef struct GT GT;

#define TT Tetro_T
typedef struct TT TT;

#define BT Board_T
typedef struct BT BT;

struct GT
{
    bool is_game_over;
    TT *tetro;
    BT *game_board;
    GT *singleton;
};

extern GT *game_constructor(void);
extern void game_init(void);
extern void game_reset(GT *);
extern void display(void);
extern void keyboard(unsigned char key, int x, int y);
extern void special(int key, int x, int y);
extern void idle(void);

extern void game_over(GT *);
extern void game_run(GT *, int argc, char **argv);

#undef GT
#undef TT
#undef BT

#endif //CBASEDOGLTETRIS_GAME_H
