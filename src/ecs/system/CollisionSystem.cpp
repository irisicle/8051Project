//
// Created by Iris Chow on 2026-02-04.
//
#include "CollisionSystem.h"
#include "../../utils/Collision.h"
#include <vector>
#include "../World.h"

void CollisionSystem::update(World& world) {

    // Get a list of entities that have colliders & transforms
    const std::vector<Entity*> collidables = queryCollidables(world.getEntities());

    std::set<CollisionKey> activeCollisions;
    std::set<CollisionKey> currentCollisions;

    // Update all collider positions first
    for (const auto entity : collidables) {
        const auto& transform = entity->getComponent<Transform>();
        auto& c = entity->getComponent<Collider>();
        c.rect.x = transform.position.x;
        c.rect.y = transform.position.y;
    }

    // Outer loop
    for (size_t i = 0; i < collidables.size(); ++i) {
        // Update the collider position
        auto& entityA = collidables[i];
        auto& colliderA = entityA->getComponent<Collider>();

        // Check for the collider collision
        // Inner loop
        for (size_t j = i + 1; j < collidables.size(); ++j) {
            auto& entityB = collidables[j];

            if (auto& colliderB = entityB->getComponent<Collider>(); Collision::AABB(colliderA, colliderB)) {
                CollisionKey key = makeKey(entityA, entityB);
                currentCollisions.insert(key);

                if (!activeCollisions.contains(key)) {
                    world.getEventManager().emit(CollisionEvent(entityA, entityB, CollisionState::Enter));
                }

                world.getEventManager().emit(CollisionEvent(entityA, entityB, CollisionState::Stay));
            }
        }
    }

    for (auto& key : activeCollisions) {
        if (!currentCollisions.contains(key)) {
            world.getEventManager().emit(CollisionEvent{key.first, key.second, CollisionState::Exit});
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
