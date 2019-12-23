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
    ParticleGenerator* sphericalGenerator = getSphericalGenerator(Vector3Zero(), 1.0f, false);
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

    Vector2* controlPoints = malloc(sizeof(Vector2) * 4);
    controlPoints[0] = (Vector2){0.0f, 0.0f};
    controlPoints[1] = (Vector2){0.0f, 1.0f};
    controlPoints[2] = (Vector2){0.0f, 1.5f};
    controlPoints[3] = (Vector2){1.0f, 0.1f};
    ParticleUpdater* alphaUpdater = getAlphaUpdater(controlPoints, 4);
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

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(0.3f, 0.6f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(1.0f, 1.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(BLUE);
    addParticleGenerator(emitter, colorGenerator);

    ParticleGenerator* speedGenerator = getSpeedGenerator(0.16f, 0.32f);
    addParticleGenerator(emitter, speedGenerator);

    ParticleUpdater* newtonUpdater = getNewtonUpdater();
    addParticleUpdater(sparks, newtonUpdater);

    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(sparks, timeUpdater);

    Vector2* controlPoints = malloc(sizeof(Vector2) * 4);
    controlPoints[0] = (Vector2){0.0f, 0.0f};
    controlPoints[1] = (Vector2){0.0f, 1.0f};
    controlPoints[2] = (Vector2){0.0f, 1.5f};
    controlPoints[3] = (Vector2){1.0f, 0.1f};
    ParticleUpdater* alphaUpdater = getAlphaUpdater(controlPoints, 4);
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

    ParticleGenerator* lifeTimeGenerator = getLifeTimeGenerator(0.3f, 0.6f);
    addParticleGenerator(emitter, lifeTimeGenerator);

    ParticleGenerator* sizeGenerator = getSizeGenerator(4.0f, 4.0f);
    addParticleGenerator(emitter, sizeGenerator);

    ParticleGenerator* colorGenerator = getColorGenerator(BLUE);
    addParticleGenerator(emitter, colorGenerator);

    ParticleUpdater* timeUpdater = getTimeUpdater();
    addParticleUpdater(shockWave, timeUpdater);

    float cpxsSize[5] = { 0.00f, 0.12f, 0.18f, 0.26f, 1.00f };
    float cpysSize[5] = { 0.00f, 0.54f, 0.65f, 0.75f, 1.00f };
    ParticleUpdater* sizeUpdater = getSizeUpdater(cpxsSize, cpysSize, 5);
    addParticleUpdater(shockWave, sizeUpdater);

    Vector2* controlPoints = malloc(sizeof(Vector2) * 4);
    controlPoints[0] = (Vector2){0.0f, 0.0f};
    controlPoints[1] = (Vector2){0.0f, 1.0f};
    controlPoints[2] = (Vector2){0.0f, 1.5f};
    controlPoints[3] = (Vector2){1.0f, 0.1f};
    ParticleUpdater* alphaUpdater = getAlphaUpdater(controlPoints, 4);
    addParticleUpdater(shockWave, alphaUpdater);

    Texture2D texture = LoadTexture("assets/particle/circle-glow.png");
    ParticleRenderer* renderer = getBillboardRenderer(texture);
    addParticleRenderer(shockWave, renderer);

    return shockWave;
}