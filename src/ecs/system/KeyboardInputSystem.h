//
// Created by Iris Chow on 2026-01-28.
//

#ifndef INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H
#define INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H

#include <SDL3/SDL_events.h>
#include <vector>
#include <memory>

#include "../Entity.h"
#include "../Component.h"

class KeyboardInputSystem {
public:
    static void update(const std::vector<std::unique_ptr<Entity>>& entities, const SDL_Event& event) {
        for (auto& entity : entities) {
            if (entity->hasComponent<PlayerTag>() && entity->hasComponent<Velocity>()) {
                auto&[direction, speed] = entity->getComponent<Velocity>();
                if (event.type == SDL_EVENT_KEY_DOWN) {
                    switch (event.key.key) {
                        case SDLK_W:
                            direction.y = -1;
                            break;
                        case SDLK_S:
                            direction.y = 1;
                            break;
                        case SDLK_D:
                            direction.x = 1;
                            break;
                        case SDLK_A:
                            direction.x = -1;
                            break;
                        case SDLK_F:
                            direction.x = 3;
                            direction.y = -1;
                            break;
                        default:
                            break;
                    }
                }

                if (event.type == SDL_EVENT_KEY_UP) {
                    switch (event.key.key) {
                        case SDLK_W:
                        case SDLK_S:
                            direction.y = 0;
                            break;
                        case SDLK_D:
                        case SDLK_A:
                            direction.x = 0;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
};

#endif //INC_8051PROJECT_KEYBOARDINPUTSYSTEM_H