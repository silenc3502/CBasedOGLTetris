//
// Created by sdr on 20. 1. 3..
//

#include <stdio.h>

#include "game.h"

#define GT Game_T
typedef struct GT GT;

int main(int argc, char **argv) {
    printf("First: Private Tetris\n");
    printf("Second: Tetris on Network\n");

    GT *ogl_game = game_constructor();
    game_run(ogl_game, argc, argv);

    return 0;
}