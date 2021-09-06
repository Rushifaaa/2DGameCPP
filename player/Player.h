//
// Created by Jakub Gencer on 03.09.21.
//

#ifndef INC_2DGAMECPP_PLAYER_H
#define INC_2DGAMECPP_PLAYER_H

#include <iostream>
#include "raylib.h"
#include "../environment/EnvironmentItem.h"
#include "Projectile.h"

#define G 400
#define PLAYER_JUMP_SPEED 290.0f
#define MAX_PLAYER_SPEED 200
#define MAX_SHOTS 100

typedef struct Player
{
    Vector2 position{};

    // Animation
    int frame = 0;
    float timer = 0;
    float speed = 0;
    bool canJump = false;
    int lastPlayerView = KEY_D;

    void HandleMovement(float deltaTime, EnvironmentItem *envItems, int envItemsLength) {
        float sprintVelocity;

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            sprintVelocity = MAX_PLAYER_SPEED * 2;
        } else {
            sprintVelocity = 0;
        }

        if (IsKeyDown(KEY_D)) {
            position.x += (MAX_PLAYER_SPEED + sprintVelocity) * deltaTime;
            lastPlayerView = KEY_D;
        } else if (IsKeyDown(KEY_A)) {
            position.x -= (MAX_PLAYER_SPEED + sprintVelocity) * deltaTime;
            lastPlayerView = KEY_A;
        }

        if (IsKeyDown(KEY_SPACE) && canJump)
        {
            speed = -PLAYER_JUMP_SPEED;
            canJump = false;
        }

        int hitObstacle = 0;
        for (int i = 0; i < envItemsLength; i++)
        {
            EnvironmentItem *ei = envItems + i;
            Vector2 *p = &(position);
            if (ei->blocking &&
                ei->rect.x <= p->x &&
                ei->rect.x + ei->rect.width >= p->x &&
                ei->rect.y >= p->y &&
                ei->rect.y < p->y + speed*deltaTime)
            {
                hitObstacle = 1;
                speed = 0.0f;
                p->y = ei->rect.y;
            }
        }
        if (!hitObstacle)
        {
            position.y += speed*deltaTime;
            speed += G*deltaTime;
            canJump = false;
        }
        else canJump = true;

    }

    Texture2D idleTexture{};
    Texture2D runTexture{};
    Texture2D jumpTexture{};

    void LoadTextures() {
        idleTexture = LoadTexture("../resources/assets/character/Idle.png");
        runTexture = LoadTexture("../resources/assets/character/Run.png");
        jumpTexture = LoadTexture("../resources/assets/character/Jump.png");
    }

    void UnloadTextures() const {
        UnloadTexture(idleTexture);
        UnloadTexture(runTexture);
        UnloadTexture(jumpTexture);
    }

    void Draw() {
        Texture2D playerTexture = idleTexture;
        auto frameWidth = (float) (playerTexture.width / 8.0);

        if (IsKeyDown(KEY_SPACE)) {
            playerTexture = jumpTexture;
            frameWidth = (float)(playerTexture.width / 2.0);
        } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A)) {
            playerTexture = runTexture;
        } else {
            playerTexture = idleTexture;
        }

        int maxFrames = (int)(playerTexture.width / (int)frameWidth);

        timer += GetFrameTime();

        if (timer >= 0.2f) {
            timer = 0;
            frame += 1;
        }

        frame = frame % maxFrames;
        Rectangle playerRect;

        if (lastPlayerView == KEY_D) {
            playerRect = { (frameWidth * (float)frame), 0, frameWidth, (float)playerTexture.height };
        } else {
            playerRect = { (frameWidth * (float)frame), 0, -frameWidth, (float)playerTexture.height };
        }

        Vector2 framePosition = { position.x - frameWidth, position.y - (float)playerTexture.height };
        DrawTextureRec(playerTexture, playerRect, framePosition, WHITE);
    }

} Player;

#endif //INC_2DGAMECPP_PLAYER_H
