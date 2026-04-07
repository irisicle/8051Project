//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_PLAYERCONTROLSYSTEM_H
#define INC_8051PROJECT_PLAYERCONTROLSYSTEM_H

#include <memory>
#include <vector>

#include "../ecs/component/Interaction.h"
#include "../ecs/core/Entity.h"
#include "../ecs/component/Tag.h"
#include "../ecs/component/Physics.h"

class PlayerControlSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (!entity->hasComponent<PlayerTag>() || !entity->hasComponent<PlayerIntent>() || !entity->hasComponent<Velocity>()) {
                continue;
            }

            const auto& intent = entity->getComponent<PlayerIntent>();
            auto& velocity = entity->getComponent<Velocity>();

            velocity.direction.x = intent.moveX;
            velocity.direction.y = intent.moveY;
        }
    }
};

#endif //INC_8051PROJECT_PLAYERCONTROLSYSTEM_H