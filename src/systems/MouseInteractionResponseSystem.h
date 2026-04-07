//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_MOUSEINTERACTIONRESPONSESYSTEM_H
#define INC_8051PROJECT_MOUSEINTERACTIONRESPONSESYSTEM_H

#include "../ecs/component/UI.h"
#include "../ecs/core/Entity.h"
#include "../ecs/event/BaseEvent.h"

class World;

class MouseInteractionResponseSystem {
public:
    static void handle(const MouseInteractionEvent& event, World& world) {
        if (!event.entity || !event.entity->hasComponent<Clickable>()) {
            return;
        }

        const auto& clickable = event.entity->getComponent<Clickable>();

        switch (event.state) {
            case MouseInteractionState::PRESSED:
                clickable.onPressed();
                break;
            case MouseInteractionState::RELEASED:
                clickable.onReleased();
                break;
            case MouseInteractionState::CANCEL:
                clickable.onCancel();
                break;
            default:
                break;
        }
    }
};

#endif //INC_8051PROJECT_MOUSEINTERACTIONRESPONSESYSTEM_H