#include <raymath.h>
#include "particle/updater.h"
#include "particle/particle.h"

void newtonUpdater(ParticleData* particleData) {
    for (int i = 0; i < particleData->countAlive; i++) {
        particleData->particles[i].pos =
            Vector3Add(particleData->particles[i].pos, Vector3Scale(particleData->particles[i].vel, 0.16f));
    }
}

ParticleUpdater getNewtonUpdater() {
    ParticleUpdater updater = {&newtonUpdater, 0};
    return updater;
}

void timeUpdater(ParticleData* particleData) {
    int endId = particleData->countAlive;
    float timeElapsed = GetFrameTime();

    if (endId == 0) return;

    for (int i = 0; i < endId; i++) {
        particleData->particles[i].lifeTime -= timeElapsed;

        if (particleData->particles[i].lifeTime < 0.0f) {
            killParticle(particleData, i);
            endId = particleData->countAlive;
            i--;
        }
    }
}

ParticleUpdater getTimeUpdater() {
    ParticleUpdater updater = {&timeUpdater, 0};
    return updater;
}