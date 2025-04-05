#include "Body.h"
#include "World.h"

Body::Body(Vector2 position, float density, float mass, float restitution, float area, bool isStatic, float radius, float width, float height, BodyType bodyType)
{
    this->position = position;
    this->linearVelocity = Vector2(0.0f, 0.0f);
    this->rotation = 0.0f;
    this->rotationalVelocity = 0.0f;

    this->density = density;
    this->mass = mass;
    this->restitution = restitution;
    this->area = area;

    this->isStatic = isStatic;

    this->radius = radius;
    this->width = width;
    this->height = height;

    this->bodyType = bodyType;
}


bool Body::CreateCircle(float radius, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg)
{
    body = nullptr;
    errorMsg = "";
    float area = 3.14f * radius * radius;
    if (area < World::MinBodySize || area > World::MaxBodySize)
    {
        errorMsg = "Area is out of bounds";
        return false;
    }
    if (density < World::MinDensity || density > World::MaxDensity)
    {
        errorMsg = "Density is out of bounds";
        return false;
    }
    restitution = Vector2::Clamp(restitution, 0.0f, 1.0f);

    body = new Body(position, density, density * area, restitution, area, isStatic, radius, 0.0f, 0.0f, BodyType::Circle);
    return true;
}

bool Body::CreateBox(float width, float height, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg)
{
    body = nullptr;
    errorMsg = "";
    float area = width * height;
    if (area < World::MinBodySize || area > World::MaxBodySize)
    {
        errorMsg = "Area is out of bounds";
        return false;
    }
    if (density < World::MinDensity || density > World::MaxDensity)
    {
        errorMsg = "Density is out of bounds";
        return false;
    }
    restitution = Vector2::Clamp(restitution, 0.0f, 1.0f);

    body = new Body(position, density, density * area, restitution, area, isStatic, 0.0f, width, height, BodyType::Box);
    return true;
}

void Body::Move(Vector2 amount)
{
    this->position += amount;
}

void Body::MoveTo(Vector2 position)
{
    this->position = position;
}
