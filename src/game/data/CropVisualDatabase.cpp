//
// Created by Iris Chow on 2026-04-06.
//

#include "CropVisualDatabase.h"

#include "../../manager/TextureManager.h"

// Encapsulation
namespace {

    bool initialized{false};
    std::unordered_map<CropType, CropVisualData> crops;

}

void CropVisualDatabase::initialize() {

    // Do not continue if texture has already been loaded to avoid duplicates
    if (initialized) {
        return;
    }

    SDL_Texture *texture = TextureManager::load("../asset/animations/plants/crops.png");

    crops[CropType::CARROT] = {
        CropType::CARROT,
        texture,
        {
            SDL_FRect{32, 64, 32, 32},
            SDL_FRect{0, 0, 32, 32},
            SDL_FRect{0, 0, 32, 32},
            SDL_FRect{0, 0, 32, 32},
            SDL_FRect{0, 0, 32, 32},
            SDL_FRect{0, 0, 32, 32},
        },
        32.0f,
        32.0f
    };

    initialized = true;
}

const CropVisualData &CropVisualDatabase::get(const CropType type) {
    return crops.at(type);
}
