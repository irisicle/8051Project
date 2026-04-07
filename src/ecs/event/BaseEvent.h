//
// Created by Iris Chow on 2026-03-04.
//

#ifndef INC_8051PROJECT_BASEEVENT_H
#define INC_8051PROJECT_BASEEVENT_H

#include "EventEnums.h"
#include "../../game/GameplayEnums.h"

class Entity;

struct BaseEvent {
    EventType type{};
    virtual ~BaseEvent() = default; // In C++ always make the destructor virtual from a class you are deriving from
};

struct CollisionEvent : BaseEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
    CollisionState state{};
    CollisionEvent(Entity* entityA, Entity* entityB, const CollisionState state) : entityA(entityA), entityB(entityB), state(state) {
        type = EventType::COLLISION;
    }
};

struct PlayerActionEvent : BaseEvent {
    Entity* player = nullptr;
    PlayerAction action{};
    int gridX{}, gridY{};
    PlayerActionEvent(Entity* player, const PlayerAction action, const int x, const int y) : player(player), action(action), gridX(x), gridY(y) {
        type = EventType::PLAYER_ACTION;
    }
};

struct MouseInteractionEvent : BaseEvent {
    Entity* entity = nullptr;
    MouseInteractionState state{};
    MouseInteractionEvent(Entity* entity, const MouseInteractionState state) : entity(entity), state(state) {
        type = EventType::MOUSE_INTERACTION;
    }
};

#endif //INC_8051PROJECT_BASEEVENT_H