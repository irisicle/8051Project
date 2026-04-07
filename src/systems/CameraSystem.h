//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_CAMERASYSTEM_H
#define INC_8051PROJECT_CAMERASYSTEM_H

#include <vector>
#include "../ecs/component/Tag.h"
#include "../ecs/core/Entity.h"
#include "../utils/Constants.h"

class CameraSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* player = nullptr;

        // Find the player
        for (auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>()) {
                player = entity.get();
                break;
            }
        }

        if (!player) return; // No player

        const auto& transform = player->getComponent<Transform>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                auto&[view, worldWidth, worldHeight] = entity->getComponent<Camera>();

                // This positions the camera so the player is at the center of its view
                view.x = transform.position.x - view.w / Constants::SCALE;
                view.y = transform.position.y - view.h / Constants::SCALE;

                // Camera is positioning itself so the player is centered, but the player could walk off the screen
                // Clamp the camera so it stays within the window
                if (view.x < 0) view.x = 0;
                if (view.y < 0) view.y = 0;
                if (view.x > worldWidth - view.w) view.x = worldWidth - view.w;
                if (view.y > worldHeight - view.h) view.y = worldHeight - view.h;
            }
        }
    }
};

#endif //INC_8051PROJECT_CAMERASYSTEM_H