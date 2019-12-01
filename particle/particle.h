#include "raylib.h"

typedef struct Particle {
    Vector3 pos;
    Vector3 vel;
    Vector3 acc;
    bool alive;
    float alpha;
    float size;
    float rotation;
} Particle;

