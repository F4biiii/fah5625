#ifndef vertical_thread_h
#define vertical_thread_h

#include "ufo.h"
#include "vertical.h"
#include <thread>

class VerticalThread 
{
private:
    std::thread* flyThread = nullptr;
    Vertical* vert;
    bool isVertFlying = false;

    //private methods
    void runner(const float x, const float y, const float height, const int speed);
public:
    //constructor
    VerticalThread();

    //destructor
    ~VerticalThread();

    //public methods
    void startUfo(const float x, const float y, const float height, const int speed);
    bool getIsVertFlying() const;
};
#endif