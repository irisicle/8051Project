//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_MAPRENDERER_H
#define INC_8051PROJECT_MAPRENDERER_H

#include "MapData.h"
#include "../ecs/core/Camera.h"

class MapRenderer {
public:
    static void draw(MapData &mapData, SDL_Renderer *renderer, const Camera &camera);

private:
    static void drawTilledOverlay(MapData &mapData, SDL_Renderer* renderer, const Camera &camera);
};

#endif //INC_8051PROJECT_MAPRENDERER_H