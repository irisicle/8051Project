//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_CROPVISUALSYSTEM_H
#define INC_8051PROJECT_CROPVISUALSYSTEM_H

#include <vector>

#include "../ecs/component/Render.h"
#include "../ecs/core/Entity.h"
#include "../game/data/CropData.h"
#include "../game/data/CropVisualDatabase.h"

class CropVisualSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities) {
        for (const auto& entity : entities) {
            if (!entity->hasComponent<Crop>() || !entity->hasComponent<Sprite>()) {
                continue;
            }

            const auto& crop = entity->getComponent<Crop>();
            auto& sprite = entity->getComponent<Sprite>();

            const auto& visualData = CropVisualDatabase::get(crop.type);

            if (visualData.stageFrames.empty()) {
                continue;
            }

            // Ensure out-of-bounds animation frame index is never accessed
            const std::size_t maxIndex = visualData.stageFrames.size() - 1;
            const std::size_t clampedStage = std::min<std::size_t>(static_cast<std::size_t>(crop.stage), maxIndex);

            sprite.texture = visualData.texture;
            sprite.src = visualData.stageFrames[clampedStage];
            sprite.width = visualData.width;
            sprite.height = visualData.height;
        }
    }
};

#endif //INC_8051PROJECT_CROPVISUALSYSTEM_H