//
// Created by Iris Chow on 2026-03-31.
//

#ifndef INC_8051PROJECT_TILESET_H
#define INC_8051PROJECT_TILESET_H

#include <SDL3/SDL_render.h>
#include <string>

struct Tileset {
    int firstGid{};
    int tileWidth{};
    int tileHeight{};
    int columns{};
    int tileCount{};

    SDL_Texture* texture{}; // Non-owning
    std::string name;
};

#endif //INC_8051PROJECT_TILESET_H