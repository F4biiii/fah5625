#include "line.h"

#include <iostream>
#include <cmath>

Line::Line(const int pXCoord, const int pYCoord, const int pEndX, const int pEndY) : GraphObj(pXCoord, pXCoord) {
    endX = pEndX;
    endY = pEndY;
}

std::vector<int> Line::getEndPoint() const {
    return {endX, endY};
}

double Line::length() const {
    int startX = getEndPoint()[0];
    int startY = getEndPoint()[1];

    return sqrt((endX-startX) * (endX-startX) + (endY-startY) * (endY-startY));
}

double Line::area() const {
    return 0;
}

void Line::draw() const {
    std::cout << "Drawing line..." << std::endl;
}
