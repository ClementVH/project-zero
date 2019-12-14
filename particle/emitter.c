#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/generator.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void emitParticle(ParticleData* particles, ParticleEmitter* emitter) {
    int startId = particles->countAlive;

    float deltaTimeAccumulated = GetFrameTime() + emitter->timeAccumulator;

    if (deltaTimeAccumulated > 1.0f / emitter->emitRate) {
        emitter->timeAccumulator = 0.0f;

        int endId = Clamp(startId + deltaTimeAccumulated * emitter->emitRate, startId, MAX_PARTICLE_COUNT);


        for (int i = 0; i < emitter->countGenerators; i++) {
            emitter->generators[i]->generate(particles, startId, endId, emitter->generators[i]);
        }

        for (int i = startId; i < endId; i++) {
            particles->countAlive++;
            particles->alive[i] = true;
            particles->size[i] = 0.8f;
        }

    } else {
        emitter->timeAccumulator = deltaTimeAccumulated;
    }
}

ParticleEmitter* ConstructParticleEmitter() {
    ParticleEmitter* emitter = (ParticleEmitter*) malloc(sizeof(ParticleEmitter));

    emitter->emitRate = 1.0f;
    emitter->timeAccumulator = 0.0f;

    ParticleGenerator** generators = (ParticleGenerator**) malloc(sizeof(ParticleGenerator*) * 100);
    emitter->generators = generators;
    emitter->countGenerators = 0;

    return emitter;
}

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator) {
    emitter->generators[emitter->countGenerators] = generator;
    emitter->countGenerators = emitter->countGenerators + 1;
}
