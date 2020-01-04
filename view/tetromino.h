//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_TETROMINO_H
#define CBASEDOGLTETRIS_TETROMINO_H

#include "game.h"
#include <stdbool.h>
#include <sys/time.h>

enum Shape {O, I, S, Z, L, J, T, NUM_OF_SHAPES};

#define GT Game_T
typedef struct GT GT;

#define TT Tetro_T
typedef struct TT TT;

#define BT Board_T
typedef struct BT BT;

struct TT {
    struct timeval start_time;
    int cur_x;
    int step_extra;
    int rotation_count;
    enum Shape shape;
    bool blocks[4][4];
    int color_id;
    GT *game_app;
    BT *game_board;
    double interval;
};

extern TT *tetromino_constructor(void);
extern void tetromino_reset(TT *);
extern double tetro_elapsed(TT *);
extern int tetro_steps(TT *);
extern void tetro_write_buffer(TT *);
extern void tetro_add_blocks(TT *);

#undef TT
#undef GT
#undef BT

#endif //CBASEDOGLTETRIS_TETROMINO_H
