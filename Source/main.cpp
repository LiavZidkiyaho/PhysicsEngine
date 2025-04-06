#include <../Lib/glew-2.1.0/include/GL/glew.h>
#include <../Lib/glfw-3.4.bin.WIN64/include/GLFW/glfw3.h>
#include "Vector2.h"
#include "Body.h"
#include "Collisions.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

GLFWwindow* window = nullptr;
std::vector<Body*> bodies; // Stores both circles and boxes
std::vector<Vector2> randomColors;
int selectedBodyIndex = 0;
bool tabPressedLastFrame = false;

bool Init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    window = glfwCreateWindow(1920, 1080, "Vector Visualization", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return false;
    }

    std::srand(static_cast<unsigned>(std::time(0)));
    return true;
}

void CreateCircle(float radius, Vector2 position, float density, bool isStatic, float restitution) {
    Body* circle = nullptr;
    std::string errorMsg;
    Body bodyInstance;

    if (bodyInstance.CreateCircle(radius, position, density, isStatic, restitution, circle, errorMsg)) {
        bodies.push_back(circle);
        randomColors.emplace_back(
            (std::rand() % 256) / 255.0f,
            (std::rand() % 256) / 255.0f
        );
    } else {
        std::cerr << "Failed to create circle body: " << errorMsg << "\n";
    }
}

void CreateBox(float width, float height, Vector2 position, float density, bool isStatic, float restitution) {
    Body* box = nullptr;
    std::string errorMsg;
    Body bodyInstance;

    if (bodyInstance.CreateBox(width, height, position, density, isStatic, restitution, box, errorMsg)) {
        bodies.push_back(box);
        randomColors.emplace_back(
            (std::rand() % 256) / 255.0f,
            (std::rand() % 256) / 255.0f
        );
    } else {
        std::cerr << "Failed to create box body: " << errorMsg << "\n";
    }
}

void GenerateCircles(int count = 10) {
    for (int i = 0; i < count; ++i) {
        float radius = 0.2; // Random radius between 0.1 and 0.6
        Vector2 position(
            (std::rand() % 400) / 100.0f - 2.0f, // Random position between -2.0 and 2.0 on X-axis
            (std::rand() % 400) / 100.0f - 2.0f  // Random position between -2.0 and 2.0 on Y-axis
        );
        float density = 2.0f;
        bool isStatic = false;
        float restitution = 0.6f;
        CreateCircle(radius, position, density, isStatic, restitution);
    }
}

void GenerateBoxes(int count = 10) {
    for (int i = 0; i < count; ++i) {
        float width = 0.2;  // Random width between 0.2 and 0.7
        float height = 0.2; // Random height between 0.2 and 0.7
        Vector2 position(
            (std::rand() % 400) / 100.0f - 2.0f, // Random position between -2.0 and 2.0 on X-axis
            (std::rand() % 400) / 100.0f - 2.0f  // Random position between -2.0 and 2.0 on Y-axis
        );
        float density = 2.0f;
        bool isStatic = false;
        float restitution = 0.6f;
        CreateBox(width, height, position, density, isStatic, restitution);
    }
}

void DrawCircle(const Body* body) {
    if (!body || body->bodyType != BodyType::Circle) return;

    float radius = body->radius;
    Vector2 pos = body->position;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float theta = i * 3.14159f / 180.0f;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(pos.GetX() + x, pos.GetY() + y);
    }
    glEnd();
}

void DrawBox(const Body* body) {
    if (!body || body->bodyType != BodyType::Box) return;

    Vector2 position = body->position;
    float width = body->width;
    float height = body->height;

    std::vector<Vector2> rotatedVertices = body->vertices;

    glBegin(GL_QUADS);
    for (const auto& vertex : rotatedVertices) {
        glVertex2f(position.GetX() + vertex.GetX(), position.GetY() + vertex.GetY());
    }
    glEnd();
}

void ResolveCollisions() {
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            Vector2 normal;
            float depth;

            if (Collisions::IntersectCircles(
                bodies[i]->position, bodies[i]->radius,
                bodies[j]->position, bodies[j]->radius,
                normal, depth)) {

                bool aStatic = bodies[i]->isStatic;
                bool bStatic = bodies[j]->isStatic;

                if (!aStatic && !bStatic) {
                    bodies[i]->Move(-normal * (depth / 2.0f));
                    bodies[j]->Move(normal * (depth / 2.0f));
                } else if (!aStatic && bStatic) {
                    bodies[i]->Move(-normal * depth);
                } else if (aStatic && !bStatic) {
                    bodies[j]->Move(normal * depth);
                }

                // Optional: draw red line to indicate collision
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(bodies[i]->position.GetX(), bodies[i]->position.GetY());
                glVertex2f(bodies[j]->position.GetX(), bodies[j]->position.GetY());
                glEnd();
            }
        }
    }
}

void ResolveRotation()
{
    for (size_t i = 0; i < bodies.size(); ++i) {
        Body * body = bodies[i];
        const float pi = 3.14159f;
        body->Rotate(pi / 2.0f);
    }
}

void ProcessInput() {
    if (bodies.empty()) return;

    Body* selected = bodies[selectedBodyIndex];

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        selected->position += Vector2(-0.01f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        selected->position += Vector2(0.01f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        selected->position += Vector2(0.0f, 0.01f);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        selected->position += Vector2(0.0f, -0.01f);

    bool tabPressedNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;
    if (tabPressedNow && !tabPressedLastFrame)
        selectedBodyIndex = (selectedBodyIndex + 1) % bodies.size();
    tabPressedLastFrame = tabPressedNow;
}

void Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = static_cast<float>(width) / height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect >= 1.0f)
        glOrtho(-2.0f * aspect, 2.0f * aspect, -2.0f, 2.0f, -1.0f, 1.0f);
    else
        glOrtho(-2.0f, 2.0f, -2.0f / aspect, 2.0f / aspect, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (size_t i = 0; i < bodies.size(); ++i) {
        const Body* body = bodies[i];
        glColor3f(randomColors[i].GetX(), randomColors[i].GetY(), 1.0f); // Set random color
        if (body->bodyType == BodyType::Circle)
            DrawCircle(body);
        else if (body->bodyType == BodyType::Box)
            DrawBox(body);
    }

    glfwSwapBuffers(window);
}

int main()
{
    if (!Init()) return -1;

    GenerateCircles();
    GenerateBoxes();

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput();
        ResolveCollisions();
        ResolveRotation();
        Render();

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
