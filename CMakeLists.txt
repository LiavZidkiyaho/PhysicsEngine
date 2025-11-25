cmake_minimum_required(VERSION 3.10)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

# ---------------------------
# Include directories
# ---------------------------
include_directories(${CMAKE_SOURCE_DIR}/Include)

# GLAD (required)
file(GLOB GLAD_SRC ${CMAKE_SOURCE_DIR}/Source/glad.c)

# ---------------------------
# Source files
# ---------------------------
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/Source/*.cpp
        ${CMAKE_SOURCE_DIR}/Include/*.h
)

add_executable(PhysicsEngine ${SOURCE_FILES} ${GLAD_SRC})

# ---------------------------
# Find OpenGL
# ---------------------------
find_package(OpenGL REQUIRED)

# ---------------------------
# Find GLFW (system installed)
# Fedora: sudo dnf install glfw-devel
# Ubuntu: sudo apt install libglfw3-dev
# MacOS: brew install glfw
# ---------------------------
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# ---------------------------
# Link libraries
# ---------------------------
target_link_libraries(PhysicsEngine
        ${GLFW_LIBRARIES}
        OpenGL::GL
)
