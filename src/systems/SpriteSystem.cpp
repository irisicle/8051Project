//
// Created by Iris Chow on 2026-04-06.
//

#include "SpriteSystem.h"
#include "../ecs/core/Entity.h"
#include "../manager/TextureManager.h"
#include "../ecs/component/Render.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Animation.h"
#include "../ecs/core/Camera.h"
#include "../ecs/core/World.h"

void SpriteSystem::draw(const std::vector<std::unique_ptr<Entity>> &entities, const Camera& camera) {
    for (const auto &entity: entities) {
        if (!entity->hasComponent<Transform>() || !entity->hasComponent<Sprite>()) {
            continue;
        }

        const auto &transform = entity->getComponent<Transform>();
        auto &sprite = entity->getComponent<Sprite>();

        if (!sprite.visible || !sprite.texture || sprite.renderLayer != RenderLayer::WORLD) {
            continue;
        }

        SDL_FRect src = sprite.src;

        // If the entity has animation, update the source rect for this frame
        if (entity->hasComponent<Animation>()) {
            const auto &animation = entity->getComponent<Animation>();

            // Avoid out-of-range frame access
            if (const auto clipIt = animation.clips.find(animation.currentClip); clipIt != animation.clips.end()
                && animation.currentFrame < clipIt->second.frames.size()) {
                src = clipIt->second.frames[animation.currentFrame];
            }
        }

        const SDL_FRect dest{
            transform.position.x - camera.view.x,
            transform.position.y - camera.view.y,
            sprite.width * transform.scale,
            sprite.height * transform.scale
        };

        // Culling - skip off-screen entities
        if (dest.x + dest.w < 0.0f ||
            dest.y + dest.h < 0.0f ||
            dest.x > camera.view.w ||
            dest.y > camera.view.h) {
            continue;
        }

        TextureManager::draw(sprite.texture, src, dest);
    }
}
