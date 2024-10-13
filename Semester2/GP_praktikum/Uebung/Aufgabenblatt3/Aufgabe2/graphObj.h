#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#include <vector>

class GraphObj 
{
private:
    int xCoord;
    int yCoord;

public:
    GraphObj(const int pXCoord, const int pYCoord);
    std::vector<int> getRefPoint() const;
    std::vector<int> setRefPoint(const int pXCoord, const int pYCoord);
    virtual double area() const = 0;
    virtual void draw() const;
};

#endif

