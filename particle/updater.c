#include "raymath.h"
#include "particle/updater.h"
#include "particle/particle.h"

void _basicUpdater(ParticleData* particleData) {

    for (int i = 0; i < particleData->countAlive; i++) {
        particleData->particles[i].pos =
            Vector3Add(particleData->particles[i].pos, Vector3Scale(particleData->particles[i].vel, 0.16f));
    }

}

ParticleUpdater basicUpdater = {&_basicUpdater};
