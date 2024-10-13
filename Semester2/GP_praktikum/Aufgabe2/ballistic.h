#ifndef BALLISTIC_H
#define BALLISTIC_H

#include "ufo.h"

class Ballistic : public Ufo
{
private:
    float takeOffAngle;
    float landingAngle;
public:
    // constructor
    Ballistic(const std::string& pId, const float pTakeOffAngle, const float pLandingAngle);
    // destructor
    ~Ballistic();
    // getters
    float getTakeOffAngle() const;
    float getLandingAngle() const;  

    // methods

    std::vector<float> firstWaypoint(const float x, const float y, const float height) const;
    std::vector<float> secondWaypoint(const float x, const float y, const float height) const;
    void flyToDest(const float x, const float y, const float height, const int speed) const override;
};

#endif