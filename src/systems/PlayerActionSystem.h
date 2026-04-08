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
    static void update(const std::vector<std::unique_ptr<Entity>> &entities, World &world);

private:
    static void consumeSelectedItem(Inventory &inventory, int amount);
};

#endif //INC_8051PROJECT_PLAYERACTIONSYSTEM_H
