//
// Created by Iris Chow on 2026-03-04.
//

#ifndef INC_8051PROJECT_MAINMENUSYSTEM_H
#define INC_8051PROJECT_MAINMENUSYSTEM_H

#include <SDL3/SDL_events.h>

class MainMenuSystem {
public:
    static void update(const SDL_Event& event);
};

#endif //INC_8051PROJECT_MAINMENUSYSTEM_H