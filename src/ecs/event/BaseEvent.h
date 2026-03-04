//
// Created by Iris Chow on 2026-03-04.
//

#ifndef INC_8051TUTORIAL_BASEEVENT_H
#define INC_8051TUTORIAL_BASEEVENT_H

class Entity;

enum class EventType {
    Collision,
    PlayerAction,
};

enum class CollisionState {
    Enter,
    Stay,
    Exit,
};

enum class PlayerAction {
    Attack,
    Interact,
    Use,
    Jump,
};

struct BaseEvent {
    EventType type{};
    virtual ~BaseEvent() = default; // In C++ always make the destructor virtual from a class you are deriving from
};

struct CollisionEvent : BaseEvent {
    Entity* entityA = nullptr;
    Entity* entityB = nullptr;
    CollisionState state{};
    CollisionEvent(Entity* entityA, Entity* entityB, const CollisionState state) : entityA(entityA), entityB(entityB), state(state) {
        type = EventType::Collision;
    }
};

struct PlayerActionEvent : BaseEvent {
    Entity* player = nullptr;
    PlayerAction action{};
    PlayerActionEvent(Entity* player, const PlayerAction action) : player(player), action(action) {
        type = EventType::PlayerAction;
    }
};

#endif //INC_8051TUTORIAL_BASEEVENT_H