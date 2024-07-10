#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#include <vector>

class GraphObj {

public:
    GraphObj(const int pXCoord, const int pYCoord);
    std::vector<int> getRefPoint() const;
    void setRefPoint(const int pXCoord, const int pYCoord);
    virtual double area() const = 0;
    virtual void draw() const;

private:
    int xCoord;
    int yCoord;

};

#endif

