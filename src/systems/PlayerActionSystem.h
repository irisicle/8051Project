//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_PLAYERACTIONSYSTEM_H
#define INC_8051PROJECT_PLAYERACTIONSYSTEM_H

#include <memory>
#include <vector>

#include "../ecs/component/Interaction.h"
#include "../ecs/component/Inventory.h"
#include "../ecs/core/Entity.h"
#include "../ecs/component/Tag.h"
#include "../ecs/component/Physics.h"
#include "../ecs/core/World.h"
#include "../game/data/ItemDatabase.h"
#include "../utils/GridUtils.h"
#include "../game/services/ToolService.h"

class PlayerActionSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>> &entities, World &world) {
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
            if (const bool success = ToolService::useTool(world, *entity, item.useAction, target.x, target.y); success && item.consumableOnUse) {
                consumeSelectedItem(inventory);
            }

            // Reset intent
            intent.usePressed = false;
        }
    }

private:
    static void consumeSelectedItem(Inventory &inventory, int amount = 1) {
        if (!inventory.isValidSelectedIndex()) {
            return;
        }

        auto& item = inventory.getSelectedItem();

        if (item.count <= 0) {
            return;
        }

        item.count -= amount;

        if (item.count <= 0) {
            item.id = ItemId::NONE;
            item.count = 0;
        }
    }
};

#endif //INC_8051PROJECT_PLAYERACTIONSYSTEM_H
