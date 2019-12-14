#ifndef FILE_EMITTER_SEEN
#define FILE_EMITTER_SEEN
#include <stdint.h>
#include "particle/system.h"
#include "particle/generator.h"

typedef struct ParticleEmitter {
    void (*emit)(ParticleData*, struct ParticleEmitter*);
    intptr_t emitterData;

    ParticleGenerator** generators;
    int countGenerators;
} ParticleEmitter;

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator);

typedef struct BasicEmitterData {
    float emitRate;
    float timeAccumulator;
} BasicEmitterData;

ParticleEmitter getBasicEmitter();

#endif