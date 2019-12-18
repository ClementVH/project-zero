#ifndef FILE_UPDATER_SEEN
#define FILE_UPDATER_SEEN
#include "particle/particle.h"
#include <stdint.h>

typedef struct ParticleUpdater {
    void (*update)(ParticleData*, struct ParticleUpdater*);
    void* updaterData;
} ParticleUpdater;

ParticleUpdater getNewtonUpdater();
ParticleUpdater getTimeUpdater();

typedef struct AlphaUpdaterData {
    float* curveX;
    float* curveY;
} AlphaUpdaterData;

ParticleUpdater getAlphaUpdater();

#endif
