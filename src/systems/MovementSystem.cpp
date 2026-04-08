//
// Created by Iris Chow on 2026-04-05.
//

#include "MovementSystem.h"

#include "../ecs/component/Interaction.h"
#include "../ecs/core/Entity.h"
#include "../ecs/component/Physics.h"

void MovementSystem::update(const std::vector<std::unique_ptr<Entity>> &entities, const float deltaTime) {
    for (const auto &entity: entities) {
        if (!entity->hasComponent<Transform>() || !entity->hasComponent<Velocity>()) {
            continue;
        }

        auto &transform = entity->getComponent<Transform>();
        const auto &velocity = entity->getComponent<Velocity>();

        // Track previous frame's position
        transform.oldPosition = transform.position;

        Vector2D direction = velocity.direction;

        if (const bool isMoving = direction.x != 0.0f || direction.y != 0.0f; isMoving && entity->hasComponent<Facing>()) {
            auto& facing = entity->getComponent<Facing>();

            if (direction.x > 0.0f) {
                facing.direction = Direction::RIGHT;
            }
            else if (direction.x < 0.0f) {
                facing.direction = Direction::LEFT;
            }
            else if (direction.y > 0.0f) {
                facing.direction = Direction::DOWN;
            }
            else if (direction.y < 0.0f) {
                facing.direction = Direction::UP;
            }
        }

        // Normalize the vector (direction = 1), so it does not shoot off the screen
        direction.normalize();

        // Vector2D needs an operator function to multiply a float to itself
        const Vector2D velocityVector = direction * velocity.speed;
        transform.position += velocityVector * deltaTime;
    }
}
