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
    emitter->emitRate = 5.0f;
    emitter->duration = 0.0f;
    emitter->delay = 0.0f;

    emitter->burst = false;
    emitter->burstMin = 100;

    // Generators
    ParticleGenerator sphericalGenerator = getSphericalGenerator();
    SphericalGeneratorData* sphericalGeneratorData = (SphericalGeneratorData*) sphericalGenerator.generatorData;
    sphericalGeneratorData->center = (Vector3){1.0f, 1.0f, 1.0f};
    sphericalGeneratorData->radius = 5.0f;
    sphericalGeneratorData->fromShell = false;
    addParticleGenerator(emitter, &sphericalGenerator);

    ParticleGenerator lifeTimeGenerator = getLifeTimeGenerator();
    LifeTimeGeneratorData* lifeTimeGeneratorData = (LifeTimeGeneratorData*) lifeTimeGenerator.generatorData;
    lifeTimeGeneratorData->minTime = 1.0f;
    lifeTimeGeneratorData->maxTime = 1.5f;
    addParticleGenerator(emitter, &lifeTimeGenerator);

    ParticleGenerator speedGenerator = getSpeedGenerator(0.09f, 0.16f);
    addParticleGenerator(emitter, &speedGenerator);

    ParticleGenerator sizeGenerator = getSizeGenerator(1.0f, 1.5f);
    addParticleGenerator(emitter, &sizeGenerator);

    ParticleGenerator colorGenerator = getColorGenerator(RED);
    addParticleGenerator(emitter, &colorGenerator);

    addParticleEmitter(system, emitter);

    // Updaters
    ParticleUpdater newtonUpdater = getNewtonUpdater();
    addParticleUpdater(system, &newtonUpdater);

    ParticleUpdater timeUpdater = getTimeUpdater();
    addParticleUpdater(system, &timeUpdater);

    ParticleUpdater alphaUpdater = getAlphaUpdater();
    addParticleUpdater(system, &alphaUpdater);

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
