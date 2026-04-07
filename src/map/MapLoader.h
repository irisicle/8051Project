//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_MAPLOADER_H
#define INC_8051PROJECT_MAPLOADER_H

#include "MapData.h"

class World;

class MapLoader {
public:
    static MapData load(const char* path, World& world);
};

#endif //INC_8051PROJECT_MAPLOADER_H