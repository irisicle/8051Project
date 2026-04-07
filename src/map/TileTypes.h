//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_TILETYPES_H
#define INC_8051PROJECT_TILETYPES_H

enum class TileLayer {
    Water,
    Terrain,
    Environment,
    Soil,
    Farming,
    Path,
    Fence,
    Building,
    COUNT
};

enum class TileState {
    UNTILLED,
    TILLED,
    WATERED,
    HARVESTABLE
};

#endif //INC_8051PROJECT_TILETYPES_H