//
// Created by Iris Chow on 2026-04-06.
//

#include "CropService.h"

#include "../data/CropData.h"
#include "../../ecs/component/Inventory.h"
#include "../../ecs/component/Physics.h"
#include "../../ecs/component/Render.h"
#include "../../ecs/core/World.h"
#include "../data/CropVisualDatabase.h"
#include "../data/ItemDatabase.h"

bool CropService::water(World& world, const int x, const int y) {
    auto& map = world.getMap();

    FarmTile* tile = map.getFarmTileAt(x, y);
    if (!tile) {
        return false;
    }

    if (!tile->isTilled) {
        return false;
    }

    tile->isWatered = true;

    // Watering successful
    return true;
}

bool CropService::plant(World& world, Entity& player, const int x, const int y) {
    auto& map = world.getMap();

    FarmTile* tile = map.getFarmTileAt(x, y);
    if (!tile) {
        return false;
    }

    if (!tile->isTilled) {
        return false;
    }

    if (tile->hasCrop()) {
        return false;
    }

    auto& inventory = player.getComponent<Inventory>();
    const auto& selected = inventory.getSelectedItem();
    const auto& item = ItemDatabase::get(selected.id);

    if (item.cropType == CropType::NONE) {
        return false;
    }

    const auto& visualData = CropVisualDatabase::get(item.cropType);

    auto& crop = world.createEntity();

    crop.addComponent<Crop>(item.cropType, 0, 10.0f);
    crop.addComponent<Transform>(Vector2D(
        static_cast<float>(x) * Constants::TILE_SIZE,
        static_cast<float>(y) * Constants::TILE_SIZE), 0.0f, 1.0f
        );

    crop.addComponent<Sprite>(
        visualData.texture,
        visualData.stageFrames[0],
        visualData.width,
        visualData.height,
        RenderLayer::WORLD
        );

    tile->crop = &crop;

    // Planting successful
    return true;
}

bool CropService::harvest(World& world, Entity& player, const int x, const int y) {
    auto& map = world.getMap();
    FarmTile* tile = map.getFarmTileAt(x, y);
    if (!tile) {
        return false;
    }

    if (!tile->hasCrop()) {
        return false;
    }

    auto* cropEntity = tile->crop;

    // Return false if crop is NOT yet ready to harvest
    if (const auto& crop = cropEntity->getComponent<Crop>(); crop.stage < static_cast<int>(CropStage::RIPENING)) {
        return false;
    }

    // TODO: ADD TO INVENTORY SERVICE

    // Delete crop entity
    cropEntity->destroy();

    tile->crop = nullptr;
    tile->isWatered = false;

    // Harvest successful
    return true;
}