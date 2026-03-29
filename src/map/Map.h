//
// Created by Iris Chow on 2026-01-14.
//

#ifndef INC_8051PROJECT_MAP_H
#define INC_8051PROJECT_MAP_H

#include <vector>

#include "../ecs/Component.h"
#include "Tileset.h"

class Map {
public:
    Map() = default;
    ~Map() = default;

    void load(const char* path);
    void draw(const Camera& cam) const;

    int width{}, height{};

    [[nodiscard]] const Tileset* getTilesetFromGid(int gid) const;

    std::vector<Tileset>tilesets;
    std::vector<std::vector<std::vector<int>>> layers;
    std::vector<Collider> colliders;
    std::vector<SavePoint> savePoints;
    std::vector<SpawnPoint> spawnPoints;
};

#endif //INC_8051PROJECT_MAP_H