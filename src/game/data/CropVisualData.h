//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_CROPVISUALDATA_H
#define INC_8051PROJECT_CROPVISUALDATA_H
#include <vector>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "../../utils/CropEnums.h"

struct CropVisualData {
    CropType type{CropType::NONE};

    SDL_Texture* texture{nullptr};
    std::vector<SDL_FRect> stageFrames{};

    float width{32.0f};
    float height{32.0f};
};

#endif //INC_8051PROJECT_CROPVISUALDATA_H