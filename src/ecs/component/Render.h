//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_RENDER_H
#define INC_8051PROJECT_RENDER_H

#include <SDL3/SDL_render.h>

enum class RenderLayer {
    WORLD,
    UI
};

struct Sprite {
    SDL_Texture* texture{nullptr};
    SDL_FRect src{};

    float width{0.0f};
    float height{0.0f};

    RenderLayer renderLayer{};
    bool visible{true};
};

#endif //INC_8051PROJECT_RENDER_H