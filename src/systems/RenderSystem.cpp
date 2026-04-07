//
// Created by Iris Chow on 2026-04-06.
//

#include "RenderSystem.h"
#include <SDL3/SDL_render.h>
#include "SpriteSystem.h"
#include "../map/MapRenderer.h"
#include "../ecs/core/World.h"

void RenderSystem::render(World& world, SDL_Renderer* renderer, const Camera& camera) {

    // Draw map
    MapRenderer::draw(world.getMap(), camera);

    // Draw world sprites
    SpriteSystem::draw(world.getEntities(), camera);

    // Draw selection highlight
    world.getSelectionHighlightSystem().draw(renderer);

    // Draw UI
}