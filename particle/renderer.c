#include <stdlib.h>
#include <raylib.h>
#include <rlgl.h>
#include "particle/particle.h"
#include "particle/renderer.h"
#include "particle/macros.h"

void draw(Rectangle sourceRec, Texture2D texture, Color tint, Vector3 center, Vector3 right, Vector3 up) {

/*
    a-------b
    |       |
    |   *   |
    |       |
    d-------c
*/

    Vector3 p1 = Vector3Add(right, up);
    Vector3 p2 = Vector3Subtract(right, up);

    Vector3 a = Vector3Subtract(center, p2);
    Vector3 b = Vector3Add(center, p1);
    Vector3 c = Vector3Add(center, p2);
    Vector3 d = Vector3Subtract(center, p1);

    if (rlCheckBufferLimit(4)) rlglDraw();

    rlEnableTexture(texture.id);

    rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);

        // Bottom-left corner for texture and quad
        rlTexCoord2f((float)sourceRec.x/texture.width, (float)sourceRec.y/texture.height);
        rlVertex3f(a.x, a.y, a.z);

        // Top-left corner for texture and quad
        rlTexCoord2f((float)sourceRec.x/texture.width, (float)(sourceRec.y + sourceRec.height)/texture.height);
        rlVertex3f(d.x, d.y, d.z);

        // Top-right corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width)/texture.width, (float)(sourceRec.y + sourceRec.height)/texture.height);
        rlVertex3f(c.x, c.y, c.z);

        // Bottom-right corner for texture and quad
        rlTexCoord2f((float)(sourceRec.x + sourceRec.width)/texture.width, (float)sourceRec.y/texture.height);
        rlVertex3f(b.x, b.y, b.z);
    rlEnd();

    rlDisableTexture();

}

// Draw a billboard (part of a texture defined by a rectangle)
void DrawParticleRec(Camera camera, Texture2D texture, Rectangle sourceRec, Particle* particle)
{
    // NOTE: Billboard size will maintain sourceRec aspect ratio, size will represent billboard width
    Vector2 sizeRatio = { particle->size, particle->size*(float)sourceRec.height/sourceRec.width };

    Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);

    Vector3 right = { matView.m0, matView.m4, matView.m8 };
    Vector3 up = { matView.m1, matView.m5, matView.m9 };

    right = Vector3Scale(right, sizeRatio.x/2);
    up = Vector3Scale(up, sizeRatio.y/2);

    draw(sourceRec, texture, particle->color, particle->pos, right, up);
}

// Draw a billboard
void DrawParticle(Camera camera, ParticleData* particleData, ParticleRenderer* renderer)
{
    Texture2D texture = renderer->texture;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

    int systemID = renderer->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        Particle particle = particleData->particles[i];
        DrawParticleRec(camera, texture, sourceRec, &particle);
    }
}

// Draw a billboard (part of a texture defined by a rectangle)
void DrawParticleStretchedRec(Camera camera, Texture2D texture, Rectangle sourceRec, Particle* particle)
{
    // NOTE: Billboard size will maintain sourceRec aspect ratio, size will represent billboard width
    Vector2 sizeRatio = { particle->size, particle->size*(float)sourceRec.height/sourceRec.width };

    Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);

    Vector3 v1 = { matView.m2, matView.m6, matView.m10 };
    Vector3 right = Vector3Normalize(particle->vel);
    Vector3 up = Vector3CrossProduct(v1, right);
    v1 = Vector3CrossProduct(right, up);

    right = Vector3Scale(right, sizeRatio.x/2 * 3.0f);
    up = Vector3Scale(up, sizeRatio.y/4);

    draw(sourceRec, texture, particle->color, particle->pos, right, up);
}

// Draw a billboard
void DrawParticleStretched(Camera camera, ParticleData* particleData, ParticleRenderer* renderer)
{
    Texture2D texture = renderer->texture;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

    int systemID = renderer->systemID;
    forParticlesInSystem(particleData->countAlive, particleData, systemID)
        Particle particle = particleData->particles[i];
        DrawParticleStretchedRec(camera, texture, sourceRec, &particle);
    }
}

ParticleRenderer* getBillboardRenderer(Texture2D texture) {
    ParticleRenderer* renderer = malloc(sizeof(ParticleRenderer));
    renderer->render = &DrawParticle;
    renderer->texture = texture;
    return renderer;
}

ParticleRenderer* getStretchedBillboardRenderer(Texture2D texture) {
    ParticleRenderer* renderer = malloc(sizeof(ParticleRenderer));
    renderer->render = &DrawParticleStretched;
    renderer->texture = texture;
    return renderer;
}