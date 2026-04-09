//
// Created by Iris Chow on 2026-04-06.
//

#include "CollisionResponseSystem.h"
#include "../ecs/component/Physics.h"
#include "../ecs/core/Entity.h"

#include <string>

void CollisionResponseSystem::handle(const CollisionEvent& event, const char* otherTag) {
    Entity* player = nullptr;
    Entity* other = nullptr;

    if (!getCollisionEntities(event, otherTag, player, other)) return;

    if (std::string(otherTag) == "item") {
        if (event.state != CollisionState::ENTER) return;

        other->destroy();
    }

    else if (std::string(otherTag) == "wall") {
        if (event.state != CollisionState::STAY) return;

        // Stop the player
        auto& transform = player->getComponent<Transform>();
        transform.position = transform.oldPosition;
    }
}

bool CollisionResponseSystem::getCollisionEntities(const CollisionEvent& event, const char* otherTag, Entity*& player, Entity*& other) {
    if (event.entityA == nullptr || event.entityB == nullptr) return false;

    if (!(event.entityA->hasComponent<Collider>() && event.entityB->hasComponent<Collider>())) return false;

    const auto& colliderA = event.entityA->getComponent<Collider>();

    if (const auto& colliderB = event.entityB->getComponent<Collider>(); colliderA.tag == "player" && colliderB.tag == otherTag) {
        player = event.entityA;
        other = event.entityB;
    }

    else if (colliderA.tag == otherTag && colliderB.tag == "player") {
        player = event.entityB;
        other = event.entityA;
    }

    return player && other;
}