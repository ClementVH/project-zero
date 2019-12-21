#ifndef FILE_PARTICLE_SEEN
#define FILE_PARTICLE_SEEN
#include "raylib.h"

#define MAX_PARTICLE_COUNT 10000

typedef struct Particle {
    int systemID;
    Vector3 pos;
    Vector3 vel;
    Vector3 acc;
    bool alive;
    float size;
    float rotation;
    float cameraDistance;
    float maxLifeTime;
    float lifeTime;
    Color color;
} Particle;

typedef struct ParticleData {
    Particle particles[MAX_PARTICLE_COUNT];
    int countAlive;
} ParticleData;

void killParticle(ParticleData*, int);

#endif