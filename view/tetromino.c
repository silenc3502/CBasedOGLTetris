//
// Created by sdr on 20. 1. 3..
//

#include "tetromino.h"
#include "game.h"
#include "constants.h"
#include "cvector2.h"

#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include <GL/glut.h>
#include <GL/glext.h>



#define CV2T CVector2_T
typedef struct CV2T CV2T;

#define TT Tetro_T
typedef struct TT TT;

const bool shapes[28][4] =
{
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 1, 1, 0},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 0},

    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0},
};

TT *tetromino_constructor(void) {
    TT *tmp = (TT *)malloc(sizeof(TT));
    //tmp->color_id = rand() % NumOfColors;
    tmp->color_id = rand() % NUMOFCOLORS;
    return tmp;
}

void tetromino_reset(TT *this)
{
    int i, j;

    this->rotation_count = 0;
    this->cur_x = 3;
    this->step_extra = -2;
    this->shape = (enum Shape)(rand() % NUM_OF_SHAPES);

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            this->blocks[j][i] = shapes[this->shape * 4 + j][i];
        }
    }

    //this->color_id = (this->color_id + 1) % NumOfColors;
    this->color_id = (this->color_id + 1) % NUMOFCOLORS;
    printf("this->color_id = %d\n", this->color_id);

    gettimeofday(&(this->start_time), NULL);

    //if(this->interval > MinimumInterval)
    if(this->interval > MINIMUMINTERVAL)
    {
        //this->interval /= IntervalSpeedUp;
        this->interval /= INTERVALSPEEDUP;
    }

    printf("tetro->interval = %lf\n", this->interval);
}

double tetro_elapsed(TT *tetro)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double elapsed_t;
    elapsed_t = (t.tv_sec - tetro->start_time.tv_sec) * 1000.0;
    elapsed_t += (t.tv_usec - tetro->start_time.tv_usec) / 1000.0;

    printf("elapsed_t = %lf\n", elapsed_t);
    return elapsed_t;
}

int tetro_steps(TT *tetro)
{
    return ceil(tetro_elapsed(tetro) / tetro->interval + tetro->step_extra);
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

void tetro_left(TT *tetro)
{
    if(!has_collision(tetro->blocks, tetro_steps(tetro), tetro->cur_x - 1, tetro->game_board))
    {
        tetro->cur_x -= 1;
    }
}

void tetro_right(TT *tetro)
{
    if(!has_collision(tetro->blocks, tetro_steps(tetro), tetro->cur_x + 1, tetro->game_board))
    {
        tetro->cur_x += 1;
    }
}

void tetro_rotate_ccw(TT *tetro)
{
    int x, y;
    bool new_blocks[4][4] = {{0}};

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            if(tetro->blocks[y][x])
            {
                int new_y = 1 - (x - 2);
                int new_x = 2 + (y - 1);

                if(0 <= new_y && new_y < 4 && 0 <= new_x && new_x < 4)
                {
                    new_blocks[new_y][new_x] = 1;
                }

                assert(new_y >= 0);
                assert(new_y < 4);
                assert(new_x >= 0);
                assert(new_x < 4);
            }
        }
    }

    if(!has_collision(new_blocks, tetro_steps(tetro), tetro->cur_x, tetro->game_board))
    {
        for(y = 0; y < 4; y++)
        {
            for(x = 0; x < 4; x++)
            {
                tetro->blocks[y][x] = new_blocks[y][x];
            }
        }
    }
    else
    {
        tetro->rotation_count -= 1;
    }
}

void tetro_rotate_cw(TT *tetro)
{
    int x, y;
    bool new_blocks[4][4] = {{0}};

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            new_blocks[y][x] = shapes[tetro->shape * 4 + y][x];

            assert(tetro->shape * 4 + y < 28);
        }
    }

    if(!has_collision(new_blocks, tetro_steps(tetro), tetro->cur_x, tetro->game_board))
    {
        memcpy(tetro->blocks, new_blocks, 4 * 4);
    }
    else
    {
        tetro->rotation_count -= 1;
    }
}

void tetro_rotate(TT *tetro)
{
    tetro->rotation_count++;

    if(tetro->shape == 0)
    {
        ;
    }
    else if(tetro->shape == I || tetro->shape == S || tetro->shape == Z)
    {
        if(tetro->rotation_count % 2 == 0)
        {
            tetro_rotate_cw(tetro);
        }
        else
        {
            tetro_rotate_ccw(tetro);
        }
    }
    else if(tetro->shape == L || tetro->shape == J || tetro->shape == T)
    {
        tetro_rotate_ccw(tetro);
    }
}

