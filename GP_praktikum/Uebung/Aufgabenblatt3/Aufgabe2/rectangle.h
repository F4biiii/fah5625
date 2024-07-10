#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "graphObj.h"

class Rectangle : public GraphObj {

private:
    int height;
    int width;

public:
    Rectangle(const int pXCoord, const int pYCoord, const int pHeight, const int pWidth);
    int getHeight() const;
    int getWidth() const;
    virtual double area() const override;
    virtual void draw() const override;
};

#endif