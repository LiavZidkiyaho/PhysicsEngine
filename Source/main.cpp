#include <iostream>
#include "../Include/Vector2.h"

int main()
{
    Vector2 v1(3.0f, 4.0f);
    Vector2 v2(1.0f, 2.0f);
    Vector2 v3 = v1 + v2;
    std::cout << "v3: (" << v3.GetX() << ", " << v3.GetY() << ")" << std::endl;
    return 0;
}