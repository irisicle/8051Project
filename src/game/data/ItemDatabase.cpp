//
// Created by Iris Chow on 2026-04-05.
//

#include "ItemDatabase.h"
#include "../../manager/TextureManager.h"

std::unordered_map<ItemId, ItemData, ItemIdHash> ItemDatabase::items{};
bool ItemDatabase::initialized{false};

void ItemDatabase::initialize() {
    if (initialized) {
        return;
    }

    SDL_Texture* toolTexture = TextureManager::load("../asset/objects/Tools.png");
    SDL_Texture* seedTexture = TextureManager::load("../asset/objects/seeds_and_crops.png");

    items[ItemId::NONE] = {
        "Empty",
        ItemId::NONE,
        ItemCategory::NONE,
        PlayerAction::NONE,
        0,
        false,
        CropType::NONE,
        nullptr,
        SDL_FRect{0, 0, 0, 0}
    };

    items[ItemId::HOE] = {
        "Hoe",
        ItemId::HOE,
        ItemCategory::TOOL,
        PlayerAction::TILL,
        1,
        false,
        CropType::NONE,
        toolTexture,
        SDL_FRect{16, 80, 16, 16}
    };

    items[ItemId::WATERING_CAN] = {
        "Watering Can",
        ItemId::WATERING_CAN,
        ItemCategory::TOOL,
        PlayerAction::WATER,
        1,
        false,
        CropType::NONE,
        toolTexture,
        SDL_FRect{16, 0, 16, 16}
    };

    items[ItemId::CARROT_SEEDS] = {
        "Carrot Seeds",
        ItemId::CARROT_SEEDS,
        ItemCategory::SEED,
        PlayerAction::PLANT,
        99,
        true,
        CropType::CARROT,
        seedTexture,
        SDL_FRect{0, 16, 16, 16}
    };

    initialized = true;
}

const ItemData& ItemDatabase::get(const ItemId id) {
    if (!initialized) {
        initialize();
    }

    if (const auto it = items.find(id); it != items.end()) {
        return it->second;
    }

    return items.at(ItemId::NONE);
}
