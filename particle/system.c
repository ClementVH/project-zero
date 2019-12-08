#include "stdlib.h"
#include "stdio.h"
#include "particle/particle.h"
#include "particle/system.h"

ParticleSystem* ConstructParticleSystem() {
    ParticleSystem* system = (ParticleSystem*) malloc(sizeof(ParticleSystem));

    ParticleData* particles = (ParticleData*) malloc(sizeof(ParticleData));

    for (int i = 0; i < MAX_PARTICLE_COUNT; ++i) {
        particles->alive[i] = false;
    }

    system->particles = particles;
    particles->countAlive = 0;

    ParticleEmitter* emitters = (ParticleEmitter*) malloc(sizeof(ParticleEmitter));

    system->emitters = emitters;
    system->countEmitters = 0;

    return system;
}

void updateParticleSystem(ParticleSystem* system) {

    for (int i = 0; i < system->countEmitters; ++i) {
        system->emitters[i].emit(system->particles);
    }

}

void addParticleEmitter(ParticleSystem* system, ParticleEmitter emitter) {

    system->emitters[system->countEmitters] = emitter;

    system->countEmitters = system->countEmitters + 1;
}
