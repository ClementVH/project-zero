#include "particle/particle.h"
#include "particle/system.h"

ParticleSystem ConstructParticleSystem() {
    Particle particles[MAX_PARTICLE_COUNT] = { 0 };

    for (int i = 0; i < MAX_PARTICLE_COUNT; ++i) {
		particles[i].alive = false;
    }
}

void updateParticleSystem(ParticleSystem system) {

}
