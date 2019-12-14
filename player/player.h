/**
 * Player
 */
#include "stdlib.h"
#include "raylib.h"
#include "raymath.h"

float pitch = 90.0f;
float roll = 0.0f;
float yaw = 0.0f;

typedef struct Player {
    Vector3* position;
    Camera* camera;
    Model model;
    ModelAnimation* anims[3];
    int animFrameCounter;
    int currentAnimation;
} Player;

void RotateModelForward(Player* player, Vector3 forward);

int ANIM_IDLE = 0;
int ANIM_WALKING = 1;
int ANIM_RUNNING = 2;

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
    SetCameraMode(*camera, CAMERA_FREE);

    player->camera = camera;

    player->model = LoadModel("assets/player/models/archer-model.iqm");

    player->model.transform = MatrixRotateXYZ((Vector3){DEG2RAD*pitch,DEG2RAD*yaw,DEG2RAD*roll});

    Texture2D texture = LoadTexture("assets/player/textures/player-diffuse.png");    // Load model texture and set material
    SetMaterialTexture(&player->model.materials[0], MAP_DIFFUSE, texture);

    int animsCount = 0;
    player->anims[ANIM_IDLE] = LoadModelAnimations("assets/player/animations/idle.iqm", &animsCount);
    player->anims[ANIM_WALKING] = LoadModelAnimations("assets/player/animations/walking.iqm", &animsCount);
    player->anims[ANIM_RUNNING] = LoadModelAnimations("assets/player/animations/running.iqm", &animsCount);
    (*player).animFrameCounter = 0;

    player->currentAnimation = ANIM_IDLE;

    return player;
}

void UpdatePlayer(Player* player) {
    Camera* camera = player->camera;
    Vector3* playerPosition = player->position;
    Model model = player->model;
    ModelAnimation** anims = player->anims;
    Vector3 previousPosition = *playerPosition;

    UpdateCamera(camera);

    Vector3 forward = Vector3Subtract(camera->target, camera->position);
    forward.y = 0;
    Vector3 forwardNormalized = Vector3Normalize(forward);
    Vector3 sidewayNormalized = {-forwardNormalized.z, 0, forwardNormalized.x};

    Vector3 movement = (Vector3){ 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_A)) {
        movement = Vector3Subtract(movement, sidewayNormalized);
    }

    if (IsKeyDown(KEY_D)) {
        movement = Vector3Add(movement, sidewayNormalized);
    }

    if (IsKeyDown(KEY_S)) {
        movement = Vector3Subtract(movement, forwardNormalized);
    }

    if (IsKeyDown(KEY_W)) {
        movement = Vector3Add(movement, forwardNormalized);
    }

    float speed = 0.0f;
    int animation = ANIM_IDLE;

    if (Vector3Length(movement) > 0.0f) {
        animation = ANIM_WALKING;
        speed = 0.11f;

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            animation = ANIM_RUNNING;
            speed = 0.26f;
        }
    }

    if (animation != player->currentAnimation) {
        player->currentAnimation = animation;
        player->animFrameCounter = 0;
    }

    movement = Vector3Multiply(Vector3Normalize(movement), speed);
    *playerPosition = Vector3Add(*playerPosition, movement);
    camera->position = Vector3Add(camera->position, movement);

    camera->target.x = playerPosition->x;
    camera->target.y = playerPosition->y;
    camera->target.z = playerPosition->z;

    Vector3 playerForward = Vector3Normalize(Vector3Subtract(*playerPosition, previousPosition));
    RotateModelForward(player, playerForward);

    player->animFrameCounter++;
    UpdateModelAnimation(model, *anims[player->currentAnimation], player->animFrameCounter);
    if (player->animFrameCounter >= (*anims[player->currentAnimation]).frameCount) player->animFrameCounter = 0;
}

void DrawPlayer(Player* player) {
    Vector3* playerPosition = player->position;
    Model model = player->model;

    DrawModel(model, *playerPosition, 0.04f, WHITE);
}


void RotateModelForward(Player* player, Vector3 forward) {
    Vector2 refOrientation = (Vector2){0.0f, 1.0f};
    Vector2 targetOrientation = (Vector2){forward.x, forward.z};

    if (targetOrientation.x == 0.0f && targetOrientation.y == 0.0f) {
        return;
    }

    float angle = atan2(refOrientation.x, refOrientation.y) - atan2(targetOrientation.x, targetOrientation.y);

    player->model.transform = MatrixRotateXYZ((Vector3){DEG2RAD*pitch,angle,DEG2RAD*roll});
}