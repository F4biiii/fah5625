#include "ufo.h"


// constructor for Ufo

Ufo::Ufo(const std::string& pId) {    
    id = pId;
    Ufosim::setSpeedup(50);
    sim = new Ufosim();
}

// destructor for Ufo

Ufo::~Ufo() {                         
    delete sim;
}

// getters for Ufo

const std::string& Ufo::getId() const {
    return id;
}

std::vector<float> Ufo::getPosition() const {
    return { sim->getX(), sim->getY(), sim->getZ() };
}

float Ufo::getFtime() const {
    return sim->getFtime();
}

// methods

float Ufo::angle(const float x1, const float y1, const float x2, const float y2) {
    float V2X = x2-x1;      // calculate x of Vector 2
    float V2Y = y2-y1;      // calculate y of Vector 2

    float finalAngle = atan2(V2Y,V2X) * (180 / std::numbers::pi); // get angle between x-axis and vector, correct it from rad to deg

    finalAngle = 90 - finalAngle;       // correction: angle relative to y-axis (north)

    if(finalAngle < 0)                  // not allow angles below 0
        finalAngle += 360;

    if(x1 == x2 && y1 == y2)           // return 0.0 if identical
        finalAngle = 0.0;

    return finalAngle;
}

