//
// Created by Iris Chow on 2026-03-29.
//

#ifndef INC_8051PROJECT_GROWTHSYSTEM_H
#define INC_8051PROJECT_GROWTHSYSTEM_H

#include <iostream>
#include <vector>

#include "../ecs/core/Entity.h"
#include "../game/data/CropData.h"

class CropGrowthSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, const float deltaTime) {
        for (auto& entity : entities) {
            if (!entity->hasComponent<Crop>()) {
                continue;
            }

            auto& crop = entity->getComponent<Crop>();

            if (!crop.isWatered) {
                continue;
            }

            // Advance timer
            crop.growthTimer += deltaTime;

            // Reset timer for next growth stage and advance crop stage
            if (crop.growthTimer >= crop.timePerStage) {
                crop.growthTimer = 0.0f;
                crop.stage++;
            }

            std::cout << "Crop has grown to " << crop.stage << " stage." << std::endl;
        }
    }
};

#endif //INC_8051PROJECT_GROWTHSYSTEM_H