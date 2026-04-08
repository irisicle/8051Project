//
// Created by Iris Chow on 2026-04-06.
//

#include "SelectionHighlightSystem.h"
#include "../ecs/component/Interaction.h"
#include "../ecs/component/Physics.h"
#include "../ecs/component/Tag.h"
#include "../ecs/core/Camera.h"
#include "../utils/Constants.h"
#include "../utils/GridUtils.h"

void SelectionHighlightSystem::update(const std::vector<std::unique_ptr<Entity>> &entities, const Camera& camera) {
    visible = false;

    Entity* player = nullptr;

    for (const auto& entity : entities) {
        if (entity->hasComponent<PlayerTag>()) {
            player = entity.get();
            break;
        }
    }

    if (!player || !player->hasComponent<Transform>() || !player->hasComponent<Facing>()) {
        return;
    }

    const auto& transform = player->getComponent<Transform>();
    const auto& facing = player->getComponent<Facing>();
    const Vector2D target = GridUtils::getFacingTile(transform.position, facing.direction, transform.scale, Constants::TILE_SIZE);

    rect.x = std::round(target.x * Constants::TILE_SIZE - camera.view.x);
    rect.y = std::round(target.y * Constants::TILE_SIZE - camera.view.y);
    rect.w = Constants::TILE_SIZE;
    rect.h = Constants::TILE_SIZE;

    visible = true;
}

void SelectionHighlightSystem::draw(SDL_Renderer* renderer) const {
    if (!visible) {
        return;
    }

    // Draw highlighter
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
    SDL_RenderFillRect(renderer, &rect);

    // Draw outline
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 180);
    SDL_RenderRect(renderer, &rect);
}
