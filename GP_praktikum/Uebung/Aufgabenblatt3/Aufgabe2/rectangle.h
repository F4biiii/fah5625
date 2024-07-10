#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "graphObj.h"

#include <iostream>

class Rectangle : public GraphObj {

public:
    Rectangle(const int pXCoord, const int pYCoord, const int pHeight, const int pWidth);
    int getHeight() const;
    int getWidth() const;
    virtual double area() const;
    virtual void draw() const;

private:
    int height;
    int width;
};

#endif