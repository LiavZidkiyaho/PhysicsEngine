#include <../Lib/glew-2.1.0/include/GL/glew.h>
#include <../Lib/glfw-3.4.bin.WIN64/include/GLFW/glfw3.h>
#include "Vector2.h"
#include "Body.h"
#include <iostream>

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

    glBegin(GL_LINE_LOOP);
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

    // Define vectors
    Vector2 v1(0.5f, 0.75f);
    Vector2 v2(1.0f, 0.5f);
    Vector2 v3(1.50f, 0.25f);

    // Print vector info
    std::cout << "v1 Length: " << Vector2::Length(v1) << std::endl;
    std::cout << "v2 Length: " << Vector2::Length(v2) << std::endl;
    std::cout << "v3 Length: " << Vector2::Length(v3) << std::endl;

    std::cout << "Distance between v1 and v2: " << Vector2::Distance(v1, v2) << std::endl;
    std::cout << "Distance between v2 and v3: " << Vector2::Distance(v2, v3) << std::endl;
    std::cout << "Distance between v1 and v3: " << Vector2::Distance(v1, v3) << std::endl;

    std::cout << "Dot product of v1 and v2: " << Vector2::Dot(v1, v2) << std::endl;
    std::cout << "Dot product of v2 and v3: " << Vector2::Dot(v2, v3) << std::endl;
    std::cout << "Dot product of v1 and v3: " << Vector2::Dot(v1, v3) << std::endl;

    std::cout << "Cross product of v1 and v2: " << Vector2::Cross(v1, v2) << std::endl;
    std::cout << "Cross product of v2 and v3: " << Vector2::Cross(v2, v3) << std::endl;
    std::cout << "Cross product of v1 and v3: " << Vector2::Cross(v1, v3) << std::endl;

    Vector2 v1Normalized = v1.Normalize();
    Vector2 v2Normalized = v2.Normalize();
    Vector2 v3Normalized = v3.Normalize();
    std::cout << "Normalized v1: (" << v1Normalized.GetX() << ", " << v1Normalized.GetY() << ")" << std::endl;
    std::cout << "Normalized v2: (" << v2Normalized.GetX() << ", " << v2Normalized.GetY() << ")" << std::endl;
    std::cout << "Normalized v3: (" << v3Normalized.GetX() << ", " << v3Normalized.GetY() << ")" << std::endl;

    // Create Body objects
    Body* circleBody = nullptr;
    Body* boxBody = nullptr;
    std::string errorMsg;

    Body bodyInstance;

    // Create circle and box with proper values
    if (bodyInstance.CreateCircle(0.5f, Vector2(0.5f, 0.5f), 2.0f, false, 0.6f, circleBody, errorMsg)) {
        std::cout << "Circle body created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create circle body: " << errorMsg << std::endl;
    }

    if (bodyInstance.CreateBox(1.0f, 0.5f, Vector2(-1.0f, -1.0f), 1.5f, false, 0.4f, boxBody, errorMsg)) {
        std::cout << "Box body created successfully." << std::endl;
    } else {
        std::cerr << "Failed to create box body: " << errorMsg << std::endl;
    }

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

        // Draw vectors
        glColor3f(1.0f, 0.0f, 0.0f);
        DrawVector(v1, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        DrawVector(v2, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        DrawVector(v3, 0.0f, 0.0f);

        // Draw shapes
        glColor3f(1.0f, 1.0f, 1.0f);
        DrawCircle(circleBody);
        DrawBox(boxBody);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    delete circleBody;
    delete boxBody;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
