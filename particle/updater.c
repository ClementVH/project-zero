#include <stdlib.h>
#include <raymath.h>
#include "particle/updater.h"
#include "particle/particle.h"
#include "utils/binary-search.h"
#include "utils/bezier.h"
#include "utils/cubic-spline.h"
#include "particle/macros.h"

#define forParticlesInSystem(endId, particleData, systemID) for(int i = 0; i < endId; i++) {\
    if (particleData->particles[i].systemID != systemID)\
        continue;\

#define endForParticlesInSystem }

ParticleUpdater* ConstructUpdater(void* update, intptr_t data) {
    ParticleUpdater* updater = malloc(sizeof(ParticleUpdater));
    updater->update = update;
    updater->updaterData = data;

    return updater;
}

void newtonUpdater(ParticleData* particleData, ParticleUpdater* updater) {
    int systemID = updater->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        Vector3 vel = particleData->particles[i].vel;
        // vel = Vector3Multiply(vel, 0.1f);
        particleData->particles[i].pos = Vector3Add(particleData->particles[i].pos, vel);
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

    int systemID = updater->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        // timeElapsed = timeElapsed / 10.0f;
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
    BezierCurveData* data = (BezierCurveData*) updater->updaterData;

    int endId = particleData->countAlive;

    if (endId == 0) return;

    int systemID = updater->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        float x = particleData->particles[i].lifeTime / particleData->particles[i].maxLifeTime;
        int closestIndex = findClosest(data->curveX, 1000, x);

        particleData->particles[i].color.a = 255.0f * data->curveY[closestIndex];
    }
}

ParticleUpdater* getAlphaUpdater(Vector2* controlPoints, int nbControlPoints) {
    BezierCurve curve = bezier(1000, 0.001f, nbControlPoints - 1, controlPoints);

    BezierCurveData* data = malloc(sizeof(BezierCurveData));
    data->curveX = curve.curveX;
    data->curveY = curve.curveY;

    ParticleUpdater* updater = ConstructUpdater(&alphaUpdater, (intptr_t) data);
    return updater;
}

void sizeUpdater(ParticleData* particleData, ParticleUpdater* updater) {
    SizeUpdaterData* data = (SizeUpdaterData*) updater->updaterData;

    int endId = particleData->countAlive;

    if (endId == 0) return;

    int systemID = updater->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        float ratioLifeTime = particleData->particles[i].lifeTime / particleData->particles[i].maxLifeTime;
        int indexCurveSpline = ratioLifeTime * 1000;
        Particle* particle = &particleData->particles[i];
        particle->size = particle->_size * data->spline.ys[indexCurveSpline];
    }

}

ParticleUpdater* getSizeUpdater(float* cpxs, float* cpys, int nbControlPoints) {
    SizeUpdaterData* data = malloc(sizeof(SizeUpdaterData));

    CubicSpline* spline = ConstructCubicSpline(nbControlPoints, cpxs, cpys);
    data->spline = *spline;
    free(spline);

    ParticleUpdater* updater = ConstructUpdater(&sizeUpdater, (intptr_t)data);
    return updater;
}