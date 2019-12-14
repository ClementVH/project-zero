#include "raymath.h"
#include "particle/updater.h"
#include "particle/particle.h"

void _basicUpdater(ParticleData* particles) {

    for (int i = 0; i < particles->countAlive; i++) {
        particles->pos[i] = Vector3Add(particles->pos[i], Vector3Scale(particles->vel[i], 0.16f));
    }

}

ParticleUpdater basicUpdater = {&_basicUpdater};
