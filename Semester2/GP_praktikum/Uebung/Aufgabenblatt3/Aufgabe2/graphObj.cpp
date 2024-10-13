#include "graphObj.h"

GraphObj::GraphObj(const int pXCoord, const int pYCoord) 
{
    xCoord = pXCoord;
    yCoord = pYCoord;
}

std::vector<int> GraphObj::getRefPoint() const 
{
    return {xCoord, yCoord};
}

std::vector<int> GraphObj::setRefPoint(const int pXCoord, const int pYCoord) 
{
    std::vector<int> old = {xCoord, yCoord};
    xCoord = pXCoord;
    yCoord = pYCoord;
    return old;
}

void GraphObj::draw() const 
{
    return;
}
