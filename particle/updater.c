#include <raymath.h>
#include "particle/updater.h"
#include "particle/particle.h"

void _basicUpdater(ParticleData* particleData) {

    for (int i = 0; i < particleData->countAlive; i++) {
        particleData->particles[i].pos =
            Vector3Add(particleData->particles[i].pos, Vector3Scale(particleData->particles[i].vel, 0.16f));
    }

}

ParticleUpdater basicUpdater = {&_basicUpdater};

void _timeUpdater(ParticleData* particleData) {
    int endId = particleData->countAlive;
    float timeElapsed = GetFrameTime();

    if (endId == 0) return;

    for (int i = 0; i < endId; i++) {
        particleData->particles[i].lifeTime -= timeElapsed;

        if (particleData->particles[i].lifeTime < 0.0f) {
            killParticle(particleData, i);
            endId = particleData->countAlive;
        }
    }
}

ParticleUpdater timeUpdater = {&_timeUpdater};
