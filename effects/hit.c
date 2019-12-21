#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/updater.h"
#include "particle/generator.h"
#include "effects/hit.h"
#include "raymath.h"

ParticleSystem* ConstructHitEffect(Vector3 center) {
    ParticleSystem* system = ConstructParticleSystem();

    ParticleEmitter* emitter = ConstructParticleEmitter();
    emitter->delay = 1.0f;
    emitter->burst = true;
    emitter->burstMin = 1;

    // Generators
    ParticleGenerator* sphericalGenerator = getSphericalGenerator(Vector3Zero(), 1.0f, false);
    addParticleGenerator(emitter, sphericalGenerator);

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(1.0f, 1.0f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(5.0f, 5.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(RED);
    addParticleGenerator(emitter, colorGenerator);

    addParticleEmitter(system, emitter);

    // Updaters
    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(system, timeUpdater);

    ParticleUpdater* alphaUpdater = getAlphaUpdater();
    addParticleUpdater(system, alphaUpdater);

    return system;
}
