#ifndef FILE_PARTICLE_SEEN
#define FILE_PARTICLE_SEEN
#include "raylib.h"

#define MAX_PARTICLE_COUNT 10000

typedef struct Particle {
    Vector3 pos;
    Vector3 vel;
    Vector3 acc;
    bool alive;
    float alpha;
    float size;
    float rotation;
    float cameraDistance;
} Particle;

typedef struct ParticleData {
    Particle particles[MAX_PARTICLE_COUNT];
    int countAlive;
} ParticleData;

#endif