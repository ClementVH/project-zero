#ifndef FILE_CUBIC_SPLINE_SEEN
#define FILE_CUBIC_SPLINE_SEEN
#include <raymath.h>

typedef struct CubicSpline {
    float* xs;
    float* ys;
} CubicSpline;

CubicSpline* ConstructCubicSpline(int n, float* cpxs, float* cpys);

void drawSpline(CubicSpline*);

#endif
