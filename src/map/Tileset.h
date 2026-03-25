//
// Created by Iris Chow on 2026-03-14.
//

#ifndef INC_8051PROJECT_TILESET_H
#define INC_8051PROJECT_TILESET_H

#include <SDL3/SDL.h>

struct Tileset {
    int firstGid{};
    int tileWidth{};
    int tileHeight{};
    int columns{};
    int tileCount{};

    SDL_Texture* texture{};
};

#endif //INC_8051PROJECT_TILESET_H