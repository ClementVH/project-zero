#ifndef FILE_RENDERER_SEEN
#define FILE_RENDERER_SEEN

#include <raylib.h>
#include <rlgl.h>
#include "particle/particle.h"

typedef struct ParticleRenderer {
    void (*render)(Camera, ParticleData*, struct ParticleRenderer*);
    Texture2D texture;
    int systemID;
} ParticleRenderer;

ParticleRenderer* getBillboardRenderer(Texture2D);
ParticleRenderer* getStretchedBillboardRenderer(Texture2D);

#endif
