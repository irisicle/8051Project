//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_ITEMDATA_H
#define INC_8051PROJECT_ITEMDATA_H

#include <string>
#include <SDL3/SDL.h>
#include "../GameplayEnums.h"
#include "../../utils/ItemEnums.h"
#include "../../utils/CropEnums.h"

struct ItemData {
    std::string name{};
    ItemId id{ItemId::NONE};
    ItemCategory category{ItemCategory::NONE};
    PlayerAction useAction{PlayerAction::NONE};

    int maxStackSize{99};
    bool consumableOnUse{false};

    CropType cropType{CropType::NONE};

    SDL_Texture* texture{nullptr};
    SDL_FRect src{};
};

#endif //INC_8051PROJECT_ITEMDATA_H