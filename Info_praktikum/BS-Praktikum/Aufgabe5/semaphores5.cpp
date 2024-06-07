#include <iostream>
#include <vector>
#include <thread>
#include <semaphore>
#include <chrono>
#include <random>


using namespace std;

vector<int> list;                                   // global empty list

int listCount = 0;
int prodCount = 1000;
bool isDone = 0;

counting_semaphore<5> semC(0);                 // counting semaphore, value 1, initially 0. Releases the consumer
counting_semaphore<1> semProt(1);              // binary semaphore, value 1, initially 1. Protects critical area


void produce() 
{ 
    int data;
    random_device rd;                          
    mt19937 gen(rd());    
    uniform_int_distribution<> dis(0, 1000000);        // random number gnerator between 0 and 1000000
    while (prodCount > 0){
        semProt.acquire();                              // protect the critical area
        if(listCount < 5) { 
            data = dis(gen);                            // get random number 
            list.insert(list.begin(), data);            // insert the random number to list
            cout << "Producer: " << data << " listCount: " << listCount << endl;   
            listCount++;
            prodCount--;
            semC.release();                             // release consumer
        } 
        semProt.release();                              // leave critical area
        this_thread::sleep_for(chrono::nanoseconds(data));    // wait for random amout of nanoseconds,  0-1 millisecond
    }
    semProt.acquire();
    isDone = 1;
    semProt.release();
    semC.release();
}

void consume() 
{ 
    while(1) {
        semC.acquire();                                 // wait for producer
        if(isDone) { break; }                           // break if nothing more to do
        semProt.acquire();                              // protect the critical area
        int listEnd = list.back();
        list.pop_back();                                // delete last element of list
        cout << "Consumer: " << listEnd << " listCount: " << listCount << endl;        // print it 
        listCount--;
        semProt.release();                              // leave critical area
    }
}

int main(int argc, char* argv[]) {
    short prodAmount;                            // how many producers shall there be
    short consAmount;                            // how many consumers shall there be
    if(argv[1] != 0 && argv[2] != 0 && atoi(argv[1]) > 0 && atoi(argv[2]) > 0) {         // programm input
        prodAmount = atoi(argv[1]);
        consAmount = atoi(argv[2]);
    }
    else {
        cout << "Invalid input. Initialized variables with 1" << endl;
        cout << "Usage: ./sem4 [amount of producers] [amount of consumers]" << endl << endl;
        prodAmount = 1;                          // set to 1 if invalid        
        consAmount = 1;                          // set to 1 if invalid
    }
    
    thread producer[prodAmount];                 // array for producer threads
    thread consumer[consAmount];                 // array for consuemer threads

    //list.push_back(2);

    int range = max(prodAmount, consAmount);
    for(int i = 0; i < range; i++)              // create the threads
    {
        if (i < prodAmount) 
            producer[i] = thread(produce);
        this_thread::sleep_for(chrono::nanoseconds(1000000));    // wait for 1 millisecond

        if (i < consAmount) 
            consumer[i] = thread(consume);
        this_thread::sleep_for(chrono::nanoseconds(1000000));    // wait for 1 millisecond

    }       

    for(int i = 0; i < range; i++)              // join the threads
    {
        if (i < prodAmount) 
            producer[i].join();
        if (i < consAmount) 
            consumer[i].join();
    }  
    return 0;
}
