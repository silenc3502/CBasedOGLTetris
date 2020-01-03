//
// Created by sdr on 20. 1. 3..
//

#include "cvector4.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define CV4T CVector4_T
typedef struct CV4T CV4T;

#define VTBL4T VirtualTBL_4T
typedef struct VTBL4T VTBL4T;

#define CON4T Constructor_4T
typedef struct CON4T CON4T;

#define OPPOF4T OperPof_4T
typedef struct OPPOF4T OPPOF4T;

#define OPTBL4T OperTBL_4T
typedef struct OPTBL4T OPTBL4T;

static VTBL4T fixed_vtbl4 = {cons1_4T, cons2_4T, cons3_4T};

void cons1_4T(CV4T *this, double zero)
{
    this->x = (GLfloat)zero;
    this->y = (GLfloat)zero;
    this->z = (GLfloat)zero;
    this->w = (GLfloat)zero;
}

void cons2_4T(CV4T *this, double a, double b, double c, double d)
{
    this->x = (GLfloat)a;
    this->y = (GLfloat)b;
    this->z = (GLfloat)c;
    this->w = (GLfloat)d;
}

void cons3_4T(CV4T *this, CV4T v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}

#if 0
void cons4_4T(CV3T *this, CV4T *v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}
#endif

CV4T *negative_4T(CV4T *this)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x *= -this->x;
    u->y *= -this->y;
    u->z *= -this->z;
    u->w *= -this->w;
    return u;
}

CV4T *plus1_4T(CV4T *this, const CV4T v)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x += v.x;
    u->y += v.y;
    u->z += v.z;
    u->w += v.w;
    return u;
}

CV4T *minus1_4T(CV4T *this, const CV4T v) {
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x -= v.x;
    u->y -= v.y;
    u->z -= v.z;
    u->w -= v.w;
    return u;
}

CV4T *mult1_4T(CV4T *this, const GLfloat s) {
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x * s;
    u->y = this->y * s;
    u->z = this->z * s;
    u->w = this->w * s;
    return u;
}

CV4T *mult2_4T(CV4T *this, const CV4T v) {
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x * v.x;
    u->y = this->y * v.y;
    u->z = this->z * v.z;
    u->w = this->w * v.w;
    return u;
}

CV4T *div1_4T(CV4T *this, const GLfloat s) {
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    GLfloat r = 1.0 / s;
    u->x = this->x * r;
    u->y = this->y * r;
    u->z = this->z * r;
    u->w = this->w * r;
    return u;
}

CV4T *plus2_4T(CV4T *this, const CV4T v)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x + v.x;
    u->y = this->y + v.y;
    u->z = this->z + v.z;
    u->w = this->w + v.w;
    return u;
}

CV4T *minus2_4T(CV4T *this, const CV4T v)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x - v.x;
    u->y = this->y - v.y;
    u->z = this->z - v.z;
    u->w = this->w - v.w;
    return u;
}

CV4T *mult3_4T(CV4T *this, const GLfloat s)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x * s;
    u->y = this->y * s;
    u->z = this->z * s;
    u->w = this->w * s;
    return u;
}

CV4T *mult4_4T(CV4T *this, const CV4T v)
{
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    u->x = this->x * v.x;
    u->y = this->y * v.y;
    u->z = this->z * v.z;
    u->w = this->w * v.w;
    return u;
}

CV4T *div2_4T(CV4T *this, const GLfloat s) {
    CV4T *u = (CV4T *)malloc(sizeof(CV4T));
    GLfloat r = 1.0 / s;
    this->x *= r;
    this->y *= r;
    this->z *= r;
    this->w *= r;
    return this;
}

GLfloat dot_4T(const CV4T u, const CV4T v)
{
    return u.x * v.x + u.y * v.y;
}

GLfloat length_4T(const CV4T v)
{
    return sqrt(dot_4T(v, v));
}

CV4T *normalize_4T(CV4T v)
{
    return div1_4T(&v, length_4T(v));
}

CV4T *cvector4_constructor(double one, double two, double three, double four)
{
    CV4T *tmp = (CV4T *)malloc(sizeof(CV4T));
    tmp->con = (CON4T *)malloc(sizeof(CON4T));
    tmp->con->pvtbl = (VTBL4T *)malloc(sizeof(VTBL4T));

    tmp->con->pvtbl->func0 = fixed_vtbl4.func0;
    tmp->con->pvtbl->func1 = fixed_vtbl4.func1;
    tmp->con->pvtbl->func2 = fixed_vtbl4.func2;

    if(!one)
        tmp->con->pvtbl->func0(tmp, 0);
    else if(two && three && four)
        tmp->con->pvtbl->func1(tmp, one, two, three, four);
    else
        printf("Instance Case\n");
        //tmp->con->pvtbl->func1(tmp, one, two);

    //printf("4T this->x = %lf, this->y = %lf\n", tmp->x, tmp->y);
    tmp->op = (OPPOF4T *)malloc(sizeof(OPPOF4T));
    return tmp;
}