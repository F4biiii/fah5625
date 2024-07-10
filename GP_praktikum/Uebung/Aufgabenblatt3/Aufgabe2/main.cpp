#include "line.h"
#include "rectangle.h"

#include <iostream>

int main() {

    Line l1(8, 9, 14, 89);
    l1.draw();
    std::cout << "Area: " << l1.area() << std::endl;

    Rectangle rec1(5, 5, 5, 5);
    rec1.draw();
    std::cout << "Area: " << rec1.area() << std::endl;

    return 0;
}