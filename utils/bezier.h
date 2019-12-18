#ifndef FILE_BEZIER_SEEN
#define FILE_BEZIER_SEEN
#include <raymath.h>
#include <stdlib.h>

float binom(int n, int k) {
    float coeff = 1.0f;
    for (int i = n - k + 1; i <= n; i++) coeff *= i;
    for (int i = 1; i <= k; i++) coeff /= i;
    return coeff;
}

typedef struct BezierCurve {
    float* curveX;
    float* curveY;
} BezierCurve;

BezierCurve bezier(int nb, float step, int order, Vector2* controlPoints) {
    float* xArr = (float*)malloc(sizeof(float) * nb);
    float* yArr = (float*)malloc(sizeof(float) * nb);

    int i = 0;
    for (float t = 0.0f; t < 1.0f; t += step) {
        float x = 0.0f;
        float y = 0.0f;

        for (int k = 0; k <= order; k++) {
            x = x + (binom(order, k) * powf((1.0f - t), (order - k)) * powf(t, k) * (controlPoints[k].x));
            y = y + (binom(order, k) * powf((1.0f - t), (order - k)) * powf(t, k) * (controlPoints[k].y));
        }

        xArr[i] = x;
        yArr[i] = y;

        i++;
    }

    return (BezierCurve){xArr, yArr};
}

#endif
