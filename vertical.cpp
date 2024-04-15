#include "vertical.h"
#include <cmath>

const std::string Vertical::type = "vertical";

Vertical::Vertical(const std::string& pId) {
    id = pId;
    Ufosim::setSpeedup(4);
    sim = new Ufosim();
}

Vertical::~Vertical() {
    delete sim;
}

const std::string Vertical::getType() {
    return type;
}

std::string& Vertical::getId() {
    return id;
}

std::vector<float> Vertical::getPosition() const {
    return {sim->getX(), sim->getY(), sim->getZ()};
}

float Vertical::getFtime() const {
    return sim->getFtime();
}

void Vertical::flyToDest(const float x, const float y, const float height, const int speed) {
    sim->flyTo(sim->getX(), sim->getY(), height, speed, 0);
    sim->flyTo(x, y, height, speed, 0);
    sim->flyTo(x, y, 0.0, speed, 0);
    return;
}

const float Vertical::angle(const float x1, const float y1, const float x2, const float y2) {
    float dotProduct = ((x2-x1)*0+(y2-y1)*1);

    float lengthV1 = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

    float lengthV2 = 1;

    float finalAngle = 0.0;

    if(lengthV1 != 0 && lengthV2 != 0)
        finalAngle = dotProduct / (lengthV1 * lengthV2);

    return acos(finalAngle)*180/M_PI;
}
