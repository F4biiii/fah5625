#ifndef BALLISTIC_H
#define BALLISTIC_H

#include <vector>

class Ballistic
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
};

#endif