//
// Created by Iris Chow on 2026-02-25.
//

#ifndef INC_8051TUTORIAL_DESTRUCTIONSYSTEM_H
#define INC_8051TUTORIAL_DESTRUCTIONSYSTEM_H

#include "../Component.h"
#include "../Entity.h"

class DestructionSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;

        // Find camera
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }
        if (!cameraEntity) return;

        const auto& cam = cameraEntity->getComponent<Camera>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<ProjectileTag>()) {

                // Destroy entity if it goes out the cam view
                if (const auto& t = entity->getComponent<Transform>();
                    t.position.x > cam.view.x + cam.view.w || // Right edge of view
                    t.position.x < cam.view.x || // Left edge of view
                    t.position.y > cam.view.y + cam.view.h || // Bottom edge of view
                    t.position.y < cam.view.y) { // Top edge of view

                    entity->destroy();
                }
            }
        }
    }
};

#endif //INC_8051TUTORIAL_DESTRUCTIONSYSTEM_H