#ifndef BODY_H
#define BODY_H
#include "Vector2.h"
#include <Vector>

enum BodyType { Circle, Box };

class Body {
public:
    Vector2 position;
    Vector2 linearVelocity;
    float rotation;
    float rotationalVelocity;
    float density;
    float mass;
    float restitution;
    float area;
    bool isStatic;
    float radius;
    float width, height;
    BodyType bodyType;
    std::vector<Vector2> vertices;
    bool transformUpdateRequired = false;

    // Constructor with default parameters
    Body(Vector2 position = Vector2(0.0f, 0.0f), float density = 1.0f, float mass = 1.0f,
         float restitution = 0.5f, float area = 1.0f, bool isStatic = false, float radius = 0.5f,
         float width = 1.0f, float height = 1.0f, BodyType bodyType = BodyType::Circle);

    std::vector<Vector2> CreateBoxVertices(float width, float height);
    void Move(Vector2 amount);
    void MoveTo(Vector2 position);
    void Rotate(float angle);
    static bool CreateCircle(float radius, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg);
    static bool CreateBox(float width, float height, Vector2 position, float density, bool isStatic, float restitution, Body*& body, std::string& errorMsg);
};


#endif //BODY_H
