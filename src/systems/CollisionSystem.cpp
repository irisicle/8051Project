//
// Created by Iris Chow on 2026-02-04.
//

#include "CollisionSystem.h"
#include "../utils/Collision.h"
#include <vector>
#include "../ecs/core/World.h"

void CollisionSystem::update(World& world) {

    // Get a list of entities that have colliders & transforms
    const std::vector<Entity*> collidables = queryCollidables(world.getEntities());

    std::set<CollisionKey> currentCollisions;

    // Outer loop
    for (size_t i = 0; i < collidables.size(); ++i) {

        // Update the collider position
        auto& entityA = collidables[i];
        auto& transformA = entityA->getComponent<Transform>();
        auto& colliderA = entityA->getComponent<Collider>();

        // Check for the collider collision
        // Inner loop
        for (size_t j = i + 1; j < collidables.size(); ++j) {
            auto& entityB = collidables[j];
            auto& transformB = entityB->getComponent<Transform>();
            auto& colliderB = entityB->getComponent<Collider>();

            if (Collision::AABB(transformA, colliderA, transformB, colliderB)) {
                CollisionKey key = makeKey(entityA, entityB);
                currentCollisions.insert(key);

                if (!activeCollisions.contains(key)) {
                    world.getEventManager().emit(CollisionEvent(entityA, entityB, CollisionState::ENTER));
                }

                world.getEventManager().emit(CollisionEvent(entityA, entityB, CollisionState::STAY));
            }
        }
    }

    for (auto& key : activeCollisions) {
        if (!currentCollisions.contains(key)) {
            world.getEventManager().emit(CollisionEvent{key.first, key.second, CollisionState::EXIT});
        }
    }

    activeCollisions = std::move(currentCollisions); // Update with current collisions
}

std::vector<Entity*> CollisionSystem::queryCollidables(const std::vector<std::unique_ptr<Entity>>& entities) {
    std::vector<Entity*> collidables;

    for (auto& entity : entities) {
        if (entity->hasComponent<Transform>() && entity->hasComponent<Collider>()) {
            collidables.push_back(entity.get());
        }
    }
    return {collidables};
}
