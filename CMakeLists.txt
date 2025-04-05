cmake_minimum_required(VERSION 3.30)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/Include)
include_directories(${CMAKE_SOURCE_DIR}/Lib/GL)
include_directories(${CMAKE_SOURCE_DIR}/Lib/GLFW)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/Source/*.cpp
        ${CMAKE_SOURCE_DIR}/Include/*.h
)

add_executable(PhysicsEngine ${SOURCE_FILES})

# Link full path to the .a or .lib files
target_link_libraries(PhysicsEngine
        ${CMAKE_SOURCE_DIR}/Lib/glew-2.1.0/lib/Release/x64/glew32.lib
        ${CMAKE_SOURCE_DIR}/Lib/glfw-3.4.bin.WIN64/lib-mingw-w64/libglfw3.a
        opengl32
)
