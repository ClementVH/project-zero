#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>
#include "particle/particle.h"
#include "particle/generator.h"

void sphericalGenerator(ParticleData* particles, int startId, int endId, ParticleGenerator* generator) {
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

        particles->pos[i] = (Vector3) {
            point.x + data->center.x,
            point.y + data->center.y,
            point.z + data->center.z
        };
        particles->vel[i] = Vector3Normalize(point);
    }
}

ParticleGenerator getSphericalGenerator() {
    SphericalGeneratorData* data = malloc(sizeof(SphericalGeneratorData));
    ParticleGenerator generator = {&sphericalGenerator, (intptr_t)data};
    return generator;
}
