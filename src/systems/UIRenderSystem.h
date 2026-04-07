//
// Created by Iris Chow on 2026-03-11.
//

#ifndef INC_8051PROJECT_UIRENDERSYSTEM_H
#define INC_8051PROJECT_UIRENDERSYSTEM_H

#include <vector>

#include "../ecs/core/Entity.h"
#include "../utils/RenderUtils.h"
#include "../manager/TextureManager.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Render.h"

class UIRenderSystem {
public:
    static void render(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            if (!entity->hasComponent<Transform>() || !entity->hasComponent<Sprite>()) {
                continue;
            }

            const auto& transform = entity->getComponent<Transform>();
            auto& sprite = entity->getComponent<Sprite>();

            if (!sprite.texture || !sprite.visible || sprite.renderLayer != RenderLayer::UI) {
                continue;
            }

            const SDL_FRect src = sprite.src;

            const SDL_FRect dest{
                transform.position.x,
                transform.position.y,
                sprite.width * transform.scale,
                sprite.height * transform.scale
            };

            TextureManager::draw(sprite.texture, src, dest);
        }
    }
};

#endif //INC_8051PROJECT_UIRENDERSYSTEM_H