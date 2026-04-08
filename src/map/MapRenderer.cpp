//
// Created by Iris Chow on 2026-04-06.
//

#include "MapRenderer.h"

#include <iostream>

#include "TileData.h"
#include "MapData.h"
#include "../ecs/component/Render.h"
#include "../ecs/component/Physics.h"
#include "../utils/Constants.h"
#include "../manager/TextureManager.h"

// Helper to draw tilled soil overlay
void MapRenderer::drawTilledOverlay(MapData &mapData, SDL_Renderer* renderer, const Camera& camera) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 110, 70, 40, 140);

    for (int row = 0; row < mapData.height; row++) {
        for (int col = 0; col < mapData.width; col++) {
            if (const FarmTile* farmTile = mapData.getFarmTileAt(col, row); !farmTile || !farmTile->isTilled) {
                continue;
            }

            const SDL_FRect dest {
                std::round(static_cast<float>(col) * Constants::TILE_SIZE - camera.view.x),
                std::round(static_cast<float>(row) * Constants::TILE_SIZE - camera.view.y),
                static_cast<float>(Constants::TILE_SIZE),
                static_cast<float>(Constants::TILE_SIZE)
            };

            SDL_RenderFillRect(renderer, &dest);
        }
    }
}

void MapRenderer::draw(MapData &mapData, SDL_Renderer *renderer, const Camera &camera) {
    SDL_FRect src{}, dest{};
    dest.w = dest.h = Constants::TILE_SIZE;

    for (std::size_t layerIndex = 0; layerIndex < mapData.grid.size(); layerIndex++) {
        const auto& layer = mapData.grid[layerIndex];

        for (int i = 0; i < mapData.width * mapData.height; i++) {
            Entity* gridEntity = layer[i];
            if (!gridEntity) {
                continue;
            }

            const auto& sprite = gridEntity->getComponent<Sprite>();
            const auto& tile = gridEntity->getComponent<TileData>();
            const auto& transform = gridEntity->getComponent<Transform>();

            // DO NOT DRAW tile if gid is blank
            if (tile.gid == 0) {
                continue;
            }

            const auto& ts = mapData.getTilesetFromGid(tile.gid);
            if (!ts || !ts->texture) {
                continue;
            }

            // Calculate src rect using tile.gid
            const int localId = tile.gid - ts->firstGid;
            const int srcX = (localId % ts->columns) * ts->tileWidth;
            const int srcY = (localId / ts->columns) * ts->tileHeight;

            src.x = static_cast<float>(srcX);
            src.y = static_cast<float>(srcY);
            src.w = static_cast<float>(ts->tileWidth);
            src.h = static_cast<float>(ts->tileHeight);

            dest.x = std::round(transform.position.x - camera.view.x);
            dest.y = std::round(transform.position.y - camera.view.y);

            TextureManager::draw(sprite.texture, src, dest);
        }
    }

    drawTilledOverlay(mapData, renderer, camera);
}