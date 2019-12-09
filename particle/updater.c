#include "particle/updater.h"
#include "particle/particle.h"

void _basicUpdater(ParticleData* particles) {

    for (int i = 0; i < particles->countAlive; i++) {
        particles->pos[i].y += 0.16f;
    }

}

ParticleUpdater basicUpdater = {&_basicUpdater};
