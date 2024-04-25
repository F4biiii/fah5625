#include <chrono>
#include <cmath>
#include <iostream>
#include "ufosim.h"

int Ufosim::SPEEDUP = 50;

Ufosim::Ufosim()
{
    simThread = std::thread(&Ufosim::runSim, this);
}
Ufosim::~Ufosim()
{
    running = false;
    simThread.join();
}
float Ufosim::getX() const
{
    return x;
}
float Ufosim::getY() const
{
    return y;
}
float Ufosim::getZ() const
{
    return z;
}
int Ufosim::getV() const
{
    return v;
}
float Ufosim::getDist() const
{
    return dist;
}
float Ufosim::getFtime() const
{
    return ftime;
}
void Ufosim::requestDeltaV(const int delta)
{
    deltaV = deltaV + delta;
}
void Ufosim::setSpeedup(const int speedup)
{
    if (SPEEDUP != 1)
        /*std::cout << "ufosim warning: speedup can be set only once"
                  << std::endl*/;
    else if (speedup < 1 || speedup > 50)
    {
        /*std::cout << "ufosim warning: speedup has to be between 1 and 50"
                  << std::endl;*/
        SPEEDUP = 1;
    }
    else
        SPEEDUP = speedup;
}
void Ufosim::updateSim()
{
    // update time if flying
    if (z > 0.0)
        ftime = ftime + 0.1;

    // update v, d, i, dist, x, y, z if not crashed
    if (z >= 0.0)
    {
        // update v
        if (deltaV > 0)
        {
            if (deltaV - ACCELERATION > 0)
            {
                if (v + ACCELERATION < VMAX)
                    v = v + ACCELERATION;
                else
                    v = VMAX;
                deltaV = deltaV - ACCELERATION;
            }
            else
            {
               if (v + deltaV < VMAX)
                    v = v + deltaV;
                else
                    v = VMAX;
                deltaV = 0;
            }
        }
        else if (deltaV < 0)
        {
            if (deltaV + ACCELERATION < 0)
            {
                if (v - ACCELERATION > 0)
                    v = v - ACCELERATION;
                else
                    v = 0.0;
                deltaV = deltaV + ACCELERATION;
            }
            else
            {
                if (v + deltaV > 0.0)
                    v = v + deltaV;
                else
                    v = 0.0;
                deltaV = 0;
            }
        }
    }

    // update velocity in m/s
    vel = v / 3.6;

    // update distance
    dist = dist + vel / 10.0;

    // calculate new position every 100 ms with 1/10 of v
    x = x + vel / 10.0 * xvect;
    y = y + vel / 10.0 * yvect;
    z = z + vel / 10.0 * zvect;

    // stop if landed or crashed
    if (z <= 0.0)
    {
        if (v == 1)           // landed with slow velocity
        {
            z = 0.0;
            v = 0;
        }
        else if (v > 1)       // crashed to the ground
        {
            z = -1.0;
            v = 0;
        }
    }
}
void Ufosim::runSim()
{
    while (running)
    {
        updateSim();
        std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));
    }
}
void Ufosim::flyTo(const float xDest, const float yDest,
                   const float zDest, const int vFlight, const int vPost)
{
    float deltaX = xDest - x;
    float deltaY = yDest - y;
    float deltaZ = zDest - z;
    float distToDest = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
    float d = dist + distToDest;
    xvect = deltaX / distToDest;
    yvect = deltaY / distToDest;
    zvect = deltaZ / distToDest;

    print("flying with " + std::to_string(vFlight) + " km/h");
    requestDeltaV(vFlight - v);        // de/accelerate to vFlight

    while (d - dist > 4.0)             // fly until distance to dest <= 4.0
        std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));

    if (vPost <= 0)
    {
        //print("decelerating to 1 km/h");
        requestDeltaV(-vFlight + 1);   // de/accelerate to 1

        if (zDest == 0.0)              // landing
        {
            while (z > 0.0)            // fly until surface is reached, that sets v to 0
                std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));

            if (z < 0)
                print("crashed to the ground");
            else
                print("landed");
        }
        else
        {
            while (d - dist > 0.03)    // fly until distance to dest <= 0.03
                std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));

            //print("stopped");
            requestDeltaV(-1);         // de/accelerate to 0
       }


        while (v != 0)                 // make sure that v is 0
            std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));
    }
    else
    {
        //print("flying with " + std::to_string(vPost) + " km/h");
        requestDeltaV(-vFlight + vPost);     // de/accelerate to vPost

        while (d - dist > 0.03)        // fly until distance to dest <= 0.03
            std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));

        while (v != vPost)             // make sure that v is vPost
            std::this_thread::sleep_for(std::chrono::milliseconds(100/SPEEDUP));
    }
}

void Ufosim::print(std::string message)
{
    std::cout.setf(std::ios::fixed);
    std::cout.precision(1);
    std::cout.width(4);
    std::cout << ftime << " s : ";
    std::cout.precision(2);
    std::cout.width(6);
    std::cout << x << " ";
    std::cout.width(6);
    std::cout << y << " ";
    std::cout.width(5);
    std::cout << z << " : " << message << std::endl;
}
