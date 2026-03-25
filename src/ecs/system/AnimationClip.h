//
// Created by Iris Chow on 2026-02-22.
//

#ifndef INC_8051PROJECT_ANIMATIONCLIP_H
#define INC_8051PROJECT_ANIMATIONCLIP_H
#include <vector>
#include <SDL3/SDL_rect.h>

struct AnimationClip {
    std::vector<SDL_FRect> frameIndices;
};
#endif //INC_8051PROJECT_ANIMATIONCLIP_H