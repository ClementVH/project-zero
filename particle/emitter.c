#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/generator.h"
#include "raymath.h"
#include "raylib.h"
#include <stdint.h>
#include <stdlib.h>

void emit(ParticleData* particleData, ParticleEmitter* emitter, int startId, int endId) {

    for (int i = 0; i < emitter->countGenerators; i++) {
        emitter->generators[i]->generate(particleData, startId, endId, emitter->generators[i]);
    }

    for (int i = startId; i < endId; i++) {
        particleData->countAlive++;
        particleData->particles[i].alive = true;
    }
}

void emitBurst(ParticleData* particleData, ParticleEmitter* emitter) {
    int startId = particleData->countAlive;

    int endId = Clamp(startId + emitter->burstMin, startId, MAX_PARTICLE_COUNT);
    emit(particleData, emitter, startId, endId);
    emitter->active = false;
}

void emitOverTime(ParticleData* particleData, ParticleEmitter* emitter) {
    int startId = particleData->countAlive;

    if (emitter->duration > 0.0f && emitter->totalTime >= emitter->duration + emitter->delay) {
        emitter->active = false;
        return;
    }

    if (emitter->timeBuffer > 1.0f / emitter->emitRate) {
        int endId = Clamp(startId + emitter->timeBuffer * emitter->emitRate, startId, MAX_PARTICLE_COUNT);
        emit(particleData, emitter, startId, endId);
        emitter->timeBuffer = 0.0f;
    }
}

void emitParticle(ParticleData* particleData, ParticleEmitter* emitter) {
    emitter->totalTime += GetFrameTime();

    if (!emitter->active || (emitter->delay > 0.0f && emitter->totalTime < emitter->delay)) {
        return;
    }

    if (emitter->burst) {
        return emitBurst(particleData, emitter);
    } else {
        emitter->timeBuffer += GetFrameTime();
        return emitOverTime(particleData, emitter);
    }
}

ParticleEmitter* ConstructParticleEmitter() {
    ParticleEmitter* emitter = (ParticleEmitter*) malloc(sizeof(ParticleEmitter));

    emitter->active = true;

    emitter->emitRate = 1.0f;
    emitter->timeBuffer = 0.0f;

    emitter->totalTime = 0.0f;
    emitter->duration = 0.0f;

    emitter->delay = 0.0f;

    ParticleGenerator** generators = (ParticleGenerator**) malloc(sizeof(ParticleGenerator*) * 100);
    emitter->generators = generators;
    emitter->countGenerators = 0;

    return emitter;
}

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator) {
    emitter->generators[emitter->countGenerators] = generator;
    emitter->countGenerators = emitter->countGenerators + 1;
}
