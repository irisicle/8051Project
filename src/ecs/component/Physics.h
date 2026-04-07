//
// Created by Iris Chow on 2026-03-30.
//

#ifndef INC_8051PROJECT_PHYSIC_H
#define INC_8051PROJECT_PHYSIC_H

#include <string>
#include "../core/Component.h"
#include "../../utils/Vector2D.h"

enum class CollisionLayer {
    NONE,
    PLAYER,
    ANIMAL,
    ITEM,
    OBJECT
};

struct Transform : Component {
    Vector2D position{};
    float rotation{0.0f};
    float scale{1.0f};
    Vector2D oldPosition{};

    Transform() = default;

    explicit Transform(const Vector2D position, const float rotation = 0.0f, const float scale = 1.0f) : position(position), rotation(rotation), scale(scale) {}
};

// Direction and speed
struct Velocity : Component {
    Vector2D direction{};
    float speed{0.0f};

    Velocity() = default;

    Velocity(const Vector2D direction, const float speed) : direction(direction), speed(speed) {}
};

struct Collider : Component {
    std::string tag{};
    Vector2D offset{};
    float width{0.0f};
    float height{0.0f};
    bool enabled{true};
    CollisionLayer layer{CollisionLayer::NONE};

    Collider() = default;

    Collider(std::string& tag, const Vector2D offset, const float width, const float height, const CollisionLayer layer = CollisionLayer::NONE)
        : tag(std::move(tag)), offset(offset), width(width), height(height), layer(layer) {}

};

#endif //INC_8051PROJECT_PHYSIC_H