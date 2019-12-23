#ifndef FILE_UPDATER_SEEN
#define FILE_UPDATER_SEEN
#include <stdint.h>
#include "particle/particle.h"
#include "utils/cubic-spline.h"

typedef struct ParticleUpdater {
    void (*update)(ParticleData*, struct ParticleUpdater*);
    intptr_t updaterData;
    int systemID;
} ParticleUpdater;

typedef struct BezierCurveData {
    float* curveX;
    float* curveY;
} BezierCurveData;

ParticleUpdater* getNewtonUpdater();
ParticleUpdater* getTimeUpdater();
ParticleUpdater* getSizeUpdater();
ParticleUpdater* getAlphaUpdater(float*, float*, int);
ParticleUpdater* getSizeUpdater(float*, float*, int);

typedef struct AlphaUpdaterData {
    CubicSpline spline;
} AlphaUpdaterData;


typedef struct SizeUpdaterData {
    CubicSpline spline;
} SizeUpdaterData;

#endif
