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

#if 0
typedef enum {
    FALSE, TRUE
}
bool;
#endif

extern void init_board(void);
extern void reset_board(BT *);
extern bool has_collision(bool[4][4], int, int, BT *);
extern bool top_reached(bool[4][4], int);
extern void board_add_blocks(bool[4][4], int, int, int, BT *);
extern void board_write_buffer(BT *);

#undef BT

#endif //CBASEDOGLTETRIS_BOARD_H
