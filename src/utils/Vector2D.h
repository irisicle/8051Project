//
// Created by Iris Chow on 2026-01-28.
//

#ifndef INC_8051PROJECT_VECTOR2D_H
#define INC_8051PROJECT_VECTOR2D_H

class Vector2D {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }
    Vector2D(const float x, const float y) : x(x), y(y) {}

    // Member operator function (*)
    // Vector2D has to be on the left, float on the right
    Vector2D operator*(float scalar) const;
    // Vector2D is on the right, and the float is on the left
    // friend makes it a non-member function
    friend Vector2D operator*(float scalar, const Vector2D& vector);
    // Member operator function (+=)
    // Vector that we want to return is on the left
    // Another vector is on the right
    Vector2D& operator+=(const Vector2D& vector);
    // Assignment 4
    Vector2D& operator-=(const Vector2D& vector);
    Vector2D operator+(const Vector2D& vector) const;
    Vector2D operator-(const Vector2D& vector) const;
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);
    Vector2D operator-() const;
    bool operator==(const Vector2D& vector) const;
    bool operator!=(const Vector2D& vector) const;

    Vector2D& normalize();

};

#endif //INC_8051PROJECT_VECTOR2D_H