#include <iostream>
#include "bruch2.h"

int main()
{
    Bruch b1(1, -2);
    Bruch b2(1, 4);

    b1 += b2;
    std::cout << b1 << '\n';

    Bruch b3(4, 3);
    Bruch b4 = b1 + b3;
    std::cout << b4 << '\n';
}
