//
// Created by Iris Chow on 2026-02-04.
//

#ifndef INC_8051PROJECT_COLLISION_H
#define INC_8051PROJECT_COLLISION_H
#include <SDL3/SDL_rect.h>
#include "../ecs/Component.h"

class Collision {

public:
    // Axis-aligned bounding box
    static bool AABB(const SDL_FRect &rectA, const SDL_FRect &rectB);
    static bool AABB(const Collider& colA, const Collider& colB);

};

#endif //INC_8051PROJECT_COLLISION_H