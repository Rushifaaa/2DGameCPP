//
// Created by Jakub Gencer on 03.09.21.
//

#ifndef INC_2DGAMECPP_PLAYER_H
#define INC_2DGAMECPP_PLAYER_H

#include "raylib.h"
#include "../Environment/EnvironmentItem.h"
#include "Projectile.h"

#define G 400
#define PLAYER_JUMP_SPEED 290.0f
#define MAX_PLAYER_SPEED 200
#define MAX_SHOTS 100

typedef struct Player
{
    Vector2 position;
    float speed;
    Color color;
    bool canJump;
    int lastPlayerView;


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

    void Draw() const {
        Rectangle playerRect = { position.x - 20, position.y - 40, 40, 40 };
        DrawRectangleRec(playerRect, color);
    }

} Player;

#endif //INC_2DGAMECPP_PLAYER_H
