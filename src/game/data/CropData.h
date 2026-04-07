//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_CROPDATA_H
#define INC_8051PROJECT_CROPDATA_H

#include "../../ecs/core/Component.h"
#include "../../utils/CropEnums.h"

struct Crop : Component {
    CropType type{CropType::NONE};
    int stage{0}; // Growth stage
    float growthTimer{0.0f};
    float timePerStage{10.0f}; // Amount of time in seconds needed to reach next growth stage
    bool isWatered{false};

    Crop() = default;

    explicit Crop(const CropType type, const int stage = 0, const float timePerStage = 10.0f) : type(type), stage(stage), timePerStage(timePerStage) {}
};

#endif //INC_8051PROJECT_CROPDATA_H