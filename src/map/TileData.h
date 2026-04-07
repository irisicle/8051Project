//
// Created by Iris Chow on 2026-03-31.
//

#ifndef INC_8051PROJECT_TILE_H
#define INC_8051PROJECT_TILE_H

#include "TileTypes.h"
#include "../utils/CropEnums.h"

struct TileData {
    int gid{0};
    TileState state{TileState::UNTILLED};

    TileData() = default;
    explicit TileData(const int gid, TileState state) : gid{gid}, state {state} {}
};

#endif //INC_8051PROJECT_TILE_H