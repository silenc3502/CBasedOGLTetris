//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_CONSTANTS_H
#define CBASEDOGLTETRIS_CONSTANTS_H

#define BUFFER_OFFSET(offset)   ((GLvoid*) (offset))

#define TWO_FLOAT_POINT_SIZE    (8)

#if 1
#define KEYCODEESC              (33)
#define KEYCODEESC2             (27)

#define NUMOFHBLOCKS            (20)
#define NUMOFHLINES             (NUMOFHBLOCKS + 1)
#define NUMOFVBLOCKS            (10)
#define NUMOFVLINES             (NUMOFVBLOCKS + 1)

#define NUMOFHPOINTS            (NUMOFHLINES << 1)
#define NUMOFVPOINTS            (NUMOFVLINES << 1)

#define BEGINTETROMINOPOINTS    (NUMOFHPOINTS + NUMOFVPOINTS)
#define NUMOFTETROMINOPOINTS    (16)

#define BEGINBOARDPOINTS        (BEGINTETROMINOPOINTS + NUMOFTETROMINOPOINTS)
#define MAXBOARDPOINTS          (800)

#define TOTALPOINTS             (NUMOFHPOINTS + NUMOFVPOINTS + NUMOFTETROMINOPOINTS + MAXBOARDPOINTS)

#define COLORSOFFSET            (TOTALPOINTS * TWO_FLOAT_POINT_SIZE)

#define H                       (0.9)
#define W                       (0.82)
#define BLOCK_H                 ((H) / (10))
#define BLOCK_W                 ((W) / (5))

#define NUMOFCOLORS             (6)

#define BLOCKEMPTY              (-1)

#define INTERVALSPEEDUP         (1.1)
#define MINIMUMINTERVAL         (100)
#define DEFAULTINTERVAL         (623)

#else

const int NumOfColors = 6;

const double IntervalSpeedUp = 1.1;
const double MinimumInterval = 100;
const double DefaultInterval = 623;
#endif

//enum Shape {O, I, S, Z, L, J, T, NUM_OF_SHAPES};
#undef CV2T

#endif //CBASEDOGLTETRIS_CONSTANTS_H
