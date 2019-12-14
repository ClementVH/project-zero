#ifndef FILE_EMITTER_SEEN
#define FILE_EMITTER_SEEN
#include "particle/system.h"
#include "particle/generator.h"

typedef struct ParticleEmitter {
    float emitRate;
    float timeBuffer;

    float totalTime;
    float duration;
    float delay;

    ParticleGenerator** generators;
    int countGenerators;
} ParticleEmitter;

ParticleEmitter* ConstructParticleEmitter();

void emitParticle(ParticleData*, ParticleEmitter*);

void addParticleGenerator(ParticleEmitter* emitter, ParticleGenerator* generator);
#endif