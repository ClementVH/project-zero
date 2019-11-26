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

    Model model = LoadModel("toto.iqm");
    Texture2D texture = LoadTexture("textures/Erika_Archer_Clothes_diffuse.png");
    SetMaterialTexture(&model.materials[0], MAP_DIFFUSE, texture);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC keyZZ
    {
        UpdatePlayer(player);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(*camera);

                DrawModelEx(model, *(player->position), (Vector3){1.0f, 0.0f, 0.0f}, -90.0f, (Vector3){0.1f, 0.1f, 0.1f}, WHITE);
                // DrawPlayer(player);
                DrawGrid(50, 1.0f);

            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

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