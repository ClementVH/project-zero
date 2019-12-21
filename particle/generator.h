#ifndef FILE_GENERATOR_SEEN
#define FILE_GENERATOR_SEEN
#include <stdint.h>
#include <raylib.h>
#include "particle/particle.h"

typedef struct ParticleGenerator {
    void (*generate)(ParticleData*, int, int, struct ParticleGenerator*);
    intptr_t generatorData;
} ParticleGenerator;

ParticleGenerator* getSphericalGenerator(Vector3 center, float radius, bool fromShell);

typedef struct SphericalGeneratorData {
    Vector3 center;
    float radius;
    bool fromShell;
} SphericalGeneratorData;

ParticleGenerator getLifeTimeGenerator();

typedef struct LifeTimeGeneratorData {
    float minTime;
    float maxTime;
} LifeTimeGeneratorData;

ParticleGenerator getSpeedGenerator(float, float);

typedef struct SpeedGeneratorData {
    float minSpeed;
    float maxSpeed;
} SpeedGeneratorData;

ParticleGenerator getSizeGenerator(float, float);

typedef struct SizeGeneratorData {
    float minSize;
    float maxSize;
} SizeGeneratorData;

ParticleGenerator getColorGenerator(Color);

typedef struct ColorGeneratorData {
    Color color;
} ColorGeneratorData;

#endif
