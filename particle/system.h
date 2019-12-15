#ifndef FILE_SYSTEM_SEEN
#define FILE_SYSTEM_SEEN

#include "particle/particle.h"
#include "particle/emitter.h"
#include "particle/updater.h"

typedef struct ParticleSystem {
    ParticleData* particleData;
    ParticleEmitter** emitters;
    int countEmitters;
    ParticleUpdater** updaters;
    int countUpdaters;
} ParticleSystem;

ParticleSystem* ConstructParticleSystem();

void updateParticleSystem(ParticleSystem* system);

void addParticleEmitter(ParticleSystem* system, ParticleEmitter* emitter);
void addParticleUpdater(ParticleSystem* system, ParticleUpdater* updater);

void sortParticles(ParticleSystem*, Camera);

#endif
