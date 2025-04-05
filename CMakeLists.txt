cmake_minimum_required(VERSION 3.30)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add include directories
include_directories(Include)

# Add source files
add_executable(PhysicsEngine
        Source/main.cpp
        Source/Vector2.cpp
)