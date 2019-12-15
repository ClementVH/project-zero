#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/generator.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void emitParticle(ParticleData* particleData, ParticleEmitter* emitter) {
    int startId = particleData->countAlive;

    emitter->timeBuffer += GetFrameTime();
    emitter->totalTime += GetFrameTime();

    if (emitter->delay > 0.0f && emitter->totalTime < emitter->delay) {
        emitter->timeBuffer = 0.0f;
        return;
    }

    if (emitter->duration > 0.0f && emitter->totalTime >= emitter->duration + emitter->delay) {
        emitter->timeBuffer = 0.0f;
        return;
    }

    if (emitter->timeBuffer > 1.0f / emitter->emitRate) {
        int endId = Clamp(startId + emitter->timeBuffer * emitter->emitRate, startId, MAX_PARTICLE_COUNT);

        for (int i = 0; i < emitter->countGenerators; i++) {
            emitter->generators[i]->generate(particleData, startId, endId, emitter->generators[i]);
        }

        for (int i = startId; i < endId; i++) {
            particleData->countAlive++;
            particleData->particles[i].alive = true;
            particleData->particles[i].size = 0.8f;
        }

        emitter->timeBuffer = 0.0f;

    }
}

ParticleEmitter* ConstructParticleEmitter() {
    ParticleEmitter* emitter = (ParticleEmitter*) malloc(sizeof(ParticleEmitter));

    emitter->emitRate = 1.0f;
    emitter->timeBuffer = 0.0f;

    emitter->totalTime = 0.0f;
    emitter->duration = 0.0f;

    ParticleGenerator** generators = (ParticleGenerator**) malloc(sizeof(ParticleGenerator*) * 100);
    emitter->generators = generators;
    emitter->countGenerators = 0;

    return emitter;
}

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator) {
    emitter->generators[emitter->countGenerators] = generator;
    emitter->countGenerators = emitter->countGenerators + 1;
}
