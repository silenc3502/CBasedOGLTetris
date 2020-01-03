//
// Created by sdr on 20. 1. 3..
//

#include "game.h"
#include "board.h"
#include "tetromino.h"
#include "constants.h"
#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <GL/glut.h>

#define GT Game_T
typedef struct GT GT;

#define TT Tetro_T
typedef struct TT TT;

#define BT Board_T
typedef struct BT BT;

//typedef struct timeval tv;

GT *game_constructor(void) {
    GT *tmp = (GT *)malloc(sizeof(T));
    return tmp;
}

void game_run(GT *this, int argc, char **argv) {
    this->singleton = this;

    struct timeval t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));

    this->tetro->game_app = this;
    //this->tetro->game_board = &(this->game_board);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 800);
    glutCreateWindow("coglTetris");

#if 0
    game_reset();
    game_init();


    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);
#endif

    glutMainLoop();
}

void game_reset(void)
{
    TT *t = tetromino_constructor();
    //t->interval = DefaultInterval;
    t->interval = DEFAULTINTERVAL;
    tetromino_reset(t);
}

void game_init(void) {
}