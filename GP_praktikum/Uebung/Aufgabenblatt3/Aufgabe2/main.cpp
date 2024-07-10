#include "line.h"
#include "rectangle.h"

#include <iostream>

int main() {

    Line line(0, 0, 5, 5);
    Line line2(0, 0, -5, -5);
    Rectangle rect(0, 0, 10, 10);
    std::vector<GraphObj*> objs = { &line, &line2, &rect };
    for (auto fp: objs)
    {
        std::cout << "area: " << fp->area() << '\n' << "draw: ";
        fp->draw();
    }  
}