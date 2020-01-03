//
// Created by sdr on 20. 1. 3..
//

#include "cvector2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define CV2T CVector2_T
typedef struct CV2T CV2T;

#define VTBL2T VirtualTBL_2T
typedef struct VTBL2T VTBL2T;

#define CON2T Constructor_2T
typedef struct CON2T CON2T;

#define OPPOF2T OperPof_2T
typedef struct OPPOF2T OPPOF2T;

#define OPTBL2T OperTBL_2T
typedef struct OPTBL2T OPTBL2T;

static VTBL2T fixed_vtbl2 = {cons1_2T, cons2_2T, NULL};

CV2T *plus1(CV2T *this, const CV2T v)
{
    this->x += v.x;
    this->y += v.y;
    return this;
}

CV2T *minus1(CV2T *this, const CV2T v)
{
    this->x -= v.x;
    this->y -= v.y;
    return this;
}

CV2T *mult1(CV2T *this, const GLfloat s)
{
    this->x *= s;
    this->y *= s;
    return this;
}

CV2T *mult2(CV2T *this, const CV2T v)
{
    this->x *= v.x;
    this->y *= v.y;
    return this;
}

CV2T *div1(CV2T *this, const GLfloat s)
{
    GLfloat r = (GLfloat)(1.0 / s);
    this->x *= s;
    this->y *= s;
    return this;
}

CV2T *negative(CV2T *this)
{
    CV2T *v = (CV2T *)malloc(sizeof(CV2T));
    v->x *= -1;
    v->y *= -1;
    return v;
}

CV2T *plus2(CV2T *this, const CV2T v)
{
    CV2T *u = (CV2T *)malloc(sizeof(CV2T));
    u->x += v.x;
    u->y += v.y;
    return u;
}

CV2T *minus2(CV2T *this, const CV2T v)
{
    CV2T *u = (CV2T *)malloc(sizeof(CV2T));
    u->x -= v.x;
    u->y -= v.y;
    return u;
}

CV2T *mult3(CV2T *this, const GLfloat s)
{
    CV2T *u = (CV2T *)malloc(sizeof(CV2T));
    u->x *= s;
    u->y *= s;
    return u;
}

CV2T *mult4(CV2T *this, const CV2T v)
{
    CV2T *u = (CV2T *)malloc(sizeof(CV2T));
    u->x *= v.x;
    u->y *= v.y;
    return u;
}

CV2T *div2(CV2T *this, const GLfloat s)
{
    CV2T *u = (CV2T *)malloc(sizeof(CV2T));
    GLfloat r = (GLfloat)(1.0 / s);
    u->x *= r;
    u->y *= r;
    return u;
}

GLfloat dot(const CV2T u, const CV2T v)
{
    return u.x * v.x + u.y * v.y;
}

GLfloat length(const CV2T v)
{
    return sqrt(dot(v, v));
}

CV2T *normalize(CV2T v)
{
    return div2(&v, length(v));
}

void cons1_2T(CV2T *this, double a)
{
    this->x = (GLfloat)a;
    this->y = (GLfloat)a;
}

void cons2_2T(CV2T *this, double a, double b)
{
    this->x = (GLfloat)a;
    this->y = (GLfloat)b;
}

CV2T *cvector2_constructor(double one, double two)
{
    CV2T *tmp = (CV2T *)malloc(sizeof(CV2T));
    tmp->con = (CON2T *)malloc(sizeof(CON2T));
    tmp->con->pvtbl = (VTBL2T *)malloc(sizeof(VTBL2T));

    tmp->con->pvtbl->func0 = fixed_vtbl2.func0;
    tmp->con->pvtbl->func1 = fixed_vtbl2.func1;
    tmp->con->pvtbl->func2 = fixed_vtbl2.func2;

    if(!one)
        tmp->con->pvtbl->func0(tmp, 0);
    else if(!two)
        tmp->con->pvtbl->func0(tmp, one);
    else
        tmp->con->pvtbl->func1(tmp, one, two);

    //printf("this->x = %lf, this->y = %lf\n", tmp->x, tmp->y);
    tmp->op = (OPPOF2T *)malloc(sizeof(OPPOF2T));
    return tmp;
}