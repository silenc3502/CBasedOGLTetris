//
// Created by sdr on 20. 1. 3..
//

#include "game.h"
#include "board.h"
#include "tetromino.h"
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct timeval tv;

game *game_constructor(void) {
    game *tmp = (game *)malloc(sizeof(game));
    return tmp;
}

void game_run(game *this, int argc, char **argv) {
    this->singleton = this;

    tv t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));

    this->tetro.game_app = this;
    this->tetro.game_board = &(this->game_board);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(340, 600);
    glutCreateWindow("coglTetris");

#if 0
    reset();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);
#endif

    glutMainLoop();
}