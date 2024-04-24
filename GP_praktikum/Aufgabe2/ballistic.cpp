#include "ballistic.h"

// constructor for Ballistic

Ballistic::Ballistic(const float pTakeOffAngle, const float pLandingAngle)
{
    if(pTakeOffAngle < 0.0 && pTakeOffAngle <= 90.0)
    {
        takeOffAngle = pTakeOffAngle;
    } else {
        takeOffAngle = 45.0;
    }
    
    if(pLandingAngle < 0.0 && pLandingAngle <= 90.0)
    {
        landingAngle = pLandingAngle;
    } else {
        landingAngle = 45.0;
    }
}

// destructor (does nothing)

Ballistic::~Ballistic() { }     

// methods

std::vector<float> firstWaypoint(const float x, const float y, const float height)
{

    return {0.0, 0.0};
}

std::vector<float> secondWaypoint(const float x, const float y, const float height) 
{

    return {0.0, 0.0}; 
}