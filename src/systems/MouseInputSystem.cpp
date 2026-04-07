//
// Created by Iris Chow on 2026-03-11.
//

#include <SDL3/SDL.h>
#include "MouseInputSystem.h"
#include "../ecs/core/World.h"
#include "../ecs/component/UI.h"

void MouseInputSystem::update(World& world, const SDL_Event& event) {

    if (
        event.type != SDL_EVENT_MOUSE_MOTION &&
        event.type != SDL_EVENT_MOUSE_BUTTON_DOWN &&
        event.type != SDL_EVENT_MOUSE_BUTTON_UP
        )
        return;

    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    for (auto& entity : world.getEntities()) {
        if (entity->hasComponent<Clickable>() && entity->hasComponent<Collider>()) {
            auto& clickable = entity->getComponent<Clickable>();
            auto& collider = entity->getComponent<Collider>();

            if (!collider.enabled) continue;

            const bool inside = (mouseX >= collider.offset.x && mouseX <= collider.offset.x + collider.width &&
                mouseY >= collider.offset.y && mouseY <= collider.offset.y + collider.height);

            // Hover
            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                if (!inside && clickable.pressed) {

                    // Cancel event
                    world.getEventManager().emit(MouseInteractionEvent{ entity.get(), MouseInteractionState::CANCEL});
                }
            }

            // Pressed
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (inside) {
                        clickable.pressed = true;

                        // Pressed event
                        world.getEventManager().emit(MouseInteractionEvent{ entity.get(), MouseInteractionState::PRESSED });
                    }
                }
            }

            // Released
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (inside) {
                        clickable.pressed = false;

                        // Released event
                        world.getEventManager().emit(MouseInteractionEvent{ entity.get(), MouseInteractionState::RELEASED });
                    }
                }
            }
        }
    }
}