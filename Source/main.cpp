#include <../Lib/glew-2.1.0/include/GL/glew.h>
#include <../Lib/glfw-3.4.bin.WIN64/include/GLFW/glfw3.h>
#include "Vector2.h"
#include <iostream>

void DrawVector(const Vector2& v, float originX, float originY) {
    glBegin(GL_LINES);
    glVertex2f(originX, originY);
    glVertex2f(originX + v.GetX(), originY + v.GetY());
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vector Visualization", NULL, NULL);
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
    Vector2 v3(-1.0f, -0.5f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw vectors
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        DrawVector(v1, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        DrawVector(v2, 0.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); // Blue color
        DrawVector(v3, 0.0f, 0.0f);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}