//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_TOOLSERVICE_H
#define INC_8051PROJECT_TOOLSERVICE_H

#include "../../ecs/core/Entity.h"
#include "../GameplayEnums.h"

class World;

class ToolService {
public:
    static bool useTool(World& world, Entity& player, PlayerAction action, int x, int y);
};

#endif //INC_8051PROJECT_TOOLSERVICE_H