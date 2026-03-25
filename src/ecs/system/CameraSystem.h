//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_CAMERASYSTEM_H
#define INC_8051PROJECT_CAMERASYSTEM_H
#include <vector>

#include "../Component.h"
#include "../Entity.h"

class CameraSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* playerEntity = nullptr;

        // Find the player
        for (auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>()) {
                playerEntity = entity.get();
                break;
            }
        }
        if (!playerEntity) return; // No player

        const auto& playerTransform = playerEntity->getComponent<Transform>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                auto& cam = entity->getComponent<Camera>();

                // This positions the camera so the player is at the center of its view
                cam.view.x = playerTransform.position.x - cam.view.w / 2;
                cam.view.y = playerTransform.position.y - cam.view.h / 2;

                // Camera is positioning itself so the player is centered, but the player could walk off the screen
                // Clamp the camera so it stays within the window
                if (cam.view.x < 0) cam.view.x = 0;
                if (cam.view.y < 0) cam.view.y = 0;
                if (cam.view.x > cam.worldWidth - cam.view.w) cam.view.x = cam.worldWidth - cam.view.w;
                if (cam.view.y > cam.worldHeight - cam.view.h) cam.view.y = cam.worldHeight - cam.view.h;
            }
        }

    }
};

#endif //INC_8051PROJECT_CAMERASYSTEM_H