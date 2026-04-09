//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_CAMERASYSTEM_H
#define INC_8051PROJECT_CAMERASYSTEM_H

#include <vector>
#include "../ecs/component/Tag.h"
#include "../ecs/core/Entity.h"
#include "../ecs/core/Camera.h"
#include "../ecs/component/Physics.h"

class CameraSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, Camera& camera) {
        Entity* player = nullptr;

        // Find the player
        for (const auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>() && entity->hasComponent<Transform>()) {
                player = entity.get();
                break;
            }
        }

        // No player found
        if (!player) {
            return;
        }

        const auto& transform = player->getComponent<Transform>();

        // Center camera on the player
        camera.view.x = transform.position.x - camera.view.w / 2;
        camera.view.y = transform.position.y - camera.view.h / 2;

        // Clamp camera to world bounds
        if (camera.view.x < 0.0f) camera.view.x = 0.0f;
        if (camera.view.y < 0.0f) camera.view.y = 0.0f;

        if (camera.view.x > camera.worldWidth - camera.view.w) {
            camera.view.x = camera.worldWidth - camera.view.w;
        }

        if (camera.view.y > camera.worldHeight - camera.view.h) {
            camera.view.y = camera.worldHeight - camera.view.h;
        }

        // In case world is smaller than the view
        if (camera.view.x < 0.0f) camera.view.x = 0.0f;
        if (camera.view.y < 0.0f) camera.view.y = 0.0f;
    }
};

#endif //INC_8051PROJECT_CAMERASYSTEM_H