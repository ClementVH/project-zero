#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/generator.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void _basicEmitter(ParticleData* particles, intptr_t pemitter) {
    ParticleEmitter* emitter = (ParticleEmitter*) pemitter;
    BasicEmitterData* data = (BasicEmitterData*) emitter->emitterData;
    int startId = particles->countAlive;

    float deltaTimeAccumulated = GetFrameTime() + data->timeAccumulator;

    if (deltaTimeAccumulated > 1.0f / data->emitRate) {
        data->timeAccumulator = 0.0f;

        int endId = Clamp(startId + deltaTimeAccumulated * data->emitRate, startId, MAX_PARTICLE_COUNT);


        for (int i = 0; i < emitter->countGenerators; i++) {
            emitter->generators[i]->generate(particles, startId, endId, (intptr_t)emitter->generators[i]);
        }

        for (int i = startId; i < endId; i++) {
            particles->countAlive++;
            particles->alive[i] = true;
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
    ParticleGenerator** generators = (ParticleGenerator**) malloc(sizeof(ParticleGenerator*) * 100);
    ParticleEmitter basicEmitter = { &_basicEmitter, (intptr_t)(data), generators, 0 };
    return basicEmitter;
}

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator) {
    emitter->generators[emitter->countGenerators] = generator;
    emitter->countGenerators = emitter->countGenerators + 1;
}
