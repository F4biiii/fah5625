#include "vertical.h"

// constructor

Vertical::Vertical(const std::string& pId) : Ufo(pId) { }

// destructor

Vertical::~Vertical() { }

// methods

void Vertical::flyToDest(const float x, const float y, const float height, const int speed) const 
{
    sim->flyTo(sim->getX(), sim->getY(), height, speed, 0);     // fly upwards to height
    sim->flyTo(x, y, height, speed, 0);                         // fly to x y of destination
    sim->flyTo(x, y, 0.0, speed, 0);                            // fly down to height 0
    return;
}

float Vertical::distance(const float x1, const float y1, const float x2, const float y2, const float h)    
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)) + 2*h;                                                         // length of vector between start and end + 2*height
}



