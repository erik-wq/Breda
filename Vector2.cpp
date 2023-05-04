#include "Vector2.h"
#include <cmath>

namespace Tmpl8
{
    Vector2::Vector2() : x(0), y(0) {}
    Vector2::Vector2(float x, float y) : x(x), y(y) {}

    // Basic operations
    Vector2 Vector2::operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 Vector2::operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 Vector2::operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    void Vector2::operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
    }

    void Vector2::operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
    }

    void Vector2::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    void Vector2::operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
    }

    bool Vector2::operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other) const {
        return x != other.x || y != other.y;
    }

    // Distance
    float Vector2::distance(const Vector2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Normalization
    void Vector2::normalize() {
        float len = length();
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    // Rotation
    void Vector2::rotate(float angle) {
        float s = std::sin(angle);
        float c = std::cos(angle);
        float newX = x * c - y * s;
        float newY = x * s + y * c;
        x = newX;
        y = newY;
    }

    // Length
    float Vector2::length() const {
        return std::sqrt(x * x + y * y);
    }
}