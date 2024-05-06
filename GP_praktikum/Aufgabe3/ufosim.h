/* DO NOT CHANGE THIS FILE

 * ufoim
 * Simulation of Unified Flying Objects
 * Copyright (C) 2013-2022 R. Gold
 *
 * This file is intended for use as an example, and
 * may be used, modified, or distributed in source or
 * object code form, without restriction, as long as
 * this copyright notice is preserved.
 *
 * The code and information is provided "as-is" without
 * warranty of any kind, either expressed or implied.
 *
 * Version: 4.0.2c
 *
 * Change history:
 *
 * 4.0.0:
 * - VMAX, ACCELERATION, SPEEDUP changed to static
 * - SPEEDUP non-const to enable setting
 * - d, i, deltaD, deltaI, getD, getI, requestDeltaD, requestDeltaI,
 *   setD, setI deleted
 * - requestDeltaV changed to private
 * - methods setSpeedup, flyTo added
 * - attribute for thread added
 * - thread started in constructor and deleted in destructor
 *
 * 4.0.1:
 * - attributes set to volatile
 * - additional parameter vPost added to flyTo
 * - console output changed
 * - print function added
 * 
 * 4.0.2:
 * - bug fixed (requestDeltaV(-vFlight + vPost); instead of 
 *   requestDeltaV(-v + vPost);)
 * - some console output removed
*/

#ifndef UFOSIM_H
#define UFOSIM_H

#include <string>
#include <thread>

class Ufosim
{
private:
    // sim constants
    static constexpr int VMAX = 50;         // maximal velocity [km/h]
    static constexpr int ACCELERATION = 1;  // constant acceleration [km/h/0.1s]

    // sim attributes
    static int SPEEDUP;                     // real-time speedup factor > 0
    volatile float x = 0.0;                 // x coordinate [m]
    volatile float y = 0.0;                 // y coordinate [m]
    volatile float z = 0.0;                 // z coordinate [m]
    volatile int v = 0;                     // 0 <= velocity <= vMax [km/h]
    volatile float dist = 0.0;              // distance covered since reset [m]
    volatile float ftime = 0.0;             // elapsed flight time with v > 0 [s]
    volatile float xvect = 0.0;             // flight vector in x direction
    volatile float yvect = 0.0;             // flight vector in y direction
    volatile float zvect = 0.0;             // flight vector in z direction
    volatile int deltaV = 0;                // requested change of v
    volatile float vel = 0.0;               // velocity [m/s]

public:
    // constructor
    Ufosim();

    // destructor
    ~Ufosim();

    // getter
    float getX() const;
    float getY() const;
    float getZ() const;
    int getV() const;
    float getDist() const;
    float getFtime() const;

private:
    // requester
    void requestDeltaV(const int delta);

public:
    // setter
    static void setSpeedup(const int speedup);

private:
    // thread attributes
    bool running = true;                    // simulation running
    std::thread simThread;                  // simulation thread

    // update simulation
    void updateSim();

    // thread function
    void runSim();

public:
    // fly to
    void flyTo(const float xDest, const float yDest, const float zDest,
               const int vFlight, const int vPost);

private:
    // print message to console
    void print(std::string message);
};

#endif
