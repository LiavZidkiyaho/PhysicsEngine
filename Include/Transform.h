// `Include/Transform.h`
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2.h"
class Vector2;

class Transform {
public:
    float x, y, angle;
    Transform(float x = 0.0f, float y = 0.0f, float angle = 0.0f);
    Transform(Vector2 position, float angle = 0.0f);
};

#endif // TRANSFORM_H