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

    return ctx;
}

void game_run(GT *this, int argc, char **argv) {
    this->singleton = this;
    ctx->is_game_over = 1;

    struct timeval t;
    gettimeofday(&t, NULL);
    srand((unsigned)(t.tv_sec * 1000 + t.tv_usec));

    //this->tetro->game_app = this;
    //this->tetro->game_board = &(this->game_board);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(600, 800);
    //glutInitWindowSize(340, 600);
    glutCreateWindow("coglTetris");

    game_reset(this);
    game_init();

    glutDisplayFunc(display);
#if 0
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);
#endif

    glutMainLoop();
}

void game_reset(GT *this)
{
    TT *t = tetromino_constructor();
    //t->interval = DefaultInterval;
    t->interval = DEFAULTINTERVAL;
    tetromino_reset(t);
    this->is_game_over = 0;
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
        p[i * 2    ].x = points[i * 2    ]->x;
        p[i * 2    ].y = points[i * 2    ]->y;
        p[i * 2 + 1].x = points[i * 2 + 1]->x;
        p[i * 2 + 1].y = points[i * 2 + 1]->y;
    }
    for(i = 0; i < NUMOFVLINES; i++)
    {
        points[NUMOFHPOINTS + i * 2    ] = cvector2_constructor(-W + BLOCK_W * i, -H);
        points[NUMOFHPOINTS + i * 2 + 1] = cvector2_constructor(-W + BLOCK_W * i,  H);
        p[NUMOFHPOINTS + i * 2    ].x = points[NUMOFHPOINTS + i * 2    ]->x;
        p[NUMOFHPOINTS + i * 2    ].y = points[NUMOFHPOINTS + i * 2    ]->y;
        p[NUMOFHPOINTS + i * 2 + 1].x = points[NUMOFHPOINTS + i * 2 + 1]->x;
        p[NUMOFHPOINTS + i * 2 + 1].y = points[NUMOFHPOINTS + i * 2 + 1]->y;
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

    //glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    printf("ctx = 0x%x\n", ctx);
    printf("ctx->is_game_over = %d\n", ctx->is_game_over);

    if(ctx->is_game_over)
    {
        printf("game over\n");
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
        //tetro_write_buffer();

        glClear(GL_COLOR_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_CULL_FACE);

        // draw grids
        glDrawArrays(GL_LINES, 0, NUMOFHPOINTS + NUMOFVPOINTS);

        // draw current tetromino
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLE_STRIP, BEGINTETROMINOPOINTS, NUMOFTETROMINOPOINTS);

        // draw bottom blocks
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        //glDrawArrays(GL_TRIANGLE_STRIP, kBeginBoardPoints, singleton->board.num_of_points);
    }

    glutSwapBuffers();
}