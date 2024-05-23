#include "vertical_thread.h"

//constructor
VerticalThread::VerticalThread() { 
    vert = new Vertical("threadVert");          // allocate memmory for vertical object, set id to "threadVert"
}
    
//destructor
VerticalThread::~VerticalThread() 
{
    if(flyThread != nullptr)                    // if a thread is still active
    {
        flyThread->join();                          // wait for it to end and close it
        delete flyThread;                           // free memmory of thread
    }
    isVertFlying = false;                       // reset isVertFlying to initially false
    delete vert;                                // free memmory of vertical object
}

//private methods
 void VerticalThread::runner(const float x, const float y, const float height, const int speed)
 {
    vert->flyToDest(x, y, height, speed);       // fly vert to given destination
    isVertFlying = false;                       // destination reached, vert is not flying anymore
 }

//public methods
 void VerticalThread::startUfo(const float x, const float y, const float height, const int speed)
 {
    if(flyThread != nullptr)                    // if a thread is still active
    {
        flyThread->join();                          // wait for it to end and close it
        delete flyThread;                           // free memmory of thread
    }
    flyThread = new std::thread(&VerticalThread::runner, this, x, y, height, speed);    // start a thread where the vert will fly to the given destination
    isVertFlying = true;                        // vert is flying now
}

 bool VerticalThread::getIsVertFlying() const
 {
    return isVertFlying;
 }