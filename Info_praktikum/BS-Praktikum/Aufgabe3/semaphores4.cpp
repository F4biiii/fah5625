#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <chrono>
#include <functional>

using namespace std;

vector<int> list;                                   // global empty list

std::counting_semaphore<1> semC(1);                 // counting semaphore, value 1, initially 0. Releases the consumer
std::counting_semaphore<1> semProt(1);              // counting semaphore, value 1, initially 1. Protects critical area


void produce(short prodCount) 
{ 
    semC.acquire();                                 // consumer has to waid
    semProt.acquire();                              // protect the critical area
    int data;
    std::srand(pthread_self());                               // use the threadID as seed for randomizer

    while (prodCount){
        data = std::rand();               // get random number between 0 and 1000000
        list.insert(list.begin(), data);            // insert the random number to list
        cout << "Producer: " << data << endl;   
        std::this_thread::sleep_for(std::chrono::nanoseconds(data));    // wait for random amout of nanoseconds,  0-1 millisecond
        prodCount--;
    }
    semProt.release();                              // leave critical area
    semC.release();                                 // release consumer
}

void consume(short consCount) 
{ 
    semC.acquire();                                 // wait for producer
    semC.release();                                 // don't block
    semProt.acquire();                              // protect the critical area
    while(consCount) {
        if(!list.empty()) {                          // if list is empty, break
            int listEnd = list.back();
            list.pop_back();                            // delete last element of list
            cout << "Consumer: " << listEnd << endl << endl;    // print it 
        } else {
            cout << "Consumer: List empty!" << endl;
        }
        consCount--;
    }
    semProt.release();                              // leave critical area
}

int main(int argc, char* argv[]) {
    short prodAmount;                            // how many producers shall there be
    short consAmount;                            // how many consumers shall there be
    short prodCount;                             // how many times shall the producer produce
    short consCount;                             // how many times shall the consumer consume
    if(argv[1] != 0 && argv[2] != 0 && argv[3] != 0 && argv[4] != 0 && atoi(argv[1]) > 0 && atoi(argv[2]) > 0 && atoi(argv[3]) > 0 && atoi(argv[4]) > 0) {         // programm input
        prodAmount = atoi(argv[1]);
        consAmount = atoi(argv[2]);
        prodCount = atoi(argv[3]);
        consCount = atoi(argv[4]);
    }
    else {
        cout << "Invalid input. Initialized variables with 1" << endl;
        cout << "Usage: ./sem4 [amount of producers] [amount of consumers] [producer count] [consumer count]" << endl << endl;
        prodAmount = 1;                          // set to 1 if invalid        
        consAmount = 1;                          // set to 1 if invalid
        prodCount = 1;                           // set to 1 if invalid
        consCount= 1;                            // set to 1 if invalid
    }
    
    thread producer[prodAmount];                 // array for producer threads
    thread consumer[consAmount];                 // array for consuemer threads

    //list.push_back(2);

    int range = max(prodAmount, consAmount);
    for(int i = 0; i < range; i++)              // create the threads
    {
        if (i < prodAmount) 
            producer[i] = thread(produce, prodCount);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));    // wait for 1 millisecond

        if (i < consAmount) 
            consumer[i] = thread(consume, consCount);
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));    // wait for 1 millisecond

    }       

    for(int i = 0; i < range; i++)              // join the threads
    {
        if (i < prodAmount) 
            producer[i].join();
        if (i < consAmount) 
            consumer[i].join();
    }  

    cout << endl << "List: ";                   // print the list
    if(list.empty()) {
        cout << "empty" << endl;
    } else {
        for(const auto iter: list) {
            cout << iter << " ";
        }
        cout << endl;
    }

    return 0;
}
