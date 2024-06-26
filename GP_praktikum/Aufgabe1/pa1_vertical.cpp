#include "pa1_vertical.h"
#include <cmath>
#include <math.h>

const std::string Vertical::type = "vertical";

Vertical::Vertical(const std::string& pId) {    // constructor
    id = pId;
    Ufosim::setSpeedup(4);
    sim = new Ufosim();
}

Vertical::~Vertical() {                         // destructor
    delete sim;
}

// getters

std::string Vertical::getType() {
    return type;
}

const std::string& Vertical::getId() const {
    return id;
}

std::vector<float> Vertical::getPosition() const {
    return { sim->getX(), sim->getY(), sim->getZ() };
}

float Vertical::getFtime() const {
    return sim->getFtime();
}

// functions

void Vertical::flyToDest(const float x, const float y, const float height, const int speed) const {
    sim->flyTo(sim->getX(), sim->getY(), height, speed, 0);     // fly upwards to height
    sim->flyTo(x, y, height, speed, 0);                         // fly to x y of destination
    sim->flyTo(x, y, 0.0, speed, 0);                            // fly down to height 0
    return;
}

float Vertical::angle(const float x1, const float y1, const float x2, const float y2) {
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

