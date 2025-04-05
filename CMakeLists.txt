cmake_minimum_required(VERSION 3.30)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(PhysicsEngine Source/main.cpp
        Include/Vector2.h
        Source/Vector2.cpp)
