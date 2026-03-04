//
// Created by Iris Chow on 2026-01-14.
//

#ifndef INC_8051TUTORIAL_MAP_H
#define INC_8051TUTORIAL_MAP_H

#include "ecs/Component.h"
#include <vector>

class Map {

public:
    Map() = default;
    ~Map() = default;

    void load(const char* path, SDL_Texture* ts);
    void draw(const Camera& cam) const;

    SDL_Texture* tileset = nullptr;
    int width{}, height{};
    std::vector<std::vector<int>> tileData;
    std::vector<Collider> colliders;
    std::vector<SpawnPoint> spawnPoints;

};

#endif //INC_8051TUTORIAL_MAP_H