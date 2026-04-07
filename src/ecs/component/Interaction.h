//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_INTERACTION_H
#define INC_8051PROJECT_INTERACTION_H

#include "../core/Component.h"

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Facing : Component {
    Direction direction{Direction::DOWN};

    Facing() = default;

    explicit Facing(const Direction direction) : direction(direction) {}
};

struct PlayerIntent : Component {
    float moveX{0.0f};
    float moveY{0.0f};

    bool usePressed{false};
};

#endif //INC_8051PROJECT_INTERACTION_H