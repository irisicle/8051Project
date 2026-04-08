//
// Created by Iris Chow on 2026-03-29.
//

#include "KeyboardInputSystem.h"

#include <iostream>
#include <ostream>

#include "../ecs/component/Interaction.h"
#include "../ecs/component/Inventory.h"
#include "../ecs/core/World.h"
#include "../ecs/component/Tag.h"

void KeyboardInputSystem::update(const std::vector<std::unique_ptr<Entity>> &entities, const SDL_Event &event) {
    for (auto &entity: entities) {
        if (!entity->hasComponent<PlayerTag>() || !entity->hasComponent<PlayerIntent>()) {
            continue;
        }

        auto& intent = entity->getComponent<PlayerIntent>();

        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_W:
                    intent.moveY = -1.0;
                    break;
                case SDLK_S:
                    intent.moveY = 1.0;
                    break;
                case SDLK_D:
                    intent.moveX = 1.0;
                    break;
                case SDLK_A:
                    intent.moveX = -1.0;
                    break;
                case SDLK_E:
                    intent.usePressed = true;
                    std::cout << "Player pressed E" << std::endl;
                    break;

                case SDLK_1:
                case SDLK_2:
                case SDLK_3:
                case SDLK_4:
                case SDLK_5:
                case SDLK_6:
                case SDLK_7:
                case SDLK_8:
                case SDLK_9:
                    if (entity->hasComponent<Inventory>()) {
                        auto& inventory = entity->getComponent<Inventory>();
                        inventory.selectedIndex = event.key.key - SDLK_1;
                        break;
                    }
                default:
                    break;
            }
        }

        if (event.type == SDL_EVENT_KEY_UP) {
            switch (event.key.key) {
                case SDLK_W:
                    if (intent.moveY < 0.0f) intent.moveY = 0.0f;
                    break;
                case SDLK_S:
                    if (intent.moveY > 0.0f) intent.moveY = 0.0f;
                    break;
                case SDLK_D:
                    if (intent.moveX > 0.0f) intent.moveX = 0.0f;
                    break;
                case SDLK_A:
                    if (intent.moveX < 0.0f) intent.moveX = 0.0f;
                    break;
                default:
                    break;
            }
        }
    }
}
