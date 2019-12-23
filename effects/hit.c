#include <stdlib.h>
#include <raymath.h>
#include "particle/system.h"
#include "particle/emitter.h"
#include "particle/updater.h"
#include "particle/generator.h"
#include "particle/renderer.h"
#include "effects/hit.h"

ParticleSystem* ConstructFlashEffect(Vector3, ParticleSystem*);
ParticleSystem* ConstructSparksEffect(Vector3, ParticleSystem*);
ParticleSystem* ConstructShockWaveEffect(Vector3, ParticleSystem*);

ParticleSystem* ConstructHitEffect(Vector3 center) {
    ParticleSystem* hit = ConstructParticleSystem();

    ConstructFlashEffect(center, hit);
    ConstructSparksEffect(center, hit);
    ConstructShockWaveEffect(center, hit);

    return hit;
}


ParticleSystem* ConstructFlashEffect(Vector3 center, ParticleSystem* parent) {

    ParticleSystem* flash = ConstructParticleSystem();
    addParticleSystem(parent, flash);

    ParticleEmitter* emitter = ConstructParticleEmitter();
    emitter->burst = true;
    emitter->burstMin = 1;

    // Generators
    ParticleGenerator* sphericalGenerator = getSphericalGenerator(center, 1.0f, false);
    addParticleGenerator(emitter, sphericalGenerator);

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(0.3f, 0.3f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(4.0f, 4.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(BLUE);
    addParticleGenerator(emitter, colorGenerator);

    addParticleEmitter(flash, emitter);

    // Updaters
    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(flash, timeUpdater);

    float cpxsAlpha[5] = { 0.00f, 0.30f, 0.58f, 0.70f, 1.00f };
    float cpysAlpha[5] = { 0.72f, 0.96f, 0.95f, 0.84f, 0.00f };
    ParticleUpdater* alphaUpdater = getAlphaUpdater(cpxsAlpha, cpysAlpha, 4);
    addParticleUpdater(flash, alphaUpdater);

    Texture2D texture = LoadTexture("assets/particle/point-light.png");
    ParticleRenderer* renderer = getBillboardRenderer(texture);
    addParticleRenderer(flash, renderer);

    return flash;
}

ParticleSystem* ConstructSparksEffect(Vector3 center, ParticleSystem* parent) {

    ParticleSystem* sparks = ConstructParticleSystem();
    addParticleSystem(parent, sparks);

    ParticleEmitter* emitter = ConstructParticleEmitter();
    emitter->burst = true;
    emitter->burstMin = 20;
    addParticleEmitter(sparks, emitter);

    ParticleGenerator* sphericalGenerator = getSphericalGenerator(center, 1.0f, false);
    addParticleGenerator(emitter, sphericalGenerator);

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(0.2f, 0.5f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(1.0f, 1.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(BLUE);
    addParticleGenerator(emitter, colorGenerator);

    ParticleGenerator* speedGenerator = getSpeedGenerator(0.16f, 0.25f);
    addParticleGenerator(emitter, speedGenerator);

    ParticleUpdater* newtonUpdater = getNewtonUpdater();
    addParticleUpdater(sparks, newtonUpdater);

    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(sparks, timeUpdater);


    float cpxsAlpha[4] = { 0.00f, 0.88f, 0.93f, 1.00f };
    float cpysAlpha[4] = { 1.00f, 0.93f, 0.84f, 0.00f };
    ParticleUpdater* alphaUpdater = getAlphaUpdater(cpxsAlpha, cpysAlpha, 4);
    addParticleUpdater(sparks, alphaUpdater);

    Texture2D texture = LoadTexture("assets/particle/point-light.png");
    ParticleRenderer* renderer = getStretchedBillboardRenderer(texture);
    addParticleRenderer(sparks, renderer);

    return sparks;
}

ParticleSystem* ConstructShockWaveEffect(Vector3 center, ParticleSystem* parent) {
    ParticleSystem* shockWave = ConstructParticleSystem();
    addParticleSystem(parent, shockWave);

    ParticleEmitter* emitter = ConstructParticleEmitter();
    emitter->burst = true;
    emitter->burstMin = 1;
    addParticleEmitter(shockWave, emitter);

    ParticleGenerator* sphericalGenerator = getSphericalGenerator(center, 1.0f, false);
    addParticleGenerator(emitter, sphericalGenerator);

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(0.4f, 0.4f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(4.0f, 4.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(BLUE);
    addParticleGenerator(emitter, colorGenerator);

    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(shockWave, timeUpdater);

    float cpxsSize[4] = { 0.00f, 0.38f, 0.56f, 1.00f };
    float cpysSize[4] = { 0.00f, 0.80f, 0.92f, 1.00f };
    ParticleUpdater* sizeUpdater = getSizeUpdater(cpxsSize, cpysSize, 4);
    addParticleUpdater(shockWave, sizeUpdater);

    float cpxsAlpha[5] = { 0.00f, 0.30f, 0.58f, 0.70f, 1.00f };
    float cpysAlpha[5] = { 0.72f, 0.96f, 0.95f, 0.84f, 0.00f };
    ParticleUpdater* alphaUpdater = getAlphaUpdater(cpxsAlpha, cpysAlpha, 4);
    addParticleUpdater(shockWave, alphaUpdater);

    Texture2D texture = LoadTexture("assets/particle/circle-glow.png");
    ParticleRenderer* renderer = getBillboardRenderer(texture);
    addParticleRenderer(shockWave, renderer);

    return shockWave;
}