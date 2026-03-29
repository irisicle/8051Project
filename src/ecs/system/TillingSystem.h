//
// Created by Iris Chow on 2026-03-26.
//

#ifndef INC_8051PROJECT_TILLINGSYSTEM_H
#define INC_8051PROJECT_TILLINGSYSTEM_H
#include <vector>

#include "EventResponseSystem.h"
#include "../Component.h"
#include "../Entity.h"

class World;

class TillingSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, float deltaTime);
};

#endif //INC_8051PROJECT_TILLINGSYSTEM_H