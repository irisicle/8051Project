//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_MAPDATA_H
#define INC_8051PROJECT_MAPDATA_H

#include <string>
#include <vector>
#include <SDL3/SDL_rect.h>

#include "Tileset.h"
#include "TileTypes.h"
#include "../utils/Vector2D.h"
#include "../ecs/core/Entity.h"

struct SpawnMarker {
    Vector2D position{};
    std::string type{};
    std::string name{};
};

struct MapCollider {
    SDL_FRect bounds{};
    bool isSolid{true};
};

struct FarmTile {
    bool isFarmable{false};
    bool isTilled{false};
    bool isWatered{false};
    Entity* crop{nullptr}; // Does not own

    [[nodiscard]] bool hasCrop() const {
        return crop != nullptr;
    }
};

struct MapData {
    int width{0};
    int height{0};

    std::array<std::vector<Entity*>, static_cast<size_t>(TileLayer::COUNT)> grid{};
    std::vector<Tileset> tilesets{};
    std::vector<MapCollider> colliders{};
    std::vector<SpawnMarker> spawnMarkers{};
    std::vector<FarmTile> farmTiles{};

    [[nodiscard]] bool isInBounds(const int x, const int y) const {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    [[nodiscard]] int toIndex(const int x, const int y) const {
        return y * width + x;
    }

    [[nodiscard]] Entity* getEntityAt(const int x, const int y, TileLayer layer) const {
        if (!isInBounds(x, y)) {
            return nullptr;
        }

        const auto& layerVector = grid[static_cast<size_t>(layer)];
        return layerVector[toIndex(x, y)];
    }

    void setEntityAt(const int x, const int y, Entity* entity, TileLayer layer) {
        if (!isInBounds(x, y)) {
            return;
        }

        grid[static_cast<size_t>(layer)][toIndex(x, y)] = entity;
    }

    [[nodiscard]] FarmTile *getFarmTileAt(const int x, const int y) {
        if (!isInBounds(x, y)) {
            return nullptr;
        }

        return &farmTiles[toIndex(x, y)];
    }

    [[nodiscard]] const Tileset* getTilesetFromGid(const int gid) const {
        for (int i = static_cast<int>(tilesets.size()) - 1; i >= 0; i--) {
            if (gid >= tilesets[i].firstGid) {
                return &tilesets[i];
            }
        }

        return nullptr;
    }
};

#endif //INC_8051PROJECT_MAPDATA_H