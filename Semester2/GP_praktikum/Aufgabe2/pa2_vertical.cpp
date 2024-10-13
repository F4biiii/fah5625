#include "pa2_vertical.h"

// constructor

Vertical::Vertical(const std::string& pId) : Ufo(pId) { }

// destructor

Vertical::~Vertical() 
{                         

}

// methods

void Vertical::flyToDest(const float x, const float y, const float height, const int speed) const 
{
    sim->flyTo(sim->getX(), sim->getY(), height, speed, 0);     // fly upwards to height
    sim->flyTo(x, y, height, speed, 0);                         // fly to x y of destination
    sim->flyTo(x, y, 0.0, speed, 0);                            // fly down to height 0
    return;
}



