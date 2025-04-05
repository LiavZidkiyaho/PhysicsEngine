#ifndef BODY_H
#define BODY_H
#include "Vector2.h"

enum BodyType {
    Circle = 0,
    Box = 1
};

class Body
{
private:
    //fields
    Vector2 linearVelocity;
    float rotation;
    float rotationalVelocity;

    //constructor
    Body(Vector2 position, float density, float mass, float restitution, float area, bool isStatic, float radius, float width, float height, BodyType bodyType);

public:
    //constructor
    Body() = default;
    //fields
    Vector2 position;

    float density;
    float mass;
    float restitution;
    float area;

     bool isStatic;

    float radius;
    float width;
    float height;

    BodyType bodyType;

    bool CreateCircle(float radius, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg);
    bool CreateBox(float width, float height, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg);
};


#endif //BODY_H
