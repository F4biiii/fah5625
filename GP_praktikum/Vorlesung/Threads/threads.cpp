#include <iostream>
#include <thread>

void run()
{
    int countdown = 10;
    std::cout << "MyThread started\n";
    for(;countdown >= 0; countdown--)
    {
        std::cout << ". ";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << "\nMyThread terminated\n";
}

int main()
{
    std::thread myThread;
    myThread = std::thread(run);
    std::cout << "Waiting for thread to terminate\n";
    myThread.join();
}