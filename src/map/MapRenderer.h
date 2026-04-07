//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_MAPRENDERER_H
#define INC_8051PROJECT_MAPRENDERER_H

#include "MapData.h"
#include "../ecs/core/Camera.h"

class MapRenderer {
public:
    static void draw(const MapData& mapData, const Camera& camera);
};

#endif //INC_8051PROJECT_MAPRENDERER_H