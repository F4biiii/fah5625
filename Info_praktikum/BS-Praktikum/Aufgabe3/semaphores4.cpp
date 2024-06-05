#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <chrono>

using namespace std;

vector<int> list;                                   // global empty list

std::counting_semaphore<1> semP(0);                 // counting semaphore, value 1, initially 0. Releases the consumer
std::counting_semaphore<1> semProt(1);              // counting semaphore, value 1, initially 1. Protects critical area


void produce(short prodCount) 
{ 
    semProt.acquire();                              // protect the critical area
    int data;
    std::srand(pthread_self());                     // use the threadID as seed for randomizer

    while (prodCount){
        data = std::rand() % 1000000;               // get random number between 0 and 1000000
        list.insert(list.begin(), data);            // insert the random number to list
        cout << "Producer: " << data << endl;   
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));    // wait for random amout of nanoseconds,  0-1 millisecond
        prodCount--;
    }
    semProt.release();                              // leave critical area
    semP.release();                                 // release the consumer 
}

void consume(short consCount) 
{ 
    semP.acquire();                                 // wait for the producer to release the consumer    
    semProt.acquire();                              // protect the critical area
    while(consCount) {
        int listEnd = list.back();
        list.pop_back();                            // delete last element of list
        cout << "Consumer: " << listEnd << endl;    // print it 
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

    int range = max(prodAmount, consAmount);
    for(int i = 0; i < range; i++)              // create the threads
    {
        if (i < prodAmount) 
            producer[i] = thread(produce, prodCount);
        if (i < consAmount) 
            consumer[i] = thread(consume, consCount);
    }       

    for(int i = 0; i < prodAmount; i++)          // join the threads
    {
        producer[i].join();
    }
    for(int i = 0; i < consAmount; i++)          // join the threads
    {
        consumer[i].join();
    }

    cout << endl << "List: ";
    if(list.empty()) {
        cout << "empty";
    } else {
        for(const auto iter: list) {
            cout << iter << " ";
        }
    }

    return 0;
}
