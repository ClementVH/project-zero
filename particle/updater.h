#ifndef FILE_UPDATER_SEEN
#define FILE_UPDATER_SEEN
#include "particle/particle.h"

typedef struct ParticleUpdater {
    void (*update)(ParticleData*);
    void* updaterData;
} ParticleUpdater;

ParticleUpdater getNewtonUpdater();
ParticleUpdater getTimeUpdater();

#endif
