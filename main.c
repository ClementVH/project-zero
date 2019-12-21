#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#include "player/player.h"
#include "particle/system.h"
#include "particle/renderer.h"
#include "particle/emitter.h"
#include "particle/updater.h"
#include "particle/generator.h"
#include "effects/hit.h"

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

    Texture2D particleTexture = LoadTexture("assets/particle/point-light.png");
    int blending = BLEND_ALPHA;

    ParticleSystem* system = ConstructHitEffect(Vector3One());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC keyZZ
    {
        UpdatePlayer(player);
        updateParticleSystem(system);
        sortParticles(system, *camera);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(*camera);
                // DrawGrid(50, 1.0f);
                // DrawPlayer(player);

                BeginBlendMode(blending);
                    ParticleData* particleData = system->particleData;
                    for (int i = 0; i < particleData->countAlive; i++) {
                        Particle particle = particleData->particles[i];
                        DrawParticle(*camera, particleTexture, particle.pos, particle.size, particle.color);
                    }
                EndBlendMode();
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
