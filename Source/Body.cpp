#include "Body.h"
#include "World.h"
#include <algorithm> // for std::clamp

Body::Body(Vector2 position, float density, float mass, float restitution, float area, bool isStatic, float radius, float width, float height, BodyType bodyType)
    : position(position), linearVelocity(0.0f, 0.0f), rotation(0.0f), rotationalVelocity(0.0f),
      density(density), mass(mass), restitution(restitution), area(area), isStatic(isStatic),
      radius(radius), width(width), height(height), bodyType(bodyType)
{
    if (bodyType == Circle) {
        // For circle, no need for width and height; just use radius.
        vertices.clear();  // Ensure no box vertices are present
    } else if (bodyType == Box) {
        this->vertices = CreateBoxVertices(width, height); // For box, create vertices based on width/height
    }
}

std::vector<Vector2> Body::CreateBoxVertices(float width, float height) {
    float left = -width / 2.0f;
    float right = left + width;
    float bottom = -height / 2.0f;
    float top = bottom + height;

    std::vector<Vector2> vertices(4);
    vertices[0] = Vector2(left, top);
    vertices[1] = Vector2(right, top);
    vertices[2] = Vector2(right, bottom);
    vertices[3] = Vector2(left, bottom);
    return vertices;
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
    restitution = std::clamp(restitution, 0.0f, 1.0f);

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
    restitution = std::clamp(restitution, 0.0f, 1.0f);

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

void Body::Rotate(float angle)
{
    this->rotation += angle;
    this->transformUpdateRequired = true;
    if (bodyType == BodyType::Box) {
        float cosAngle = cosf(rotation);
        float sinAngle = sinf(rotation);

        for (auto& vertex : vertices) {
            float x = vertex.GetX();
            float y = vertex.GetY();
            vertex.SetX(cosAngle * x - sinAngle * y);
            vertex.SetY(sinAngle * x + cosAngle * y);
        }
    }
}
