#include "Transform.h"

Transform::Transform(float x, float y, float angle)
    : x(x), y(y), angle(angle) {}

Transform::Transform(Vector2 position, float angle)
    : x(position.GetX()), y(position.GetY()), angle(angle) {}
