# 0 "E:/PhysicsEngine/Source/World.cpp"
# 1 "E:\\PhysicsEngine\\cmake-build-debug//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "E:/PhysicsEngine/Source/World.cpp"
# 1 "E:/PhysicsEngine/Include/World.h" 1



class World
{
public:
    static float MinBodySize;
    static float MaxBodySize;

    static float MinDensity;
    static float MaxDensity;
};
# 2 "E:/PhysicsEngine/Source/World.cpp" 2

float World::MinBodySize = 0.01f * 0.01f;
float World::MaxBodySize = 64.0f * 64.0f;

float World::MinDensity = 0.5f;
float World::MaxDensity = 21.4f;
