#include "particle/particle.h"
#include "particle/emitter.h"

#define MAX_PARTICLE_COUNT 100

typedef struct ParticleSystem {
    Particle particles[MAX_PARTICLE_COUNT];
    ParticleEmitter* emitters;
} ParticleSystem;

ParticleSystem ConstructParticleSystem();
void updateParticleSystem(ParticleSystem system);
