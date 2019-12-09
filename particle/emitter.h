#ifndef FILE_EMITTER_SEEN
#define FILE_EMITTER_SEEN
#include "particle/system.h"
#include "particle/generator.h"
#include <stdint.h>

typedef struct ParticleEmitter {
    void (*emit)(ParticleData*, intptr_t);
    intptr_t emitterData;
} ParticleEmitter;

ParticleEmitter addGenerator(ParticleGenerator* generator);
ParticleEmitter getBasicEmitter();

#endif