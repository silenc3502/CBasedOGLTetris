//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_CVECTOR4_H
#define CBASEDOGLTETRIS_CVECTOR4_H

#include <GL/glut.h>

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

struct CON4T
{
    int count;
    VTBL4T *pvtbl;
};

struct OPPOF4T
{
    OPTBL4T *poptbl;
};

struct CV4T
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat w;

    /* constructor with pof */
    CON4T *con;

    /* operator overloading with pof */
    OPPOF4T *op;
};

struct VTBL4T
{
    void (* func0)(CV4T *, double);
    void (* func1)(CV4T *, double, double, double, double);
    void (* func2)(CV4T *, CV4T);
};

struct OPTBL4T
{
    void * (* plus)(void *, void *);
    void * (* minus)(void *, void *);
    void * (* mult)(void *, void *);
    void * (* div)(void *, void *);
};

extern void cons1_4T(CV4T *this, double zero);
extern void cons2_4T(CV4T *this, double a, double b, double c, double d);
extern void cons3_4T(CV4T *this, CV4T v);

extern CV4T *negative_4T(CV4T *this);
extern CV4T *plus1_4T(CV4T *this, const CV4T v);
extern CV4T *minus1_4T(CV4T *this, const CV4T v);
extern CV4T *mult1_4T(CV4T *this, const GLfloat s);
extern CV4T *mult2_4T(CV4T *this, const CV4T v);
extern CV4T *div1_4T(CV4T *this, const GLfloat s);
extern CV4T *plus2_4T(CV4T *this, const CV4T v);
extern CV4T *minus2_4T(CV4T *this, const CV4T v);
extern CV4T *mult3_4T(CV4T *this, const GLfloat s);
extern CV4T *mult4_4T(CV4T *this, const CV4T v);
extern CV4T *div2_4T(CV4T *this, const GLfloat s);
extern GLfloat dot_4T(const CV4T u, const CV4T v);
extern GLfloat length_4T(const CV4T v);
extern CV4T *normalize_4T(CV4T v);
extern CV4T *cvector4_constructor(double, double, double, double);

#undef CV4T
#undef VTBL4T
#undef CON4T
#undef OPPOF4T
#undef OPTBL4T

#endif //CBASEDOGLTETRIS_CVECTOR4_H
