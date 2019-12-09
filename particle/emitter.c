#include "particle/system.h"
#include "particle/emitter.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct BasicEmitterData {
    float emitRate;
    float timeAccumulator;
} BasicEmitterData;

void _basicEmitter(ParticleData* particles, intptr_t emitterData) {
    BasicEmitterData* data = (BasicEmitterData*) emitterData;
    int startId = particles->countAlive;

    float deltaTimeAccumulated = GetFrameTime() + data->timeAccumulator;

    if (deltaTimeAccumulated > data->emitRate) {
        data->timeAccumulator = 0.0f;

        int endId = Clamp(startId + data->emitRate, startId, MAX_PARTICLE_COUNT);

        for (int i = startId; i < endId; i++) {
            particles->countAlive++;
            particles->pos[i] = (Vector3){1.0f, 1.0f, 1.0f};
            particles->size[i] = 0.8f;
        }

    } else {
        data->timeAccumulator = deltaTimeAccumulated;
    }
}

ParticleEmitter getBasicEmitter() {
    BasicEmitterData* data = malloc(sizeof(BasicEmitterData));
    data->emitRate = 1.0f;
    data->timeAccumulator = 0.0f;
    ParticleEmitter basicEmitter = { &_basicEmitter, (intptr_t)(data) };
    return basicEmitter;
}
