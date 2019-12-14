#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/generator.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void emitParticle(ParticleData* particles, ParticleEmitter* emitter) {
    int startId = particles->countAlive;

    if (emitter->duration > 0.0f && emitter->totalTime >= emitter->duration) {
        return;
    }

    if (emitter->timeBuffer > 1.0f / emitter->emitRate) {
        int endId = Clamp(startId + emitter->timeBuffer * emitter->emitRate, startId, MAX_PARTICLE_COUNT);

        for (int i = 0; i < emitter->countGenerators; i++) {
            emitter->generators[i]->generate(particles, startId, endId, emitter->generators[i]);
        }

        for (int i = startId; i < endId; i++) {
            particles->countAlive++;
            particles->alive[i] = true;
            particles->size[i] = 0.8f;
        }

        emitter->timeBuffer = 0.0f;

    }

    emitter->timeBuffer += GetFrameTime();
    emitter->totalTime += GetFrameTime();
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
