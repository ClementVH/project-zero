#include "particle/system.h"
#include "particle/emitter.h"
#include "raymath.h"
#include "raylib.h"

void _basicEmitter(ParticleData* particles) {
    int maxNewParticles = 1;
    int startId = particles->countAlive;
    int endId = Clamp(startId + maxNewParticles, startId, MAX_PARTICLE_COUNT);

    for (int i = startId; i < endId; i++) {
        particles->countAlive++;
        particles->pos[i] = (Vector3){1.0f, 1.0f, 1.0f};
        particles->size[i] = 0.8f;
    }
}

ParticleEmitter basicEmitter = { &_basicEmitter };
