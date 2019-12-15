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

    ParticleEmitter* emitter = ConstructParticleEmitter();
    emitter->emitRate = 10.0f;
    emitter->duration = 3.0f;
    emitter->delay = 2.0f;

    emitter->burst = true;
    emitter->burstMin = 100;

    ParticleGenerator sphericalGenerator = getSphericalGenerator();
    SphericalGeneratorData* sphericalGeneratorData = (SphericalGeneratorData*) sphericalGenerator.generatorData;
    sphericalGeneratorData->center = (Vector3){1.0f, 1.0f, 1.0f};
    sphericalGeneratorData->radius = 1.0f;
    addParticleGenerator(emitter, &sphericalGenerator);

    ParticleGenerator lifeTimeGenerator = getLifeTimeGenerator();
    LifeTimeGeneratorData* lifeTimeGeneratorData = (LifeTimeGeneratorData*) lifeTimeGenerator.generatorData;
    lifeTimeGeneratorData->minTime = 0.2f;
    lifeTimeGeneratorData->maxTime = 0.6f;
    addParticleGenerator(emitter, &lifeTimeGenerator);

    addParticleEmitter(system, emitter);

    ParticleUpdater newtonUpdater = getNewtonUpdater();
    addParticleUpdater(system, &newtonUpdater);

    ParticleUpdater timeUpdater = getTimeUpdater();
    addParticleUpdater(system, &timeUpdater);

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

            ClearBackground(RAYWHITE);

            BeginMode3D(*camera);
                DrawGrid(50, 1.0f);
                DrawPlayer(player);


                BeginBlendMode(blending);
                    ParticleData* particleData = system->particleData;
                    for (int i = 0; i < particleData->countAlive; i++) {
                        DrawParticle(*camera, particleTexture, particleData->particles[i].pos, particleData->particles[i].size, RED);
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