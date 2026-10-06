#ifndef MAT4_HPP
#define MAT4_HPP
#include <math.h>

struct Mat4
{
    float m[16];

    static Mat4 identity();
    static Mat4 translate(float tx, float ty, float tz);
    Mat4 operator*(const Mat4 &o) const;
    static Mat4 rotateY(float angle);
};

#endif