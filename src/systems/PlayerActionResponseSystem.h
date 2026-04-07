//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_PLAYERACTIONRESPONSESYSTEM_H
#define INC_8051PROJECT_PLAYERACTIONRESPONSESYSTEM_H

#include "../ecs/event/BaseEvent.h"
#include "../game/services/ToolService.h"

class World;

class PlayerActionResponseSystem {
public:
    static void handle(const PlayerActionEvent &event, World &world) {
        if (!event.player) {
            return;
        }

        ToolService::useTool(
            world,
            *event.player,
            event.action,
            event.gridX,
            event.gridY
        );
    }
};

#endif //INC_8051PROJECT_PLAYERACTIONRESPONSESYSTEM_H
