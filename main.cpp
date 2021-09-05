#include <stdlib.h>
#include <raylib.h>
#include "raymath.h"
#include "Player/Player.h"
#include "Player/Projectile.h"
#include "Environment/EnvironmentItem.h"


#define MAX_BUILDINGS 100

static const int screenWidth = 800;
static const int screenHeight = 450;
static const int targetFPS = 60;

static Player player = { 0 };
static Camera2D camera = { 0 };
static Projectile projectiles[MAX_SHOTS] = { 0 };
static int shootRate = 0;

// TODO: Generate random environment
static EnvironmentItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
};
static int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

void cameraSetup() {
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Initilize() {
    shootRate = 0;

    InitWindow(screenWidth, screenHeight, "2DGameCPP");
    SetTargetFPS(targetFPS);

    cameraSetup();

    Vector2 playerPosition = (Vector2){ 400, 280 };
    player = { playerPosition, 0, ORANGE, false, KEY_D };

    for (auto & projectile : projectiles) {
        projectile.position = player.position;
        projectile.direction = KEY_D;
        projectile.color = MAROON;
        projectile.radius = 16;
        projectile.isActive = false;
        projectile.velocity.x = 600;
        projectile.velocity.y = 0;
    }
}

void HandleShooting(float deltaTime) {

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        shootRate += 5;

        for (auto & projectile : projectiles) {
            if (!projectile.isActive && shootRate % 50 == 0) {
                projectile.position.x = player.position.x;
                projectile.position.y = player.position.y - 20;
                projectile.direction = player.lastPlayerView;

                projectile.isActive = true;
                break;
            }
        }
    }

    for (auto & projectile : projectiles) {
        if (projectile.isActive) {
            if (projectile.direction == KEY_A) {
                projectile.position.x -= projectile.velocity.x * deltaTime;
            } else if (projectile.direction == KEY_D) {
                projectile.position.x += projectile.velocity.x * deltaTime;
            }
        }
    }
}

void CameraUpdater(Camera2D *camera2D, Player *p) {
    camera2D->target = p->position;
    camera2D->offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvironmentItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, *camera2D);
    Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, *camera2D);

    if (max.x < screenWidth) camera2D->offset.x = screenWidth - (max.x - (float)screenWidth / 2);
    if (max.y < screenHeight) camera2D->offset.y = screenHeight - (max.y - (float)screenHeight / 2);
    if (min.x > 0) camera2D->offset.x = (float)screenWidth / 2 - min.x;
    if (min.y > 0) camera2D->offset.y = (float)screenHeight / 2 - min.y;
}

void Update() {
    float deltaTime = GetFrameTime();

    player.HandleMovement(deltaTime, envItems, envItemsLength);
    HandleShooting(deltaTime);

    CameraUpdater(&camera, &player);
}

void Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);

    for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

    player.Draw();

    for (auto & projectile : projectiles) {
        if (projectile.isActive) DrawCircleV(projectile.position, projectile.radius, projectile.color);
    }

    EndMode2D();
    EndDrawing();
}

void Deinitialize() {
    CloseWindow();
}

int main() {
    Initilize();
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    Deinitialize();
    return 0;
}
