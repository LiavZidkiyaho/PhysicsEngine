#include <../Lib/glew-2.1.0/include/GL/glew.h>
#include <../Lib/glfw-3.4.bin.WIN64/include/GLFW/glfw3.h>
#include "Vector2.h"
#include "Body.h"
#include "Collisions.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

GLFWwindow* window = nullptr;
std::vector<Body*> circles;
std::vector<Vector2> randomColors;
int selectedCircleIndex = 0;
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

void CreateCircles(int count = 10) {
    for (int i = 0; i < count; ++i) {
        float radius = 0.2f;
        Vector2 position((std::rand() % 400) / 100.0f - 2.0f, (std::rand() % 400) / 100.0f - 2.0f);
        float density = 2.0f;
        bool isStatic = false;
        float restitution = 0.6f;
        std::string errorMsg;

        Body* circle = nullptr;
        Body bodyInstance;
        if (bodyInstance.CreateCircle(radius, position, density, isStatic, restitution, circle, errorMsg)) {
            circles.push_back(circle);
            randomColors.emplace_back(
                (std::rand() % 256) / 255.0f,
                (std::rand() % 256) / 255.0f
            );
        } else {
            std::cerr << "Failed to create circle body: " << errorMsg << "\n";
        }
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

void ProcessInput() {
    if (circles.empty()) return;

    Body* selected = circles[selectedCircleIndex];

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
        selectedCircleIndex = (selectedCircleIndex + 1) % circles.size();
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

    // Draw and resolve collisions
    for (size_t i = 0; i < circles.size(); ++i) {
        Vector2 color = randomColors[i];
        glColor3f(color.GetX(), color.GetY(), 1.0f - color.GetY());
        DrawCircle(circles[i]);
    }

    for (size_t i = 0; i < circles.size(); ++i) {
        for (size_t j = i + 1; j < circles.size(); ++j) {
            Vector2 normal;
            float depth;

            if (Collisions::IntersectCircles(
                circles[i]->position, circles[i]->radius,
                circles[j]->position, circles[j]->radius,
                normal, depth)) {

                bool aStatic = circles[i]->isStatic;
                bool bStatic = circles[j]->isStatic;

                if (!aStatic && !bStatic) {
                    circles[i]->Move(-normal * (depth / 2.0f));
                    circles[j]->Move(normal * (depth / 2.0f));
                } else if (!aStatic && bStatic) {
                    circles[i]->Move(-normal * depth);
                } else if (aStatic && !bStatic) {
                    circles[j]->Move(normal * depth);
                }

                // Optional: draw red line to indicate collision
                glColor3f(1.0f, 0.0f, 0.0f);
                glBegin(GL_LINES);
                glVertex2f(circles[i]->position.GetX(), circles[i]->position.GetY());
                glVertex2f(circles[j]->position.GetX(), circles[j]->position.GetY());
                glEnd();
            }
        }
    }

    glfwSwapBuffers(window);
}



void Cleanup() {
    for (auto c : circles) delete c;
    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    if (!Init()) return -1;

    CreateCircles();

    while (!glfwWindowShouldClose(window)) {
        ProcessInput();
        Render();
        glfwPollEvents();
    }

    Cleanup();
    return 0;
}