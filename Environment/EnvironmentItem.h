//
// Created by Jakub Gencer on 04.09.21.
//

#ifndef INC_2DGAMECPP_ENVIRONMENTITEM_H
#define INC_2DGAMECPP_ENVIRONMENTITEM_H

#include "raylib.h"

typedef struct EnvironmentItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvironmentItem;

#endif //INC_2DGAMECPP_ENVIRONMENTITEM_H
