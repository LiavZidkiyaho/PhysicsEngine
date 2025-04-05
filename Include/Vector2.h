#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>

class Vector2
{
private:
    float x;
    float y;

public:
    // Constructors
    Vector2();
    Vector2(float x, float y);

    // Operators
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2 operator+=(const Vector2& other);

    // Methods
    static float Length(const Vector2& v);
    static float Distance(const Vector2& a, const Vector2& b);
    static float Dot(const Vector2& a, const Vector2& b);
    static float Cross(const Vector2& a, const Vector2& b);
    Vector2 Normalize() const;

    // Getters
    float GetX() const;
    float GetY() const;

    // Setters
    void SetX(float x);
    void SetY(float y);

    static float Clamp(float value, float min, float max);
};

#endif //VECTOR2_H