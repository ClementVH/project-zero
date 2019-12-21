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

        Vector3 pos = (Vector3) {0.0f};

        if (data->fromShell) {
            pos.x = point.x + data->center.x;
            pos.y = point.y + data->center.y;
            pos.z = point.z + data->center.z;
        } else {
            pos.x = data->center.x;
            pos.y = data->center.y;
            pos.z = data->center.z;
        }

        particleData->particles[i].pos = pos;
        particleData->particles[i].vel = Vector3Normalize(point);
    }
}

ParticleGenerator getSphericalGenerator() {
    SphericalGeneratorData* data = malloc(sizeof(SphericalGeneratorData));
    data->fromShell = false;
    ParticleGenerator generator = {&sphericalGenerator, (intptr_t)data};
    return generator;
}

void lifeTimeGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    LifeTimeGeneratorData* data = (LifeTimeGeneratorData*) generator->generatorData;

    float interval = data->maxTime - data->minTime;

    for (int i = startId; i < endId; i++) {
        float time = ((float)rand()/(float)(RAND_MAX)) * interval + data->minTime;
        particleData->particles[i].maxLifeTime = time;
        particleData->particles[i].lifeTime = 0.0f;
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

void sizeGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    SizeGeneratorData* data = (SizeGeneratorData*) generator->generatorData;

    float interval = data->maxSize - data->minSize;

    for (int i = startId; i < endId; i++) {
        float size = ((float)rand()/(float)(RAND_MAX)) * interval + data->minSize;
        particleData->particles[i].size = size;
    }
}

ParticleGenerator getSizeGenerator(float minSize, float maxSize) {
    SizeGeneratorData* data = malloc(sizeof(SizeGeneratorData));
    data->minSize = minSize;
    data->maxSize = maxSize;
    ParticleGenerator generator = {&sizeGenerator, (intptr_t)data};
    return generator;
}

void colorGenerator(ParticleData* particleData, int startId, int endId, ParticleGenerator* generator) {
    ColorGeneratorData* data = (ColorGeneratorData*) generator->generatorData;

    for (int i = startId; i < endId; i++) {
        particleData->particles[i].color = data->color;
    }
}

ParticleGenerator getColorGenerator(Color color) {
    ColorGeneratorData* data = malloc(sizeof(ColorGeneratorData));
    data->color = color;
    ParticleGenerator generator = {&colorGenerator, (intptr_t)data};
    return generator;
}
