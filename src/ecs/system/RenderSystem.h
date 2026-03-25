//
// Created by Iris Chow on 2026-01-21.
//

#ifndef INC_8051PROJECT_RENDERSYSTEM_H
#define INC_8051PROJECT_RENDERSYSTEM_H
#include <memory>
#include <vector>

#include "../Component.h"
#include "../Entity.h"
#include "../../manager/TextureManager.h"

class RenderSystem {
public:
    static void render(const std::vector<std::unique_ptr<Entity>>& entities) {

        Entity* cameraEntity = nullptr;

        // Find camera
        for (auto& entity : entities) {
            if (entity->hasComponent<Camera>()) {
                cameraEntity = entity.get();
                break;
            }
        }
        if (!cameraEntity) return; // No camera

        const auto& camera = cameraEntity->getComponent<Camera>();

        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                const auto& transform = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::World) continue;

                // Converting from world space to screen space
                sprite.dst.x = transform.position.x - camera.view.x;
                sprite.dst.y = transform.position.y - camera.view.y;

                // If the entity has animation, update the source rect
                if (entity->hasComponent<Animation>()) {
                    auto& animation = entity->getComponent<Animation>();
                    sprite.src = animation.clips[animation.currentClip].frameIndices[animation.currentFrame];
                }

                TextureManager::draw(sprite.texture, sprite.src, sprite.dst);
            }
        }
    }
};

#endif //INC_8051PROJECT_RENDERSYSTEM_H