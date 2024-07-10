#ifndef LINE_H
#define LINE_H

#include "graphObj.h"

#include <vector>
#include <iostream>
#include <cmath>

class Line : public GraphObj {

public:
    Line(const int pXCoord, const int pYCoord, const int pEndX, const int pEndY);
    std::vector<int> getEndPoint() const;
    double length() const;
    virtual double area() const;
    virtual void draw() const;

private:
    int endX;
    int endY;
};

#endif
