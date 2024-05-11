#include "route.h"
#include <algorithm>


// constructor

Route::Route(const float pHeight, float(*pDist)(const float x1, const float y1, const float x2, const float y2, const float h))
{
    destinations = new std::vector<std::pair<float, float>>();  // allocate memmory 
    height = pHeight;
    dist = pDist;
}

// destructor

Route::~Route() 
{
    delete destinations;                                        // free memmory    
}

// methods

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
    float result = 0.0;                                                          // return variable, initially 0                                                                                         
    float height = Route::getHeight();                                           // get height                                
    std::vector<std::pair<float,float>> dests = Route::getDestinations();        // get list of destinations
    std::pair<float,float> start;                                                                         
    std::pair<float,float> end;                                                                                  
    if (!dests.empty()) {                                                        // if list of destinations is not empty               
        for(size_t i = 0; i < dests.size()-1; i++) {                                    // iterate through all destinations (not the last one as it will be used with i+1)                                                                     
            start = dests[i];                                                    
            end = dests[i + 1];
            result += dist(start.first, start.second, end.first, end.second, height);   // add length of vector between start and end to result
        }
        result += dist(0.0, 0.0, dests[0].first, dests[0].second, height);                              // add distance from 0.0, 0.0 to first destination manually
        result += dist(dests[dests.size()-1].first, dests[dests.size()-1].second, 0.0, 0.0, height);    // add distance from last destination to 0.0, 0.0 manually
    }
    return result;                                                               // return result
}


void Route::shortestRoute()
{
    std::sort(destinations->begin(), destinations->end());                          // sort destination to get all permutations
    std::vector<std::pair<float,float>> shortestRoute = *destinations;              // safe first (sorted) permutation as shortest route
    float shortestDistance = distance();                                            // safe first distance as shortest distance           
    while (next_permutation(destinations->begin(), destinations->end()))            // iterate through all permutations of distance 
    { 
        if (distance() < shortestDistance)                                              // if distance of current permutation is shorter than the (so far found) shortest distance          
        {
            shortestRoute = *destinations;                                                  // safe current permutation as shortest (so far found) route          
            shortestDistance = distance();                                                  // safe distance of current permutation as shortest (so far found) distance  
        }
    }
    *destinations = shortestRoute;                                                  // as all permutations have been checked, apply shortest found route to destinations 
}