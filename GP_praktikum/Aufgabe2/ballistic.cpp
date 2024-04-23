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