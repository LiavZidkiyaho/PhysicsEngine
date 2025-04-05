#include "Vector2.h"

// Constructors
Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

// Operators
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

Vector2 Vector2::operator+=(const Vector2& other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}


// Methods
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

// Getters
float Vector2::GetX() const {
    return x;
}

float Vector2::GetY() const {
    return y;
}

// Setters
void Vector2::SetX(float x) {
    this->x = x;
}

void Vector2::SetY(float y) {
    this->y = y;
}

// Clamp function
float Vector2::Clamp(float value, float min, float max) {
    if (min == max) return min;
    if (min > max) throw std::out_of_range("Min is greater than max");
    if (value < min) return min;
    if (value > max) return max;
    return value;
}