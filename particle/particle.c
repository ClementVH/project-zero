#include "particle/particle.h"

void swapParticles(ParticleData* particleData, int index1, int index2) {
    Particle temp = particleData->particles[index1];

    Particle* p1 = particleData->particles;
    p1 += index1;
    Particle* p2 = particleData->particles;
    p2 += index2;

    *p1 = *p2;
    *p2 = temp;
}

void killParticle(ParticleData* particleData, int particleIndex) {
    if (particleData->countAlive > 0) {
        particleData->particles[particleIndex].alive = false;
        swapParticles(particleData, particleIndex, particleData->countAlive - 1);
        particleData->countAlive--;
    }
}