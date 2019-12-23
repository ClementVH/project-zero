#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#include "rlgl.h"
#include "player/player.h"
#include "particle/system.h"
#include "particle/renderer.h"
#include "particle/emitter.h"
#include "particle/updater.h"
#include "particle/generator.h"
#include "effects/hit.h"
#include "utils/cubic-spline.h"
#include "glad.h"

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "raylib");

    Player* player = ConstructPlayer();
    Camera* camera = player->camera;
    Model model = player->model;

    int blending = BLEND_ADDITIVE;

    ParticleSystem* system = ConstructHitEffect(Vector3One());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC keyZZ
    {
        if (IsMouseButtonPressed(0)) {
            system = ConstructHitEffect(Vector3One());
        }

        UpdatePlayer(player);
        updateParticleSystem(system);
        sortParticles(system, *camera);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(*camera);
                rlEnableDepthTest();

                DrawGrid(50, 1.0f);
                // DrawPlayer(player);

                glDepthMask(GL_FALSE);
                BeginBlendMode(blending);
                    renderParticleSystem(*camera, system);
                EndBlendMode();
                glDepthMask(GL_TRUE);

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadModel(model);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
