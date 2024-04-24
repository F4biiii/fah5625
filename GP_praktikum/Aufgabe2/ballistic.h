#ifndef BALLISTIC_H
#define BALLISTIC_H

#include <vector>
#include "ufo.h"

class Ballistic : public Ufo
{
private:
    float takeOffAngle;
    float landingAngle;
public:
    // constructor
    Ballistic(const float pTakeOffAngle, const float pLandingAngle);
    // destructor
    ~Ballistic();
    // getters
    const float getTakeOffAngle() const;
    const float getLandingAngle() const;  

    // methods

    std::vector<float> firstWaypoint(const float x, const float y, const float height) const;
    std::vector<float> secondWaypoint(const float x, const float y, const float height) const;
    void flyToDest(const float x, const float y, const float height, const int speed) const override;
};

#endif