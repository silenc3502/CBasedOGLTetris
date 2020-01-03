//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_CVECTOR_H
#define CBASEDOGLTETRIS_CVECTOR_H

#include <GL/glut.h>

typedef struct _cvec2 cvec2;
typedef struct _vtbl vtbl;
typedef struct _cons cons;
typedef struct _oppof oppof;
typedef struct _optbl optbl;

struct _cons
{
    int count;
    vtbl *pvtbl;
};

struct _oppof
{
    optbl *poptbl;
};

struct _cvec2
{
    GLfloat x;
    GLfloat y;

    /* constructor with pof */
    cons *con;

    /* operator overloading with pof */
    oppof *op;
};

struct _vtbl
{
    void (* const func0)(int);
    void (* const func1)(int, int);
    void (* const func2)(cvec2 *);
};

struct _optbl
{
    void * (* plus)(void *, void *);
    void * (* minus)(void *, void *);
    void * (* mult)(void *, void *);
    void * (* div)(void *, void *);
};

#endif //CBASEDOGLTETRIS_CVECTOR_H
