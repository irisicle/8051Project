//
// Created by Iris Chow on 2026-03-11.
//

#ifndef INC_8051PROJECT_RENDERUTILS_H
#define INC_8051PROJECT_RENDERUTILS_H

#include <SDL3/SDL_rect.h>

namespace RenderUtils {

    // Scaling from center point
    [[nodiscard]] inline SDL_FRect getScaledDest(const SDL_FRect& dest, const float scale) {
        return SDL_FRect{
            dest.x + dest.w * (1 - scale) / 2,
            dest.y + dest.h * (1 - scale) / 2,
            dest.w * scale,
            dest.h * scale,
        };
    }

}

#endif //INC_8051PROJECT_RENDERUTILS_H