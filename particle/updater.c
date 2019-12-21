#include <stdlib.h>
#include <raymath.h>
#include "particle/updater.h"
#include "particle/particle.h"
#include "utils/binary-search.h"
#include "utils/bezier.h"

ParticleUpdater* ConstructUpdater(void* update, intptr_t data) {
    ParticleUpdater* updater = malloc(sizeof(ParticleUpdater));
    updater->update = update;
    updater->updaterData = data;

    return updater;
}

void newtonUpdater(ParticleData* particleData, ParticleUpdater* updater) {
    for (int i = 0; i < particleData->countAlive; i++) {
        particleData->particles[i].pos = Vector3Add(particleData->particles[i].pos, particleData->particles[i].vel);
    }
}

ParticleUpdater* getNewtonUpdater() {
    ParticleUpdater* updater = ConstructUpdater(&newtonUpdater, 0);
    return updater;
}

void timeUpdater(ParticleData* particleData, ParticleUpdater* updater) {
    int endId = particleData->countAlive;
    float timeElapsed = GetFrameTime();

    if (endId == 0) return;

    for (int i = 0; i < endId; i++) {
        particleData->particles[i].lifeTime += timeElapsed;

        if (particleData->particles[i].lifeTime > particleData->particles[i].maxLifeTime) {
            killParticle(particleData, i);
            endId = particleData->countAlive;
            i--;
        }
    }
}

ParticleUpdater* getTimeUpdater() {
    ParticleUpdater* updater = ConstructUpdater(&timeUpdater, 0);
    return updater;
}

void alphaUpdater(ParticleData* particleData, ParticleUpdater* updater) {
    AlphaUpdaterData* data = (AlphaUpdaterData*) updater->updaterData;

    int endId = particleData->countAlive;

    if (endId == 0) return;

    for (int i = 0; i < endId; i++) {
        float x = particleData->particles[i].lifeTime / particleData->particles[i].maxLifeTime;
        int closestIndex = findClosest(data->curveX, 1000, x);

        particleData->particles[i].color.a = 255.0f * data->curveY[closestIndex];
    }
}

ParticleUpdater* getAlphaUpdater() {
    AlphaUpdaterData* data = malloc(sizeof(AlphaUpdaterData));

    Vector2* controlPoints = malloc(sizeof(Vector2) * 4);
    controlPoints[0] = (Vector2){0.0f, 0.0f};
    controlPoints[1] = (Vector2){0.0f, 1.0f};
    controlPoints[2] = (Vector2){0.0f, 1.5f};
    controlPoints[3] = (Vector2){1.0f, 0.1f};


    BezierCurve curve = bezier(1000, 0.001f, 3, controlPoints);

    data->curveX = curve.curveX;
    data->curveY = curve.curveY;

    ParticleUpdater* updater = ConstructUpdater(&alphaUpdater, (intptr_t) data);
    return updater;
}