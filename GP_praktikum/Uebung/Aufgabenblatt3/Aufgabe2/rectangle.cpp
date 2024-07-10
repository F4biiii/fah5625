#include "rectangle.h"

Rectangle::Rectangle(const int pXCoord, const int pYCoord, const int pHeight, const int pWidth) : GraphObj(pXCoord, pYCoord) {
    height = pHeight;
    width = pWidth;
}

int Rectangle::getHeight() const {
    return height;
}

int Rectangle::getWidth() const {
    return width;
}

double Rectangle::area() const {
    return width * height;
}

void Rectangle::draw() const {
    std::cout << "Drawing rectangle..." << std::endl;
}
