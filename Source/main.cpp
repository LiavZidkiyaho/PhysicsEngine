#include <../Lib/glew-2.1.0/include/GL/glew.h>
#include <../Lib/glfw-3.4.bin.WIN64/include/GLFW/glfw3.h>
#include "Vector2.h"
#include "Body.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void DrawVector(const Vector2& v, float originX, float originY) {
    glBegin(GL_LINES);
    glVertex2f(originX, originY);
    glVertex2f(originX + v.GetX(), originY + v.GetY());
    glEnd();
}

void DrawCircle(const Body* body) {
    if (body == nullptr || body->bodyType != BodyType::Circle) return;

    float radius = body->radius;
    Vector2 position = body->position;

    glBegin(GL_POLYGON); // Filled circle
    for (int i = 0; i < 360; ++i) {
        float theta = i * 3.14159f / 180.0f;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(position.GetX() + x, position.GetY() + y);
    }
    glEnd();
}

void DrawBox(const Body* body) {
    if (body == nullptr || body->bodyType != BodyType::Box) return;

    float width = body->width;
    float height = body->height;
    Vector2 position = body->position;

    glBegin(GL_LINE_LOOP);
    glVertex2f(position.GetX() - width / 2, position.GetY() - height / 2);
    glVertex2f(position.GetX() + width / 2, position.GetY() - height / 2);
    glVertex2f(position.GetX() + width / 2, position.GetY() + height / 2);
    glVertex2f(position.GetX() - width / 2, position.GetY() + height / 2);
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Vector Visualization", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Seed random number generator
    std::srand(std::time(0));

    // Create a vector of circles with random positions and random colors
    std::vector<Body*> circles;
    std::vector<Vector2> randomColors;

    for (int i = 0; i < 10; ++i) {
        float radius = 0.2f;
        Vector2 position((std::rand() % 400) / 100.0f - 2.0f, (std::rand() % 400) / 100.0f - 2.0f);  // Random position
        float density = 2.0f;
        bool isStatic = false;
        float restitution = 0.6f;
        std::string errorMsg;

        Body* circle = nullptr;
        if (circle == nullptr) {
            Body bodyInstance;
            if (bodyInstance.CreateCircle(radius, position, density, isStatic, restitution, circle, errorMsg)) {
                circles.push_back(circle);
                // Generate random colors for each circle
                randomColors.push_back(Vector2((std::rand() % 256) / 255.0f, (std::rand() % 256) / 255.0f));
            } else {
                std::cerr << "Failed to create circle body: " << errorMsg << std::endl;
            }
        }
    }

    // Variable to track which circle is selected
    int selectedCircleIndex = 0;

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Maintain aspect ratio
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = static_cast<float>(width) / height;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (aspectRatio >= 1.0f) {
            glOrtho(-2.0f * aspectRatio, 2.0f * aspectRatio, -2.0f, 2.0f, -1.0f, 1.0f);
        } else {
            glOrtho(-2.0f, 2.0f, -2.0f / aspectRatio, 2.0f / aspectRatio, -1.0f, 1.0f);
        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // === Move selected circle with arrow keys ===
        if (!circles.empty()) {
            Body* selected = circles[selectedCircleIndex];
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                selected->position = selected->position + Vector2(-0.01f, 0.0f);
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                selected->position = selected->position + Vector2(0.01f, 0.0f);
            }
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                selected->position = selected->position + Vector2(0.0f, 0.01f);
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                selected->position = selected->position + Vector2(0.0f, -0.01f);
            }
        }

        // Optional: Switch between circles using TAB key
        static bool tabPressedLastFrame = false;
        bool tabPressedNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

        if (tabPressedNow && !tabPressedLastFrame) {
            selectedCircleIndex = (selectedCircleIndex + 1) % circles.size();
        }
        tabPressedLastFrame = tabPressedNow;

        // === Draw circles with random colors ===
        for (size_t i = 0; i < circles.size(); ++i) {
            Body* circle = circles[i];
            Vector2 color = randomColors[i];

            // Set color
            glColor3f(color.GetX(), color.GetY(), 1.0f - color.GetY());  // R, G, B variation

            // Draw circle
            DrawCircle(circle);
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    for (auto circle : circles) {
        delete circle;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
