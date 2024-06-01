#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <semaphore>
#include <chrono>

using namespace std;

vector<int> list;           // global empty list
std::counting_semaphore<1> sem(1);

void produce(int data) 
{
    sem.acquire();                             // thread enters semaphore, decreases value from 1 to 0
    list.insert(list.begin(), data);            // insert the random number parameter
    sem.release();                             // thread exits the semaphore, decrease value from 0 to 1    
    cout << "Producer: " << data << endl;   
    std::this_thread::sleep_for(std::chrono::nanoseconds(data));    // wait for random amout of nanoseconds, 0 - 1000000  
}

void consume() 
{ 
    if(!list.empty()) {                                     // if list is not empty
        sem.acquire();                                     // thread enters semaphore, decreases value from 1 to 0
        int listEnd = list[list.size()-1];                  // safe end of list for output
        list.erase(list.end()-1);                           // delete last element of list
        sem.release();                                     // thread exits semaphore, increases value from 0 to 1
        cout << "Consumer: " << listEnd << endl << endl;
    } else {                                                // if list is empty
        
        cout << "Consumer: list empty" << endl << endl;
    } 
}

int main(int argc, char* argv[]) {
    short prodConsCount;                            // how many producers/consumers shall there be
    if(argv[1] != 0 && atoi(argv[1]) > 0) {         // programm input
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
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
        consumer[i] = thread(consume);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
    }


    for(int i = 0; i < prodConsCount; i++)          // join the threads
    {
        producer[i].join();
        consumer[i].join();        
    }
  
    return 0;
}
