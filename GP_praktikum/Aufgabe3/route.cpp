#include "route.h"

Route::Route(const float pHeight, float(*pDist)(const float x1, const float y1, const float x2, const float y2, const float h))
{
    height = pHeight;
    dist = pDist;
}

Route::~Route() { }

void Route::add(const float destX, const float destY)
{
    destinations->push_back({destX, destY});
}

const std::vector<std::pair<float,float>>& Route::getDestinations() const
{
    return *destinations;
}

float Route::getHeight() const
{
    return height;
}

void Route::setHeight(const float pHeight)
{
    height = pHeight;
}

void Route::setDist(float(*pDist)(const float x1, const float y1, const float x2, const float y2, const float h))
{
    dist = pDist;
}

float Route::distance() const
{
    
}

void Route::shortestRoute()
{

}