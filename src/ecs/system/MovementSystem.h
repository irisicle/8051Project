//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_MOVEMENTSYSTEM_H
#define INC_8051PROJECT_MOVEMENTSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class MovementSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, const float deltaTime) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Velocity>()) {
                auto& t = entity->getComponent<Transform>();
                auto&[direction, speed] = entity->getComponent<Velocity>();

                // Track previous frame's position
                t.oldPosition = t.position;

                Vector2D directionVector = direction;

                // Normalize the vector (direction = 1), so it does not shoot off the screen
                directionVector.normalize();

                // Vector2D needs an operator function to multiply a float to itself
                Vector2D velocityVector = directionVector * speed;
                //Vector2D velocityVector = speed * directionVector;

                t.position += (velocityVector * deltaTime);
            }
        }
    }
};

#endif //INC_8051PROJECT_MOVEMENTSYSTEM_H