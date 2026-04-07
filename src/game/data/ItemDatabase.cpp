//
// Created by Iris Chow on 2026-04-05.
//

#include "ItemDatabase.h"

const std::unordered_map<ItemId, ItemData> ItemDatabase::items{
    {
        ItemId::NONE,
        {
            "Empty",
            ItemId::NONE,
            ItemCategory::NONE,
            PlayerAction::NONE,
            0,
            false,
            CropType::NONE
        }
    },
    {
        ItemId::HOE,
        {
            "Hoe",
            ItemId::HOE,
            ItemCategory::TOOL,
            PlayerAction::TILL,
            1,
            false,
            CropType::NONE
        }
    },
    {
        ItemId::WATERING_CAN,
        {
            "Watering Can",
            ItemId::WATERING_CAN,
            ItemCategory::TOOL,
            PlayerAction::WATER,
            1,
            false,
            CropType::NONE
        }
    },
    {
        ItemId::CARROT_SEEDS,
        {
            "Carrot Seeds",
            ItemId::CARROT_SEEDS,
            ItemCategory::SEED,
            PlayerAction::PLANT,
            99,
            true,
            CropType::CARROT
        }
    }


};

const ItemData& ItemDatabase::get(const ItemId id) {
    if (const auto it = items.find(id); it != items.end()) {
        return it->second;
    }

    return items.at(ItemId::NONE);
}
