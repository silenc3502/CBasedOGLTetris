//
// Created by sdr on 20. 1. 4..
//

#include "board.h"
#include "constants.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <GL/glut.h>
#include <GL/glext.h>



#define BT Board_T
typedef struct BT BT;

void reset_board(BT *gameboard)
{
    int x, y;

    for(y = 0; y < 20; y++)
    {
        for(x = 0; x < 10; x++)
        {
            gameboard->blocks[y][x] = BLOCKEMPTY;
        }
    }

    gameboard->num_of_points = 0;
}

bool has_collision(bool tetro_blocks[4][4], int steps, int cur_x, BT *gameboard)
{
    int x, y;

    int left_most = 999;
    int right_most = -999;
    int bottom_most = -999;

    printf("general\n");

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            if(tetro_blocks[y][x])
            {
                if(x < left_most)
                {
                    left_most = x;
                }
                if(x > right_most)
                {
                    right_most = x;
                }
                if(y > bottom_most)
                {
                    bottom_most = y;
                }
            }
        }
    }

    printf("check side border\n");

    if(cur_x + left_most < 0)
    {
        return true;
    }
    if(cur_x + right_most > 9)
    {
        return true;
    }

    printf("check bottom border\n");

    if(steps + bottom_most >= 20)
    {
        return true;
    }

    printf("check collision\n");
    printf("BLOCKEMPTY = %d\n", BLOCKEMPTY);

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            printf("steps = %d\n", steps);
            printf("cur_x = %d\n", cur_x);
            printf("tetro_blocks[%d][%d] = %d\n", y, x, tetro_blocks[y][x]);
            printf("gameboard->blocks[%d][%d] = %d\n", steps + y, cur_x + x, gameboard->blocks[steps + y][cur_x + x]);

            if(steps + y >= 0 && steps + y < 20 &&
                tetro_blocks[y][x] && (gameboard->blocks[steps + y][cur_x + x] != BLOCKEMPTY))
            {
                return true;
            }
        }
    }

    return false;
}

bool top_reached(bool tetro_blocks[4][4], int steps)
{
    int x, y;
    int top_most = 999;

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            if(tetro_blocks[y][x])
            {
                if(y < top_most)
                {
                    top_most = y;
                }
            }
        }
    }

    if(steps + top_most <= 0)
    {
        return true;
    }

    return false;
}

void board_add_blocks(bool tetro_blocks[4][4], int steps, int cur_x, int color_id, BT *gameboard)
{
    int i, x, y;

    for(y = 0; y < 4; y++)
    {
        for(x = 0; x < 4; x++)
        {
            if(tetro_blocks[y][x] && steps + y < 20 && cur_x + x < 10 && steps + y >= 0)
            {
                if(gameboard->blocks[steps + y][cur_x + x] == BLOCKEMPTY)
                {
                    gameboard->num_of_points += 4;
                }
                gameboard->blocks[steps + y][cur_x + x] = color_id;

                assert(0 <= color_id && color_id < NUMOFCOLORS);
                assert(steps + y >= 0);
                assert(steps + y < 20);
                assert(cur_x + x >= 0);
                assert(cur_x + x < 10);
            }
        }
    }

    for(y = 0; y < 20; y++)
    {
        bool full = true;
        for(x = 0; x < 10; x++)
        {
            if(gameboard->blocks[y][x] == BLOCKEMPTY)
            {
                full = false;
                break;
            }
        }

        if(full)
        {
            for(i = y; i > 0; i--)
            {
                for(x = 0; x < 10; x++)
                {
                    gameboard->blocks[i][x] = gameboard->blocks[i - 1][x];
                }
            }
            for(i = 0; i < 10; i++)
            {
                gameboard->blocks[0][i] = BLOCKEMPTY;
            }
            gameboard->num_of_points -= 4 * 10;
        }
    }
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

void board_write_buffer(BT *gameboard)
{
    int i, j;
    int current = 0;

    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 10; j++)
        {
            if(gameboard->blocks[i][j] != BLOCKEMPTY)
            {
                struct point_2d points[4];
                struct point_4d color;
                struct point_4d colors[4];

                points[0].x = -W + (j    ) * BLOCK_W;
                points[1].x = -W + (j + 1) * BLOCK_W;
                points[2].x = -W + (j    ) * BLOCK_W;
                points[3].x = -W + (j + 1) * BLOCK_W;

                points[0].y = H - (i + 1) * BLOCK_H;
                points[1].y = H - (i + 1) * BLOCK_H;
                points[2].y = H - (  i  ) * BLOCK_H;
                points[3].y = H - (  i  ) * BLOCK_H;

                glBufferSubData(
                        GL_ARRAY_BUFFER,
                        (BEGINBOARDPOINTS + 4 * current) * sizeof(struct point_2d),
                        sizeof(points),
                        points
                );

                switch(gameboard->blocks[i][j])
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

                assert(0 <= gameboard->blocks[i][j] && gameboard->blocks[i][j] < NUMOFCOLORS);

#if 0
                printf("colors[0].x = %f\n", colors[0].x);
                printf("colors[1].y = %f\n", colors[1].y);
                printf("colors[2].z = %f\n", colors[2].z);
                printf("colors[3].w = %f\n", colors[3].w);
#endif

                glBufferSubData(
                        GL_ARRAY_BUFFER,
                        COLORSOFFSET + (BEGINBOARDPOINTS + 4 * current) * sizeof(struct point_4d),
                        sizeof(colors),
                        colors
                );

                current += 1;
            }
        }
    }
}