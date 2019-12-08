#ifndef FILE_EMITTER_SEEN
#define FILE_EMITTER_SEEN
#include "particle/system.h"
#include "particle/generator.h"

typedef struct ParticleEmitter {
    void (*emit)(ParticleData*);
} ParticleEmitter;

ParticleEmitter addGenerator(ParticleGenerator* generator);
ParticleEmitter basicEmitter;

#endif