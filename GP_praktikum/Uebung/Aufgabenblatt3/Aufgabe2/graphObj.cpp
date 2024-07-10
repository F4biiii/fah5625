#include "graphObj.h"

GraphObj::GraphObj(const int pXCoord, const int pYCoord) {
    xCoord = pXCoord;
    yCoord = pYCoord;
}

std::vector<int> GraphObj::getRefPoint() const {
    return {xCoord, yCoord};
}

void GraphObj::setRefPoint(const int pXCoord, const int pYCoord) {
    xCoord = pXCoord;
    yCoord = pYCoord;
}

void GraphObj::draw() const {
    return;
}
