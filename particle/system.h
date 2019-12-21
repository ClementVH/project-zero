#ifndef FILE_SYSTEM_SEEN
#define FILE_SYSTEM_SEEN

#include "particle/particle.h"
#include "particle/emitter.h"
#include "particle/updater.h"
#include "particle/renderer.h"

typedef struct ParticleSystem {
    int systemID;

    ParticleData* particleData;

    ParticleEmitter** emitters;
    int countEmitters;

    ParticleUpdater** updaters;
    int countUpdaters;

    ParticleRenderer** renderers;
    int countRenderers;

    struct ParticleSystem** systems;
    int countSystems;
} ParticleSystem;

ParticleSystem* ConstructParticleSystem();

void updateParticleSystem(ParticleSystem*);
void renderParticleSystem(Camera, ParticleSystem*);

void addParticleEmitter(ParticleSystem*, ParticleEmitter*);
void addParticleUpdater(ParticleSystem*, ParticleUpdater*);
void addParticleRenderer(ParticleSystem*, ParticleRenderer*);
void addParticleSystem(ParticleSystem*, ParticleSystem*);

void sortParticles(ParticleSystem*, Camera);

#endif
