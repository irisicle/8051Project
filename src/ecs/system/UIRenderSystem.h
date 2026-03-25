//
// Created by Iris Chow on 2026-03-11.
//

#ifndef INC_8051PROJECT_UIRENDERSYSTEM_H
#define INC_8051PROJECT_UIRENDERSYSTEM_H

#include <vector>

#include "../Component.h"
#include "../Entity.h"
#include "../../utils/RenderUtils.h"
#include "../../manager/TextureManager.h"

class UIRenderSystem {
public:
    static void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (entity->hasComponent<Transform>() && entity->hasComponent<Sprite>()) {
                const auto& transform = entity->getComponent<Transform>();
                auto& sprite = entity->getComponent<Sprite>();

                if (sprite.renderLayer != RenderLayer::UI) continue;

                // No converting from world space to screen space
                sprite.dst.x = transform.position.x;
                sprite.dst.y = transform.position.y;

                if (sprite.visible) {
                    const SDL_FRect scaledDest = RenderUtils::getScaledDest(sprite.dst, transform.scale);
                    TextureManager::draw(sprite.texture, sprite.src, scaledDest);
                }
            }
        }
    }
};

#endif //INC_8051PROJECT_UIRENDERSYSTEM_H