//
// Created by sdr on 20. 1. 3..
//

#include "tetromino.h"
#include "game.h"
#include "constants.h"
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>

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

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            this->blocks[j][i] = shapes[this->shape * 4 + j][i];
        }
    }

    //this->color_id = (this->color_id + 1) % NumOfColors;
    this->color_id = (this->color_id + 1) % NUMOFCOLORS;

    gettimeofday(&(this->start_time), NULL);

    //if(this->interval > MinimumInterval)
    if(this->interval > MINIMUMINTERVAL)
    {
        //this->interval /= IntervalSpeedUp;
        this->interval /= INTERVALSPEEDUP;
    }
}