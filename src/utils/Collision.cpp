//
// Created by Iris Chow on 2026-02-04.
//

#include "Collision.h"
#include <SDL3/SDL_rect.h>

// Axis-aligned bounding box
// Passing in rects
bool Collision::AABB(const SDL_FRect& rectA, const SDL_FRect& rectB) {
    // 1. Is the right edge of rectA >= the left edge of rectB
    // 2. Is the right edge of rectB >= the left edge of rectA
    // 3. Is the bottom edge of rectA >= the top edge of rectB
    // 4. Is the bottom edge of rectB >= the top edge of rectA
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y
        ) { return true; }
    return false;
}

// Passing in the colliders themselves
bool Collision::AABB(const Collider& colA, const Collider& colB) {
    if (AABB(colA.rect, colB.rect)) {
        return true;
    }
    return false;
}
