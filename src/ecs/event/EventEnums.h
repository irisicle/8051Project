//
// Created by Iris Chow on 2026-04-06.
//

#ifndef INC_8051PROJECT_EVENTENUMS_H
#define INC_8051PROJECT_EVENTENUMS_H

enum class EventType {
    COLLISION,
    PLAYER_ACTION,
    MOUSE_INTERACTION
};

enum class CollisionState {
    ENTER,
    STAY,
    EXIT
};

enum class MouseInteractionState {
    PRESSED,
    RELEASED,
    CANCEL
};

#endif //INC_8051PROJECT_EVENTENUMS_H