#include <stdlib.h>
#include <stdio.h>
#include <raymath.h>
#include "particle/particle.h"
#include "particle/system.h"
#include "particle/updater.h"

ParticleSystem* ConstructParticleSystem() {
    ParticleSystem* system = (ParticleSystem*) malloc(sizeof(ParticleSystem));
    system->systemID = 0;

    ParticleData* particleData = (ParticleData*) malloc(sizeof(ParticleData));

    for (int i = 0; i < MAX_PARTICLE_COUNT; ++i) {
        particleData->particles[i].alive = false;
        particleData->particles[i].systemID = 0;
    }

    system->particleData = particleData;
    particleData->countAlive = 0;

    ParticleEmitter** emitters = (ParticleEmitter**) malloc(sizeof(ParticleEmitter*) * 100);

    system->emitters = emitters;
    system->countEmitters = 0;

    ParticleUpdater** updaters = (ParticleUpdater**) malloc(sizeof(ParticleUpdater*) * 100);

    system->updaters = updaters;
    system->countUpdaters = 0;

    ParticleRenderer** renderers = (ParticleRenderer**) malloc(sizeof(ParticleRenderer*) * 100);

    system->renderers = renderers;
    system->countRenderers = 0;

    ParticleSystem** systems = (ParticleSystem**) malloc(sizeof(ParticleSystem*) * 100);

    system->systems = systems;
    system->countSystems = 0;

    return system;
}

void updateParticleSystem(ParticleSystem* system) {

    for (int i = 0; i < system->countEmitters; ++i) {
        emitParticle(system->particleData, system->emitters[i]);
    }

    for (int i = 0; i < system->countUpdaters; ++i) {
        system->updaters[i]->update(system->particleData, system->updaters[i]);
    }

    for (int i = 0; i < system->countSystems; ++i) {
        updateParticleSystem(system->systems[i]);
    }

}

void renderParticleSystem(Camera camera, ParticleSystem* system) {
    for (int i = 0; i < system->countRenderers; ++i) {
        system->renderers[i]->render(camera, system->particleData, system->renderers[i]);
    }

    for (int i = 0; i < system->countSystems; ++i) {
        renderParticleSystem(camera, system->systems[i]);
    }
}

void addParticleEmitter(ParticleSystem* system, ParticleEmitter* emitter) {
    emitter->systemID = system->systemID;
    system->emitters[system->countEmitters] = emitter;

    system->countEmitters = system->countEmitters + 1;
}

void addParticleUpdater(ParticleSystem* system, ParticleUpdater* updater) {
    updater->systemID = system->systemID;
    system->updaters[system->countUpdaters] = updater;

    system->countUpdaters = system->countUpdaters + 1;
}

void addParticleRenderer(ParticleSystem* system, ParticleRenderer* renderer) {
    renderer->systemID = system->systemID;
    system->renderers[system->countRenderers] = renderer;

    system->countRenderers = system->countRenderers + 1;
}

void addParticleSystem(ParticleSystem* system, ParticleSystem* systemToAdd) {
    system->systems[system->countSystems] = systemToAdd;

    system->countSystems = system->countSystems + 1;

    free(systemToAdd->particleData);
    systemToAdd->particleData =system->particleData;
    systemToAdd->systemID = system->countSystems;
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
