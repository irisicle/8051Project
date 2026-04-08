//
// Created by Iris Chow on 2026-04-08.
//

#include "PlayerActionSystem.h"

#include <iostream>
#include "../utils/Constants.h"

void PlayerActionSystem::update(const std::vector<std::unique_ptr<Entity>> &entities, World &world) {
    for (const auto &entity: entities) {
        if (!entity->hasComponent<PlayerTag>() || !entity->hasComponent<PlayerIntent>() || !entity->hasComponent<Transform>() ||
            !entity->hasComponent<Facing>() || !entity->hasComponent<Inventory>()) {
            continue;
        }

        auto &intent = entity->getComponent<PlayerIntent>();
        auto &inventory = entity->getComponent<Inventory>();
        const auto &transform = entity->getComponent<Transform>();
        const auto &facing = entity->getComponent<Facing>();

        if (!intent.usePressed) {
            continue;
        }

        if (!inventory.isValidSelectedIndex()) {
            intent.usePressed = false;
            continue;
        }

        auto &selectedItem = inventory.getSelectedItem();
        const auto &item = ItemDatabase::get(selectedItem.id);

        if (item.useAction == PlayerAction::NONE) {
            intent.usePressed = false;
            continue;
        }

        const Vector2D target = GridUtils::getFacingTile(
            transform.position,
            facing.direction,
            transform.scale,
            static_cast<float>(Constants::TILE_SIZE)
        );

        // Item amount -1 if action successful
        if (const bool success = ToolService::useTool(
            world,
            *entity,
            item.useAction,
            static_cast<int>(target.x),
            static_cast<int>(target.y)); success && item.consumableOnUse) {
            consumeSelectedItem(inventory, 1);
        }

        // Reset intent
        intent.usePressed = false;
    }
}

void PlayerActionSystem::consumeSelectedItem(Inventory &inventory, const int amount = 1) {
    if (!inventory.isValidSelectedIndex()) {
        return;
    }

    auto &item = inventory.getSelectedItem();

    if (item.count <= 0) {
        return;
    }

    item.count -= amount;

    if (item.count <= 0) {
        item.id = ItemId::NONE;
        item.count = 0;
    }
}
