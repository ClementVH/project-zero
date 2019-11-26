/**
 * Player
 */
#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"

typedef struct Player {
    Vector3* position;
    Camera* camera;
} Player;

Player* ConstructPlayer() {
    Player* player = (Player*) malloc(sizeof(Player));

    player->position = (Vector3*) malloc(sizeof(Vector3));
    player->position->x = 0.0f;
    player->position->y = 0.0f;
    player->position->z = 0.0f;

    Camera* camera = (Camera*) malloc(sizeof(Camera));
    camera->position = (Vector3){ 10.0f, 15.0f, 8.0f };
    camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };

    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };

    camera->fovy = 40.0f;
    camera->type = CAMERA_ORTHOGRAPHIC;

    player->camera = camera;

    return player;
}

void UpdatePlayer(Player* player) {
    Camera* camera = player->camera;
    Vector3* playerPosition = player->position;

    UpdateCamera(camera);

    Vector3 forward = Vector3Subtract(camera->target, camera->position);
    forward.y = 0;
    Vector3 forwardNormalized = Vector3Normalize(forward);
    Vector3 sidewayNormalized = {-forwardNormalized.z, 0, forwardNormalized.x};

    if (IsKeyDown(KEY_A)) {
        *playerPosition = Vector3Add(*playerPosition, Vector3Multiply(sidewayNormalized, -0.2f));
        camera->position = Vector3Add(camera->position, Vector3Multiply(sidewayNormalized, -0.2f));
    }

    if (IsKeyDown(KEY_D)) {
        *playerPosition = Vector3Add(*playerPosition, Vector3Multiply(sidewayNormalized, 0.2f));
        camera->position = Vector3Add(camera->position, Vector3Multiply(sidewayNormalized, 0.2f));
    }

    if (IsKeyDown(KEY_S)) {
        *playerPosition = Vector3Add(*playerPosition, Vector3Multiply(forwardNormalized, -0.2f));
        camera->position = Vector3Add(camera->position, Vector3Multiply(forwardNormalized, -0.2f));
    }

    if (IsKeyDown(KEY_W)) {
        *playerPosition = Vector3Add(*playerPosition, Vector3Multiply(forwardNormalized, 0.2f));
        camera->position = Vector3Add(camera->position, Vector3Multiply(forwardNormalized, 0.2f));
    }

    camera->target.x = playerPosition->x;
    camera->target.y = playerPosition->y;
    camera->target.z = playerPosition->z;
}

void DrawPlayer(Player* player) {
    Vector3* playerPosition = player->position;

    DrawCube(*playerPosition, 2.0f, 2.0f, 2.0f, MAROON);
    DrawCubeWires(*playerPosition, 2.0f, 2.0f, 2.0f, MAROON);
}