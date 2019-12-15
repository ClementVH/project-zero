#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>
#include "particle/particle.h"
#include "particle/generator.h"

void sphericalGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    SphericalGeneratorData* data = (SphericalGeneratorData*) generator->generatorData;

    for (int i = startId; i < endId; i++) {

        float lambda = (float)(rand() % 360 - 180);

        float x = ((float)rand()/(float)(RAND_MAX));
        float phi = acosf(2 * x - 1);
        Vector3 point = (Vector3) {
            data->radius * sinf(phi) * cosf(lambda),
            data->radius * sinf(phi) * sinf(lambda),
            data->radius * cosf(phi)
        };

        particleData->particles[i].pos = (Vector3) {
            point.x + data->center.x,
            point.y + data->center.y,
            point.z + data->center.z
        };
        particleData->particles[i].vel = Vector3Normalize(point);
    }
}

ParticleGenerator getSphericalGenerator() {
    SphericalGeneratorData* data = malloc(sizeof(SphericalGeneratorData));
    ParticleGenerator generator = {&sphericalGenerator, (intptr_t)data};
    return generator;
}

void lifeTimeGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    LifeTimeGeneratorData* data = (LifeTimeGeneratorData*) generator->generatorData;

    float interval = data->maxTime - data->minTime;

    for (int i = startId; i < endId; i++) {
        float time = ((float)rand()/(float)(RAND_MAX)) * interval + data->minTime;
        particleData->particles[i].lifeTime = time;
    }
}

ParticleGenerator getLifeTimeGenerator() {
    LifeTimeGeneratorData* data = malloc(sizeof(LifeTimeGeneratorData));
    ParticleGenerator generator = {&lifeTimeGenerator, (intptr_t)data};
    return generator;
}

void speedGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    SpeedGeneratorData* data = (SpeedGeneratorData*) generator->generatorData;

    float interval = data->maxSpeed - data->minSpeed;

    for (int i = startId; i < endId; i++) {
        float speed = ((float)rand()/(float)(RAND_MAX)) * interval + data->minSpeed;
        particleData->particles[i].vel = Vector3Scale(particleData->particles[i].vel, speed);
    }
}

ParticleGenerator getSpeedGenerator(float minSpeed, float maxSpeed) {
    SpeedGeneratorData* data = malloc(sizeof(SpeedGeneratorData));
    data->minSpeed = minSpeed;
    data->maxSpeed = maxSpeed;
    ParticleGenerator generator = {&speedGenerator, (intptr_t)data};
    return generator;
}
