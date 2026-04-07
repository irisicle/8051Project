//
// Created by Iris Chow on 2026-02-04.
//

#ifndef INC_8051PROJECT_COLLISION_H
#define INC_8051PROJECT_COLLISION_H

#include <SDL3/SDL_rect.h>
#include "../ecs/component/Physics.h"

class Collision {
public:
    // Axis-aligned bounding box
    static bool AABB(const SDL_FRect &rectA, const SDL_FRect &rectB);
    static bool AABB(const Transform& transformA, const Collider& colliderA, const Transform& transformB, const Collider& colliderB);

private:
    static SDL_FRect getWorldBounds(const Transform& transform, const Collider& collider);
};

#endif //INC_8051PROJECT_COLLISION_H