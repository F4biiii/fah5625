#include <iostream>
#include "vertical_thread.h"
int main() {
 
    VerticalThread vthread;
    // fly from (0.0, 0.0, 0.0) to (5.0, -1.5, 0.0)
    // at altitude 4.0 with 10 km/h in a new thread
    vthread.startUfo(5.0, -1.5, 4.0, 10);
    // in the time until landing other work could be done
    while (vthread.getIsVertFlying())
    {
        std::cout << '.';
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // fly from (5.0, -1.5, 0.0) to (-3.0, 0.0, 0.0)
    // at altitude 8.0 with 5 km/h in a new thread
    vthread.startUfo(-3.0, 0.0, 8.0, 5);
    return 0;
}