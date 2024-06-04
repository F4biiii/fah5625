#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <semaphore>
#include <chrono>

using namespace std;

vector<int> list;                               // global empty list
std::counting_semaphore<1> semInit(1);             // counting semaphore, value 1, initially 1
std::counting_semaphore<1> semProt(1);             // counting semaphore, value 1, initially 1


void produce(int data) 
{ 
    semProt.acquire();
    list.insert(list.begin(), data);            // insert the random number parameter
    cout << "Producer: " << data << endl;   
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));    // wait for random amout of nanoseconds,  0-1 millisecond
    semProt.release();
    semInit.release();
}

void consume() 
{ 
    semProt.acquire();
    if(!list.empty()) {                                                 // if list is not empty
        int listEnd = list[list.size()-1];
        list.pop_back();                                                    // delete last element of list
        cout << "Consumer: " << listEnd << endl << endl;
    } else {                                                            // if list is empty
        cout << "Consumer: list empty" << endl << endl;
    }
    semProt.release();
    semInit.release();
}

int main(int argc, char* argv[]) {
    short prodCount;                            // how many producers shall there be
    short consCount;                            // how many consumers shall there be
    if(argv[1] != 0 && argv[2] != 0 && atoi(argv[1]) > 0 && atoi(argv[2]) > 0) {         // programm input
        prodCount = atoi(argv[1]);
        consCount = atoi(argv[2]);
    }
    else {
        prodCount = 1;                          // set to 1 if invalid        
        consCount = 1;                          // set to 1 if invalid
    }
    
    int data;
    std::srand(pthread_self());                       // use the time as seed for randomizer
    
    thread producer[prodCount];                 // array for producer threads
    thread consumer[consCount];                 // array for consuemer threads

    int range = max(prodCount, consCount);
    for(int i = 0; i < range; i++)          // create the threads
    {
        data = std::rand() % 1000000;               // get random number between 0 and 1000000
        if (i < prodCount) {
            semInit.acquire();
            producer[i] = thread(produce, data);
        }
        if (i < consCount) {
            semInit.acquire();
            consumer[i] = thread(consume);
        }
    }                        

    for(int i = 0; i < prodCount; i++)          // join the threads
    {
        producer[i].join();
    }
    for(int i = 0; i < consCount; i++)          // join the threads
    {
        consumer[i].join();
    }
  
    return 0;
}
