//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_INPUT_H
#define INC_8051PROJECT_INPUT_H

#include "../core/Component.h"
#include "../../utils/Vector2D.h"

struct PlayerIntent : Component {
    Vector2D moveDirection{0.0f, 0.0f};
    bool useToolPressed{false};
    bool interactPressed{false};
};

#endif //INC_8051PROJECT_INPUT_H