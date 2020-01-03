//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_BOARD_H
#define CBASEDOGLTETRIS_BOARD_H

#include <stdbool.h>

#define BT Board_T
typedef struct BT BT;

struct BT
{
    int blocks[20][10];
    int num_of_points;
};

void init_board(void);
void reset_board(void);
bool has_collision(bool, int, int);
bool top_reached(bool, int);
void add_blocks(bool, int, int, int);
void write_buffer(void);

#endif //CBASEDOGLTETRIS_BOARD_H
