#ifndef FILE_RENDERER_SEEN
#define FILE_RENDERER_SEEN

#include "raylib.h"
#include "rlgl.h"

void DrawParticleRec(Camera camera, Texture2D texture, Rectangle sourceRec, Vector3 center, float size, Color tint);
void DrawParticle(Camera camera, Texture2D texture, Vector3 center, float size, Color tint);

void DrawParticleStretched(Camera camera, Texture2D texture, Particle* particle);

#endif
