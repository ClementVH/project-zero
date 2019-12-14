#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "raylib.h"
#include "./player/player.h"
#include "./particle/system.h"
#include "./particle/renderer.h"
#include "./particle/emitter.h"
#include "./particle/updater.h"
#include "./particle/generator.h"

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

    ParticleSystem* system = ConstructParticleSystem();
    Texture2D particleTexture = LoadTexture("assets/particle/point-light.png");
    int blending = BLEND_ALPHA;

    ParticleEmitter basicEmitter = getBasicEmitter();
    BasicEmitterData* emitterData = (BasicEmitterData*) basicEmitter.emitterData;
    emitterData->emitRate = 5.0f;

    ParticleGenerator sphericalGenerator = getSphericalGenerator();
    SphericalGeneratorData* generatorData = (SphericalGeneratorData*) sphericalGenerator.generatorData;
    generatorData->center = (Vector3){1.0f, 1.0f, 1.0f};
    generatorData->radius = 1.0f;
    addParticleGenerator(&basicEmitter, &sphericalGenerator);

    addParticleEmitter(system, &basicEmitter);
    addParticleUpdater(system, &basicUpdater);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC keyZZ
    {
        UpdatePlayer(player);
        updateParticleSystem(system);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(*camera);
                DrawGrid(50, 1.0f);
                DrawPlayer(player);


                BeginBlendMode(blending);
                    for (int i = 0; i < system->particles->countAlive; i++) {
                        DrawParticle(*camera, particleTexture, system->particles->pos[i], system->particles->size[i], RED);
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