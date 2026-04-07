//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_UICOMPONENT_H
#define INC_8051PROJECT_UICOMPONENT_H

#include <functional>
#include <vector>
#include "../core/Component.h"

class Entity;

struct Clickable : Component {
    std::function<void()> onPressed{};
    std::function<void()> onReleased{};
    std::function<void()> onCancel{};

    bool pressed = false;
};

struct Parent : Component {
    Entity* parent = nullptr;

    explicit Parent(Entity* entity) : parent(entity) {}
};

struct Children : Component {
    std::vector<Entity*> children{};
};

#endif //INC_8051PROJECT_UICOMPONENT_H