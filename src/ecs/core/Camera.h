//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_CAMERA_H
#define INC_8051PROJECT_CAMERA_H

#include <SDL3/SDL_rect.h>

struct Camera {
    SDL_FRect view{};
    float worldWidth{0.0f};
    float worldHeight{0.0f};
};

#endif //INC_8051PROJECT_CAMERA_H