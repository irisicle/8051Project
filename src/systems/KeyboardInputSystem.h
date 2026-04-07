//
// Created by Iris Chow on 2026-01-28.
//

#ifndef INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H
#define INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H

#include <SDL3/SDL_events.h>
#include <vector>
#include <memory>

#include "../ecs/core/Entity.h"

class World;

class KeyboardInputSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>> &entities, const SDL_Event &event);
};

#endif //INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H