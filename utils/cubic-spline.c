#include "utils/cubic-spline.h"
#include <stdlib.h>
#include <raylib.h>

CubicSpline* ConstructCubicSpline(int n, float* cpxs, float* cpys) {
    int i, j;
    n--;
    float x[n + 1], a[n + 1], h[n], A[n], l[n + 1],
        u[n + 1], z[n + 1], c[n + 1], b[n], d[n];

    for (i = 0; i <= n; ++i) {
        x[i] = cpxs[i];
        a[i] = cpys[i];
    }

    for (i = 0; i <= n - 1; ++i) h[i] = x[i + 1] - x[i];

    /** Step 2 */
    for (i = 1; i <= n - 1; ++i)
        A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];

    /** Step 3 */
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    /** Step 4 */
    for (i = 1; i <= n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1];
        u[i] = h[i] / l[i];
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    /** Step 5 */
    l[n] = 1;
    z[n] = 0;
    c[n] = 0;

    /** Step 6 */
    for (j = n - 1; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    float* xs = malloc(sizeof(float) * 1000);
    float* ys = malloc(sizeof(float) * 1000);
    j = 0;
    for (float k = 0.0f; k < 1.0f; k += 0.001f) {
        int before = 0;
        int after = 1;

        while ( !((k >= cpxs[before]) && (k <= cpxs[after])) ) {
            before++;
            after++;
        }

        int index = before;
        xs[j] = k;
        ys[j] = a[index] +
            (k - cpxs[index]) * b[index] +
            powf((k - cpxs[index]), 2) * c[index] +
            powf((k - cpxs[index]), 3) * d[index];
        j++;
    }

    CubicSpline* curve = malloc(sizeof(CubicSpline));
    curve->xs = xs;
    curve->ys = ys;

    // for (int o = 0; o < 1000; o ++) {
    //     printf("%f, %f\n", xs[o], ys[o]);
    // }
    return curve;
}

void drawSpline(CubicSpline* spline) {
    int offset = 100;
    int scale = 500;
    for (int i = 0; i < 1000; i++) {
        DrawPixel(spline->xs[i] * scale + offset, scale - spline->ys[i] * scale + offset, RED);
    }
}
