//
// Created by Iris Chow on 2026-03-11.
//

#ifndef INC_8051PROJECT_MOUSEINPUTSYSTEM_H
#define INC_8051PROJECT_MOUSEINPUTSYSTEM_H

#include <SDL3/SDL_events.h>

class World;

class MouseInputSystem {
public:
    static void update(World& world, const SDL_Event& event);
};

#endif //INC_8051PROJECT_MOUSEINPUTSYSTEM_H