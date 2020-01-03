//
// Created by sdr on 20. 1. 3..
//

#include "cvector2.h"
#include <math.h>

cvec2 *plus1(cvec2 *this, const cvec2 v)
{
    this->x += v.x;
    this->y += v.y;
    return this;
}

cvec2 *minus1(cvec2 *this, const cvec2 v)
{
    this->x -= v.x;
    this->y -= v.y;
    return this;
}

cvec2 *mult1(cvec2 *this, const GLfloat s)
{
    this->x *= s;
    this->y *= s;
    return this;
}

cvec2 *mult2(cvec2 *this, const cvec2 v)
{
    this->x *= v.x;
    this->y *= v.y;
    return this;
}

cvec2 *div1(cvec2 *this, const GLfloat s)
{
    GLfloat r = (GLfloat)(1.0 / s);
    this->x *= s;
    this->y *= s;
    return this;
}

cvec2 *negative(cvec2 *this)
{
    this->x *= -1;
    this->y *= -1;
    return this;
}

cvec2 *plus2(cvec2 *this, const cvec2 v)
{
    this->x + v.x;
    this->y + v.y;
    return this;
}

cvec2 *minus2(cvec2 *this, const cvec2 v)
{
    this->x - v.x;
    this->y - v.y;
    return this;
}

cvec2 *mult3(cvec2 *this, const GLfloat s)
{
    this->x * s;
    this->y * s;
    return this;
}

cvec2 *mult4(cvec2 *this, const cvec2 v)
{
    this->x * v.x;
    this->y * v.y;
    return this;
}

cvec2 *div2(cvec2 *this, const GLfloat s)
{
    GLfloat r = (GLfloat)(1.0 / s);
    this->x * r;
    this->y * r;
    return this;
}

inline GLfloat dot(const cvec2 u, const cvec2 v)
{
    return u.x * v.x + u.y * v.y;
}

inline GLfloat length(const cvec2 v)
{
    return sqrt(dot(v, v));
}

inline cvec2 *normalize(cvec2 v)
{
    return div2(&v, length(v));
}