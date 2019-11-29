#include "raylib.h"
#include "./player/player.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    Player* player = ConstructPlayer();
    Camera* camera = player->camera;
    Model* model = player->model;

    // float pitch = 90.0f;
    // float roll = 0.0f;
    // float yaw = -45.0f;

    // Model model = LoadModel("archer.iqm");

    // Texture2D texture = LoadTexture("textures/Erika_Archer_Clothes_diffuse.png");    // Load model texture and set material
    // SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);

    // model.transform = MatrixRotateXYZ((Vector3){DEG2RAD*pitch,DEG2RAD*yaw,DEG2RAD*roll});

    // int animsCount = 0;
    // ModelAnimation *anims = LoadModelAnimations("archer.iqm", &animsCount);
    // int animFrameCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC keyZZ
    {
        UpdatePlayer(player);

        // animFrameCounter++;
        // UpdateModelAnimation(model, anims[0], animFrameCounter);
        // if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(*camera);

                // DrawModel(model, *(player->position), 0.04f, WHITE);
                DrawPlayer(player);
                DrawGrid(50, 1.0f);

            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadModel(*model);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}