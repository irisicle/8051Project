//
// Created by Iris Chow on 2026-02-04.
//

#include "Collision.h"
#include <SDL3/SDL_rect.h>

SDL_FRect Collision::getWorldBounds(const Transform &transform, const Collider &collider) {
    return SDL_FRect{
        transform.position.x + collider.offset.x * transform.scale,
        transform.position.y + collider.offset.y * transform.scale,
        collider.width,
        collider.height
    };
}

// Axis-aligned bounding box
// Passing in rects
bool Collision::AABB(const SDL_FRect &rectA, const SDL_FRect &rectB) {

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
bool Collision::AABB(const Transform& transformA, const Collider& colliderA, const Transform& transformB, const Collider& colliderB) {
    if (!colliderA.enabled || !colliderB.enabled) {
        return false;
    }

    const SDL_FRect rectA = getWorldBounds(transformA, colliderA);
    const SDL_FRect rectB = getWorldBounds(transformB, colliderB);

    return AABB(rectA, rectB);
}
