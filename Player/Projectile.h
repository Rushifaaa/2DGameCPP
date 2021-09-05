//
// Created by Jakub Gencer on 04.09.21.
//

#ifndef INC_2DGAMECPP_PROJECTILE_H
#define INC_2DGAMECPP_PROJECTILE_H

typedef struct Projectile {
    Vector2 position;
    Vector2 velocity;
    int direction;
    bool isActive;
    float radius;
    Color color;
} Projectile;

#endif //INC_2DGAMECPP_PROJECTILE_H
