#ifndef LINE_H
#define LINE_H

#include "graphObj.h"

#include <vector>

class Line : public GraphObj {

private:
    int endX;
    int endY;

public:
    Line(const int pXCoord, const int pYCoord, const int pEndX, const int pEndY);
    std::vector<int> getEndPoint() const;
    double length() const;
    virtual double area() const override;
    virtual void draw() const override;
};

#endif
