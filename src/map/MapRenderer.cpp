//
// Created by Iris Chow on 2026-04-06.
//

#include "MapRenderer.h"

#include "TileData.h"
#include "../ecs/component/Render.h"
#include "../ecs/component/Physics.h"
#include "../utils/Constants.h"
#include "../manager/TextureManager.h"

void MapRenderer::draw(const MapData &mapData, const Camera &camera) {
    SDL_FRect src{}, dest{};
    dest.w = dest.h = Constants::TILE_SIZE;

    for (const auto& layer : mapData.grid) {
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
}