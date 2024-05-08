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
    float result = 0;                                                               // return variable, initially 0                                                                                         
    float height = Route::getHeight();                                              // get height                                
    std::vector<std::pair<float,float>> destinations = Route::getDestinations();    // get list of destinations
    std::pair<float,float> start;                                                                                
    std::pair<float,float> end;                                                                                         
    if (!destinations.empty()) {                                                    // if list of destinations is not empty               
        for(int i = 0; i < destinations.size() - 1; i++) {                          // iterate through all destinations (not the last one as it will be used with i+1)
            start = destinations[i];                                                    
            end = destinations[i + 1];                                                  
            result += dist(start.first, start.second, end.first, end.second, height);   // add length of vector between start and end to result
        }
    }
    return result;                                                                  // return result
}


void Route::shortestRoute()
{

}