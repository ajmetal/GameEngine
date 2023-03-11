#pragma once

class Vector2 
{
public:
    float x;
    float y;
    Vector2();
    Vector2(float a, float b);
    void Normalize();
    Vector2 Normalized() const;
    float Magnitude() const;
    static float Dot(Vector2 lhs, Vector2 rhs);
    static Vector2 Cross(Vector2 lhs, Vector2 rhs);
    static Vector2 Vector2Zero();
    static Vector2 Vector2One();
    static float Distance(Vector2 lhs, Vector2 rhs);
    static Vector2 Lerp(Vector2 v1, Vector2 v2, float amount);

    Vector2 operator*(const float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }

    void operator*=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
    }

    Vector2 operator/(const float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }

    void operator/=(const float scalar)
    {
        x /= scalar;
        y /= scalar;
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    void operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    void operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
    }

};