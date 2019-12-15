#include <stdlib.h>
#include <stdio.h>
#include <raymath.h>
#include "particle/particle.h"
#include "particle/system.h"
#include "particle/updater.h"

ParticleSystem* ConstructParticleSystem() {
    ParticleSystem* system = (ParticleSystem*) malloc(sizeof(ParticleSystem));

    ParticleData* particleData = (ParticleData*) malloc(sizeof(ParticleData));

    for (int i = 0; i < MAX_PARTICLE_COUNT; ++i) {
        particleData->particles[i].alive = false;
    }

    system->particleData = particleData;
    particleData->countAlive = 0;

    ParticleEmitter** emitters = (ParticleEmitter**) malloc(sizeof(ParticleEmitter*) * 100);

    system->emitters = emitters;
    system->countEmitters = 0;

    ParticleUpdater** updaters = (ParticleUpdater**) malloc(sizeof(ParticleUpdater*) * 100);

    system->updaters = updaters;
    system->countUpdaters = 0;

    return system;
}

void updateParticleSystem(ParticleSystem* system) {

    for (int i = 0; i < system->countEmitters; ++i) {
        emitParticle(system->particleData, system->emitters[i]);
    }

    for (int i = 0; i < system->countUpdaters; ++i) {
        system->updaters[i]->update(system->particleData);
    }

}

void addParticleEmitter(ParticleSystem* system, ParticleEmitter* emitter) {

    system->emitters[system->countEmitters] = emitter;

    system->countEmitters = system->countEmitters + 1;
}

void addParticleUpdater(ParticleSystem* system, ParticleUpdater* updater) {

    system->updaters[system->countUpdaters] = updater;

    system->countUpdaters = system->countUpdaters + 1;
}

int comp (const void * elem1, const void * elem2)
{
    Particle f = *((Particle*)elem1);
    Particle s = *((Particle*)elem2);
    if (f.cameraDistance > s.cameraDistance) return  -1;
    if (f.cameraDistance <= s.cameraDistance) return 1;
    return 0;
}

void sortParticles(ParticleSystem* system, Camera camera) {

    for (int i = 0; i < system->particleData->countAlive; i++) {
        system->particleData->particles[i].cameraDistance =
            Vector3Distance(system->particleData->particles[i].pos, camera.position);
    }


    Particle* particles = system->particleData->particles;
    qsort(particles, system->particleData->countAlive, sizeof(Particle), comp);
}
