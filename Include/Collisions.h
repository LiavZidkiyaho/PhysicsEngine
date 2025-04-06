#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "Vector2.h"

class Collisions
{
  public:
    static bool IntersectCircles(const Vector2& centerA, float radiusA, const Vector2& centerB, float radiusB, Vector2& normal, float& depth);
};


#endif //COLLISIONS_H
