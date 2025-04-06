#include "Collisions.h"

bool Collisions::IntersectCircles(const Vector2& centerA, float radiusA, const Vector2& centerB, float radiusB, Vector2& normal, float& depth)
{
    float distance = Vector2::Distance(centerA, centerB);
    float radiusSum = radiusA + radiusB;

    if (distance >= radiusSum)
    {
        return false;
    }
    normal = (centerB - centerA).Normalize();
    depth = radiusSum - distance;
    return true;
}