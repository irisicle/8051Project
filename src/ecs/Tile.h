//
// Created by Iris Chow on 2026-03-27.
//

#ifndef INC_8051PROJECT_TILE_H
#define INC_8051PROJECT_TILE_H

#include "../utils/Vector2D.h"

enum class TileState {
    Untilled,
    Tilled,
    Planted,
    Watered,
    Harvestable,
};

struct Tile {
    TileState state = TileState::Untilled;
    int gid{};
    bool isSteppable = true;
};

struct Grid {
    Vector2D position{};
};

#endif //INC_8051PROJECT_TILE_H