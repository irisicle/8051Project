//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_RENDER_H
#define INC_8051PROJECT_RENDER_H

#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

enum class RenderLayer {
    WORLD,
    UI
};

enum class LabelType {
    SEASON,
    DAY,
    TIME,
};

struct Sprite {
    SDL_Texture* texture{nullptr};
    SDL_FRect src{};

    float width{0.0f};
    float height{0.0f};

    RenderLayer renderLayer{};
    bool visible{true};
};

struct Label {
    std::string text{};
    TTF_Font* font{nullptr};
    SDL_Color color{};
    LabelType type{};
    std::string textureCacheKey{};
    SDL_Texture* texture{nullptr};
    SDL_FRect dst{};
    bool visible{true};
    bool dirty{false};
};

#endif //INC_8051PROJECT_RENDER_H