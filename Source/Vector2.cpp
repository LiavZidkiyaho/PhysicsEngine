// `Source/Vector2.cpp`
#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

float Vector2::Length(const Vector2& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float Vector2::Distance(const Vector2& a, const Vector2& b) {
    return Length(a - b);
}

float Vector2::Dot(const Vector2& a, const Vector2& b) {
    return a.x * b.x + a.y * b.y;
}

float Vector2::Cross(const Vector2& a, const Vector2& b) {
    return a.x * b.y - a.y * b.x;
}

Vector2 Vector2::Normalize() const {
    float length = Length(*this);
    return Vector2(x / length, y / length);
}

Vector2 Vector2::Transform(const Vector2& v, const::Transform& transform) {
    float cosAngle = std::cos(transform.angle);
    float sinAngle = std::sin(transform.angle);
    float newX = v.x * cosAngle - v.y * sinAngle + transform.x;
    float newY = v.x * sinAngle + v.y * cosAngle + transform.y;
    return Vector2(newX, newY);
}

float Vector2::GetX() const {
    return x;
}

float Vector2::GetY() const {
    return y;
}

void Vector2::SetX(float x) {
    this->x = x;
}

void Vector2::SetY(float y) {
    this->y = y;
}

float Vector2::Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}