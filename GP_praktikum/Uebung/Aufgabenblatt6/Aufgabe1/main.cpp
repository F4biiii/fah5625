#include <chrono>
#include <iostream>
#include <random>
#include <thread>

std::mutex mtx;

class Sender
{
private:
    int number;
    int countdown;
    std::mt19937 r;
    std::thread *senderThread;

    void run()
    {
        mtx.lock();
        std::cout << "\nsending message " << number << ": ";
        mtx.unlock();
        for (; countdown >= 0; countdown--)
        {
            mtx.lock();
            std::cout << number << " ";
            mtx.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(r()%200));
        }
       
    }

public:
    Sender(const int pNumber, const int pCountdown)
    {
        number = pNumber;
        countdown = pCountdown;
        senderThread = new std::thread(Sender::run, this);
    }

    ~Sender()
    {
        senderThread->join();
    }
};


int main()
{
    Sender sender1(1, 20);
    Sender sender2(2, 20);
    return 0;
}
