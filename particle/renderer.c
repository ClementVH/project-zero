#include "raylib.h"
#include "rlgl.h"
#include "particle/renderer.h"

// Draw a billboard (part of a texture defined by a rectangle)
void DrawParticleRec(Camera camera, Texture2D texture, Rectangle sourceRec, Vector3 center, float size, Color tint)
{
    // NOTE: Billboard size will maintain sourceRec aspect ratio, size will represent billboard width
    Vector2 sizeRatio = { size, size*(float)sourceRec.height/sourceRec.width };

    Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);

    Vector3 right = { matView.m0, matView.m4, matView.m8 };
    Vector3 up = { matView.m1, matView.m5, matView.m9 };

    // NOTE: Billboard locked on axis-Y
    // Vector3 up = { 0.0f, 1.0f, 0.0f };
/*
    a-------b
    |       |
    |   *   |
    |       |
    d-------c
*/
    right = Vector3Scale(right, sizeRatio.x/2);
    up = Vector3Scale(up, sizeRatio.y/2);

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

// Draw a billboard
void DrawParticle(Camera camera, Texture2D texture, Vector3 center, float size, Color tint)
{
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

    DrawParticleRec(camera, texture, sourceRec, center, size, tint);
}