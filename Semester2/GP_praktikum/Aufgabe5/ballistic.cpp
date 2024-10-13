#include "ballistic.h"

// constructor for Ballistic

Ballistic::Ballistic(const std::string& pId, const float pTakeOffAngle, const float pLandingAngle) : Ufo(pId)
{
    if(pTakeOffAngle > 0.0 && pTakeOffAngle <= 90.0)                    // TakeOffAngle has to be between 0 and 90°
    {
        takeOffAngle = pTakeOffAngle;
    } else {                                                            // else set it to 45°
        takeOffAngle = 45.0;
    }
    
    if(pLandingAngle > 0.0 && pLandingAngle <= 90.0)                    // TakeOffAngle has to be between 0 and 90°
    {
        landingAngle = pLandingAngle;
    } else {                                                            // else set it to 45°
        landingAngle = 45.0;
    }
}

// destructor (does nothing)

Ballistic::~Ballistic() { }                                  

// getters

float Ballistic::getTakeOffAngle() const
{
    return takeOffAngle;
}
float Ballistic::getLandingAngle() const
{
    return landingAngle;
}

// methods

std::vector<float> Ballistic::firstWaypoint(const float x, const float y, const float height) const
{
    std::vector<float> initialPosition = getPosition();     // get the position of start

    // vector from start to end position
    float directionVectorX = x - initialPosition[0];        // calculate x-component x(destination) - x(initial)
    float directionVectorY = y - initialPosition[1];        // calculate y-component y(destination) - y(initial)
    
    float lengthDirectionVector = sqrt(directionVectorX*directionVectorX + directionVectorY*directionVectorY);  // calculate length of direction vector (ground distance from start to end)

    // change the length of direction vecotor to exactly 1 (makes it easy to reach a specific point on the track)
    directionVectorX = 1/lengthDirectionVector * directionVectorX;
    directionVectorY = 1/lengthDirectionVector * directionVectorY;


    float takeOffAngleDeg = getTakeOffAngle()*(std::numbers::pi /180 ); // get takeoff angle, change it from deg to rad
    float distanceFirstPoint = height / tan(takeOffAngleDeg);           // calculate length of first part (ground part until firstWayPoint)

    // vector addition 
    float xFinal = initialPosition[0] + directionVectorX * distanceFirstPoint;      // add the adjusted direction vector to the initial point
    float yFinal = initialPosition[1] + directionVectorY * distanceFirstPoint;      // add the adjusted direction vector to the initial point
    return {xFinal, yFinal};
}

std::vector<float> Ballistic::secondWaypoint(const float x, const float y, const float height) const
{
    std::vector<float> initialPosition = getPosition();     // get the position of start

    // vector from start to end position
    float directionVectorX = x - initialPosition[0];        // calculate x-component x(destination) - x(initial)
    float directionVectorY = y - initialPosition[1];        // calculate y-component y(destination) - y(initial)
    
    float lengthDirectionVector = sqrt(directionVectorX*directionVectorX + directionVectorY*directionVectorY);  // calculate length of direction Vector (ground distance from start to end)

    // change the length of direction vecotor to exactly 1 (makes it easy to reach a specific point on the track) 1/vectorlength * vector
    directionVectorX = 1/lengthDirectionVector * directionVectorX;
    directionVectorY = 1/lengthDirectionVector * directionVectorY;

    float landingAngleDeg =  getLandingAngle()*(std::numbers::pi/180);                      // get takeoff angle, change it from deg to rad
    float distanceSecondPoint = lengthDirectionVector - ( height / tan(landingAngleDeg) );  // calculate length of ground part until second waypoint 
    
    // vector addition 
    float xFinal = initialPosition[0] + directionVectorX * distanceSecondPoint;      // add adjusted direction vector to the initial point (direction vector is as long as distance to second track)
    float yFinal = initialPosition[1] + directionVectorY * distanceSecondPoint;      // add adjusted direction vector to the initial point (direction vector is as long as distance to second track)

    return {xFinal, yFinal};
}

void Ballistic::flyToDest(const float x, const float y, const float height, const int speed) const
{
    std::vector<float> pos1 = Ballistic::firstWaypoint(x, y, height);
    std::vector<float> pos2 = Ballistic::secondWaypoint(x, y, height);

    sim->flyTo(pos1[0], pos1[1], height, speed, speed);         // fly to first waypoint
    sim->flyTo(pos2[0], pos2[1], height, speed, speed);         // fly to second waypoint
    sim->flyTo(x, y, 0, speed, 0);                              // fly to actual destination
}