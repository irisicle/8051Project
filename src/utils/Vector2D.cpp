//
// Created by Iris Chow on 2026-01-28.
//
// Operator was working fine, accidentally printing b-value instead of a-value
// Fixed Mario so he is no longer cut in half
//

#include "Vector2D.h"

#include <valarray>

// Member operator function so that we could use the Vector2D that we want to change on the left hand side
Vector2D &Vector2D::operator += (const Vector2D &vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D &Vector2D::operator -= (const Vector2D &vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D &Vector2D::operator *= (const float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D &Vector2D::operator /= (const float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Vector2D Vector2D::operator + (const Vector2D &vector) const {
    return Vector2D{this->x + vector.x, this->y + vector.y};
}

Vector2D Vector2D::operator - (const Vector2D &vector) const {
    return Vector2D{this->x - vector.x, this->y - vector.y};
}

bool Vector2D::operator == (const Vector2D &vector) const {
    return x == vector.x && y == vector.y;
}

bool Vector2D::operator != (const Vector2D &vector) const {
    return x == vector.x && y == vector.y;
}

Vector2D Vector2D::operator - () const {
    return Vector2D{-this->x, -this->y};
}

// Member operator function so that we could use the Vector2D on the left hand side
Vector2D Vector2D::operator * (const float scalar) const {
    return Vector2D{this->x * scalar, this->y * scalar};
}

// Non-member operator function so that we could make use of putting the Vector2D on the right hand side
Vector2D operator * (const float scalar, const Vector2D &vector) {
    return Vector2D{vector.x * scalar, vector.y * scalar};
}

Vector2D operator / (const float scalar, const Vector2D &vector) {
    return Vector2D{vector.x / scalar, vector.y / scalar};
}

Vector2D &Vector2D::normalize() {
    // Pythagorean Theorem
    // For example, if the length was 4.4; x = x/4.4; y = y/4.4
    if (const float length = std::sqrt(x * x + y * y); length > 0) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}

