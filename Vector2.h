#pragma once

namespace Tmpl8
{
    class Vector2 {
    public:
        float x, y;

        // Constructors
        Vector2();
        Vector2(float x, float y);

        // Basic operations
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;
        void operator+=(const Vector2& other);
        void operator-=(const Vector2& other);
        void operator*=(float scalar);
        void operator/=(float scalar);
        bool operator==(const Vector2& other) const;
        bool operator!=(const Vector2& other) const;

        // Distance
        float distance(const Vector2& other) const;

        // Normalization
        void normalize();

        // Rotation
        void rotate(float angle);

        // Length
        float length() const;
    };
}

