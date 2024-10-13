#ifndef vertical_thread_h
#define vertical_thread_h

#include "vertical.h"
#include <thread>
#include <QObject>

class VerticalThread : public QObject
{
    Q_OBJECT

private:
    std::thread* flyThread = nullptr;
    Vertical* vert;
    bool isVertFlying = false;

    //private methods
    void runner(const float x, const float y, const float height, const int speed)
    {
        vert->flyToDest(x, y, height, speed);       // fly vert to given destination
        isVertFlying = false;                       // destination reached, vert is not flying anymore
        emit stopped(vert->getPosition());          // send signal that flight is done
    }
public:
    //constructor
    VerticalThread()
    {
        vert = new Vertical("threadVert");          // allocate memmory for vertical object, set id to "threadVert"
    }

    //destructor
    ~VerticalThread()
    {
        if(flyThread != nullptr)                    // if a thread is still active
        {
            flyThread->join();                          // wait for it to end and close it
            delete flyThread;                           // free memmory of thread
        }
        isVertFlying = false;                       // reset isVertFlying to initially false
        delete vert;                                // free memmory of vertical object
    }

    //public methods
    void startUfo(const float x, const float y, const float height, const int speed)
    {
        if(flyThread != nullptr)                    // if a thread is still active
        {
            flyThread->join();                          // wait for it to end and close it
            delete flyThread;                           // free memmory of thread
        }
        flyThread = new std::thread(&VerticalThread::runner, this, x, y, height, speed);    // start a thread where the vert will fly to the given destination
        isVertFlying = true;                        // vert is flying now
    }

    bool getIsVertFlying() const
    {
        return isVertFlying;
    }

signals:
    void stopped(std::vector<float>);               // signal that the flight is done

};
#endif
