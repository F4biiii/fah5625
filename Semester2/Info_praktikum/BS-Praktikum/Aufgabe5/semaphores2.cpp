#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <semaphore>
#include <chrono>

using namespace std;

vector<int> list;                               // global empty list3
std::counting_semaphore<1> semA(1);              // counting semaphore, value 1, initially 1
std::counting_semaphore<1> semB(0);             // counting semaphore, value 1, initially 0


void produce(int data) 
{
    semA.acquire();
    list.insert(list.begin(), data);            // insert the random number parameter
    cout << "Producer: " << data << endl;   
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));    // wait for random amout of nanoseconds,  0-1 millisecond
    semB.release();                              // thread exits the semaphore, decrease value from 0 to 1    
}

void consume() 
{ 
    semB.acquire();
    if(!list.empty()) {                                                 // if list is not empty
        int listEnd = list[list.size()-1];
        list.pop_back();                                                    // delete last element of list
        cout << "Consumer: " << listEnd << endl << endl;
    } else {                                                            // if list is empty
        cout << "Consumer: list empty" << endl << endl;
    } 
    semA.release();                              // thread exits the semaphore, decrease value from 0 to 1    
}

int main(int argc, char* argv[]) {
    short prodConsCount;                            // how many producers/consumers shall there be
    if(argv[1] != 0 && atoi(argv[1]) >= 0) {         // programm input
        prodConsCount = atoi(argv[1]);
    }
    else {
        prodConsCount = 1;                          // set to 1 if invalid
    }
    
    int data;
    std::srand(std::time(0));                       // use the time as seed for randomizer
    
    thread producer[prodConsCount];                 // array for producer threads
    thread consumer[prodConsCount];                 // array for consuemer threads
    
    for(int i = 0; i < prodConsCount; i++)          // create the threads
    {
        data = std::rand() % 1000000;               // get random number between 0 and 1000000
        producer[i] = thread(produce, data);
        consumer[i] = thread(consume);
    }

    for(int i = 0; i < prodConsCount; i++)          // join the threads
    {
        producer[i].join();
        consumer[i].join();        
    }
  
    return 0;
}
