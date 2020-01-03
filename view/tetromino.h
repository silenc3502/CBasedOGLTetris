//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_TETROMINO_H
#define CBASEDOGLTETRIS_TETROMINO_H

#include "game.h"

enum Shape {O, I, S, Z, L, J, T, NUM_OF_SHAPES};

typedef struct _tetromino tetromino;
struct _tetromino {
    int cur_x;
    struct _game *game_app;
    struct _board *game_board;
    double interval;
};

#endif //CBASEDOGLTETRIS_TETROMINO_H
