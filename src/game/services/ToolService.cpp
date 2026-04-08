//
// Created by Iris Chow on 2026-04-06.
//

#include "ToolService.h"

#include <iostream>
#include <ostream>

#include "CropService.h"
#include "../../ecs/core/World.h"
#include "../GameplayEnums.h"
#include "../../map/MapData.h"

bool ToolService::useTool(World& world, Entity &player, const PlayerAction action, const int x, const int y) {
    auto& map = world.getMap();

    switch (action) {
        case PlayerAction::TILL: {
            FarmTile* tile = map.getFarmTileAt(x, y);

            if (!tile) {
                return false;
            }

            if (tile->isTilled || tile->hasCrop()) {
                return false;
            }

            tile->isTilled = true;

            // SFX after action
            world.getAudioEventQueue().push(std::make_unique<AudioEvent>("till"));

            std::cout << "Tilled tile at (" << x << ", " << y << ")" << std::endl;
            return true;
        }

        case PlayerAction::WATER:
            return CropService::water(world, x, y);

        case PlayerAction::PLANT:
            return CropService::plant(world, player, x, y);

        case PlayerAction::HARVEST:
            return CropService::harvest(world, player, x, y);

        case PlayerAction::NONE:
        default:
            return false;
    }
}
