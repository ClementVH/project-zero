#ifndef FILE_PARTICLE_SEEN
#define FILE_PARTICLE_SEEN
#include "raylib.h"

#define MAX_PARTICLE_COUNT 10000

typedef struct ParticleData {
    Vector3 pos[MAX_PARTICLE_COUNT];
    Vector3 vel[MAX_PARTICLE_COUNT];
    Vector3 acc[MAX_PARTICLE_COUNT];
    bool alive[MAX_PARTICLE_COUNT];
    float alpha[MAX_PARTICLE_COUNT];
    float size[MAX_PARTICLE_COUNT];
    float rotation[MAX_PARTICLE_COUNT];
    int countAlive;
} ParticleData;

#endif