void tetro_up(TT *tetro)
{
    tetro->step_extra -= 1;
}

void tetro_down(TT *tetro)
{
    tetro->step_extra++;

    if(has_collision(tetro->blocks, tetro_steps(tetro), tetro->cur_x, tetro->game_board))
    {
        tetro_add_blocks(tetro);
    }
}

void tetro_write_buffer(TT *tetro)
{
    int i, j;
    int current = 0;
    int steps = tetro_steps(tetro);

    printf("steps = %d\n", steps);

    //printf("before\n");

    if(has_collision(tetro->blocks, steps, tetro->cur_x, tetro->game_board))
    {
        if(top_reached(tetro->blocks, steps))
        {
            printf("is game over ?\n");
            tetro_add_blocks(tetro);
            game_over(tetro->game_app);
            return;
        }
        else
        {
            tetro_add_blocks(tetro);
            return;
        }
    }

    //printf("after\n");

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            if(tetro->blocks[i][j])
            {
                struct point_2d points[4];
                struct point_4d color;
                struct point_4d colors[4];

                points[0].x = -W + (j + tetro->cur_x    ) * BLOCK_W;
                points[1].x = -W + (j + tetro->cur_x + 1) * BLOCK_W;
                points[2].x = -W + (j + tetro->cur_x    ) * BLOCK_W;
                points[3].x = -W + (j + tetro->cur_x + 1) * BLOCK_W;

                points[0].y = H - (i + 1) * BLOCK_H - steps * BLOCK_H;
                points[1].y = H - (i + 1) * BLOCK_H - steps * BLOCK_H;
                points[2].y = H - (  i  ) * BLOCK_H - steps * BLOCK_H;
                points[3].y = H - (  i  ) * BLOCK_H - steps * BLOCK_H;

                glBufferSubData(GL_ARRAY_BUFFER,
                                (BEGINTETROMINOPOINTS + 4 * current) * sizeof(struct point_2d),
                                sizeof(points),
                                points);


                /*
                 const vec4 kDefaultColors[kNumOfColors] =
                 {
                    vec4(.37, .62, .95, 1.0), // blue
                    vec4(.39, .84, .29, 1.0), // green
                    vec4(.95, .28, .25, 1.0), // red
                    vec4(.75, .37, .99, 1.0), // purple
                    vec4(.97, .57, .22, 1.0), // orange
                    vec4(.99, .37, .61, 1.0), // pink
                 };
                 */

                switch(tetro->color_id)
                {
                    case 0:
                        color.x = 0.37;
                        color.y = 0.62;
                        color.z = 0.95;
                        color.w = 1.0;
                        break;
                    case 1:
                        color.x = 0.39;
                        color.y = 0.84;
                        color.z = 0.29;
                        color.w = 1.0;
                        break;
                    case 2:
                        color.x = 0.95;
                        color.y = 0.28;
                        color.z = 0.25;
                        color.w = 1.0;
                        break;
                    case 3:
                        color.x = 0.75;
                        color.y = 0.37;
                        color.z = 0.99;
                        color.w = 1.0;
                        break;
                    case 4:
                        color.x = 0.97;
                        color.y = 0.57;
                        color.z = 0.22;
                        color.w = 1.0;
                        break;
                    case 5:
                        color.x = 0.99;
                        color.y = 0.37;
                        color.z = 0.61;
                        color.w = 1.0;
                        break;
                }

                //colors = {color, color, color, color};
                memcpy(&colors, &color, 16);
                memcpy(&colors[1], &color, 16);
                memcpy(&colors[2], &color, 16);
                memcpy(&colors[3], &color, 16);

                printf("colors[0].x = %f\n", colors[0].x);
                printf("colors[1].y = %f\n", colors[1].y);
                printf("colors[2].z = %f\n", colors[2].z);
                printf("colors[3].w = %f\n", colors[3].w);

                glBufferSubData(
                        GL_ARRAY_BUFFER,
                        COLORSOFFSET + (BEGINTETROMINOPOINTS + 4 * current) * sizeof(struct point_4d),
                        sizeof(colors),
                        colors
                );

                current += 1;
            }
        }
    }
}

void tetro_add_blocks(TT *tetro)
{
    int rollback = 1;

    while(has_collision(tetro->blocks, tetro_steps(tetro) - rollback, tetro->cur_x, tetro->game_board))
    {
        rollback += 1;
    }
    board_add_blocks(tetro->blocks, tetro_steps(tetro) - rollback, tetro->cur_x, tetro->color_id, tetro->game_board);
    tetromino_reset(tetro);
}