//
// Created by sdr on 20. 1. 3..
//

#define GLFW_INCLUDE_GLEXT
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "game.h"
#include "board.h"
#include "tetromino.h"
#include "constants.h"
#include "cvector2.h"
#include "cvector4.h"
#include "constants.h"

#include <sys/time.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "initglsl.h"

#include <GL/glext.h>

#define TWO_POINTER_SIZE        (16)

#define GT Game_T
typedef struct GT GT;

#define TT Tetro_T
typedef struct TT TT;

#define BT Board_T
typedef struct BT BT;

#define CV2T CVector2_T
typedef struct CV2T CV2T;

#define CV4T CVector4_T
typedef struct CV4T CV4T;

//typedef struct timeval tv;

GT *ctx;

GT *game_constructor(void) {
    ctx = (GT *)malloc(sizeof(GT));
    ctx->singleton = (GT *)malloc(sizeof(GT));
    ctx->tetro = (TT *)malloc(sizeof(TT));
    ctx->game_board = (BT *)malloc(sizeof(BT));

    return ctx;
}

void game_run(GT *this, int argc, char **argv) {
    this->singleton = this;

    struct timeval t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));

    this->tetro->game_app = this;
    this->tetro->game_board = this->game_board;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 800);
    //glutInitWindowSize(340, 600);
    glutCreateWindow("coglTetris");

    game_reset(this);
    game_init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    glutMainLoop();
}

void game_reset(GT *this)
{
    //TT *t = tetromino_constructor();
    //t->interval = DefaultInterval;
    this->tetro->interval = DEFAULTINTERVAL;
    //t->interval = DEFAULTINTERVAL;
    printf("tetro reset\n");
    tetromino_reset(this->tetro);
    reset_board(this->game_board);
    this->is_game_over = false;
}

struct point_2d
{
    GLfloat x;
    GLfloat y;
};

struct point_4d
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;
};

void game_init(void) {
    int i;
    CV2T *points[TOTALPOINTS];
    struct point_2d p[TOTALPOINTS];

    for(i = 0; i < NUMOFHLINES; i++)
    {
        points[i * 2    ] = cvector2_constructor(-W, -H + BLOCK_H * i);
        points[i * 2 + 1] = cvector2_constructor( W, -H + BLOCK_H * i);
        p[i * 2    ].x = -W;
        p[i * 2    ].y = -H + BLOCK_H * i;
        p[i * 2 + 1].x = W;
        p[i * 2 + 1].y = -H + BLOCK_H * i;
    }
    for(i = 0; i < NUMOFVLINES; i++)
    {
        points[NUMOFHPOINTS + i * 2    ] = cvector2_constructor(-W + BLOCK_W * i, -H);
        points[NUMOFHPOINTS + i * 2 + 1] = cvector2_constructor(-W + BLOCK_W * i,  H);
        p[NUMOFHPOINTS + i * 2    ].x = -W + BLOCK_W * i;
        p[NUMOFHPOINTS + i * 2    ].y = -H;
        p[NUMOFHPOINTS + i * 2 + 1].x = -W + BLOCK_W * i;
        p[NUMOFHPOINTS + i * 2 + 1].y = H;
    }

    CV4T *colors[TOTALPOINTS];
    struct point_4d c4[TOTALPOINTS];
    for(i = 0; i < NUMOFHPOINTS + NUMOFVPOINTS; i++)
    {
        colors[i] = cvector4_constructor(0.93, 0.93, 0.93, 1.0);
        c4[i].x = 0.93;
        c4[i].y = 0.93;
        c4[i].z = 0.93;
        c4[i].w = 1.0;
    }

#if 0
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, TOTALPOINTS * (sizeof(CV2T) - TWO_POINTER_SIZE), points);
    glBufferSubData(GL_ARRAY_BUFFER, COLORSOFFSET, sizeof(colors), colors);
#else
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p) + sizeof(c4), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, TOTALPOINTS * sizeof(struct point_2d), p);
    glBufferSubData(GL_ARRAY_BUFFER, COLORSOFFSET, sizeof(c4), c4);
#endif

    GLuint program = InitShader("vshader.glsl", "fshader.glsl");

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(COLORSOFFSET));

    glClearColor(1.0, 1.0, 1.0, 1.0);
    //glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //printf("ctx->is_game_over = %d\n", ctx->is_game_over);

    if(ctx->is_game_over)
    {
        //printf("game over\n");
        glRasterPos2f(-0.5, 0.1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');
        glRasterPos2f(-0.2, 0.1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
        glRasterPos2f(0.1, 0.1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
        glRasterPos2f(0.4, 0.1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');

        glRasterPos2f(-0.5, -0.2);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
        glRasterPos2f(-0.2, -0.2);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');
        glRasterPos2f(0.1, -0.2);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
        glRasterPos2f(0.4, -0.2);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
    }
    else
    {
        //printf("tetro_write_buffer\n");
        tetro_write_buffer(ctx->tetro);
        board_write_buffer(ctx->game_board);

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);

        // draw grids
        glDrawArrays(GL_LINES, 0, NUMOFHPOINTS + NUMOFVPOINTS);

        // draw current tetromino
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLE_STRIP, BEGINTETROMINOPOINTS, NUMOFTETROMINOPOINTS);

        // draw bottom blocks
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLE_STRIP, BEGINBOARDPOINTS, ctx->game_board->num_of_points);
    }

    glutSwapBuffers();
}

void game_over(GT *game)
{
    game->is_game_over = true;
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            //ctx->tetro->left();
            tetro_left(ctx->tetro);
            break;
        case GLUT_KEY_RIGHT:
            //ctx->tetro->right();
            tetro_right(ctx->tetro);
            break;
        case GLUT_KEY_UP:
            //ctx->tetro->rotate();
            tetro_rotate(ctx->tetro);
            break;
        case GLUT_KEY_DOWN:
            //ctx->tetro->down();
            tetro_down(ctx->tetro);
            break;
        case 'w':
        case 'W':
            //ctx->tetro->up();
            tetro_up(ctx->tetro);
            break;
        case 'r':
        case 'R':
            game_reset(ctx);
            break;
        case 'q':
        case 'Q':
        case KEYCODEESC:
        case KEYCODEESC2:
            exit(EXIT_SUCCESS);
            break;
    }
}

void special(int key, int x, int y)
{
    keyboard(key, x, y);
}

void idle(void)
{
    usleep(20);
    glutPostRedisplay();
}