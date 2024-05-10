#ifndef ROUTE_H
#define ROUTE_H

#include "ufo.h"

#include <vector>

class Route 
{
private:
    std::vector<std::pair<float,float>>* destinations;
    float height;
    float(*dist)(const float x1, const float y1, const float x2, const float y2, const float h);
public:
    Route(const float pHeight, float(*dist)(const float x1, const float y1, const float x2, const float y2, const float h));
    ~Route();
    void add(const float destX, const float destY);
    const std::vector<std::pair<float,float>>& getDestinations() const;
    float getHeight() const;
    void setHeight(const float pHeight);
    void setDist(float(*pDist)(const float x1, const float y1, const float x2, const float y2, const float h));
    float distance() const;
    void shortestRoute();

};

#endif