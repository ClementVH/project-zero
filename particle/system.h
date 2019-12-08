#ifndef FILE_SYSTEM_SEEN
#define FILE_SYSTEM_SEEN

#include "particle/particle.h"
#include "particle/emitter.h"

typedef struct ParticleSystem {
    ParticleData* particles;
    ParticleEmitter* emitters;
    int countEmitters;
} ParticleSystem;

ParticleSystem* ConstructParticleSystem();
void updateParticleSystem(ParticleSystem* system);
void addParticleEmitter(ParticleSystem* system, ParticleEmitter emitter);

#endif
