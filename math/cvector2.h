//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_CVECTOR_H
#define CBASEDOGLTETRIS_CVECTOR_H

#include <GL/glut.h>

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

struct CON2T
{
    int count;
    VTBL2T *pvtbl;
};

struct OPPOF2T
{
    OPTBL2T *poptbl;
};

struct CV2T
{
    GLfloat x;
    GLfloat y;

    /* constructor with pof */
    CON2T *con;

    /* operator overloading with pof */
    OPPOF2T *op;
};

struct VTBL2T
{
    void (* func0)(CV2T *, double);
    void (* func1)(CV2T *, double, double);
    void (* func2)(CV2T *);
};

struct OPTBL2T
{
    void * (* plus)(void *, void *);
    void * (* minus)(void *, void *);
    void * (* mult)(void *, void *);
    void * (* div)(void *, void *);
};

extern CV2T *plus1(CV2T *this, const CV2T v);
extern CV2T *minus1(CV2T *this, const CV2T v);
extern CV2T *mult1(CV2T *this, const GLfloat s);
extern CV2T *mult2(CV2T *this, const CV2T v);
extern CV2T *div1(CV2T *this, const GLfloat s);
extern CV2T *negative(CV2T *this);
extern CV2T *plus2(CV2T *this, const CV2T v);
extern CV2T *minus2(CV2T *this, const CV2T v);
extern CV2T *mult3(CV2T *this, const GLfloat s);
extern CV2T *mult4(CV2T *this, const CV2T v);
extern CV2T *div2(CV2T *this, const GLfloat s);
extern GLfloat dot(const CV2T u, const CV2T v);
extern GLfloat length(const CV2T v);
extern CV2T *normalize(CV2T v);
extern void cons1_2T(CV2T *this, double a);
extern void cons2_2T(CV2T *this, double a, double b);
extern CV2T *cvector2_constructor(double, double);

#undef CV2T
#undef VTBL2T
#undef CON2T
#undef OPPOF2T
#undef OPTBL2T

#endif //CBASEDOGLTETRIS_CVECTOR_H
