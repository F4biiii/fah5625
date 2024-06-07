#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>

#define limit 1000000

int count = 2;                                                         // current number to be checked for prime

struct threadParam {                                                                // struct with arguments for thread function
    int threadNumber;                                                                   // chronological numeration of all threads [0, threadCount]
    double* threadT;                                                                    // variable to save elapsed time for each thread
    int* threadPrimeCount;                                                              // variable to save found primes for each thread
}; 

void* printPrimes(void* args) {                                                         
    struct threadParam* data = (struct threadParam*)  args;                             
    struct timespec thr1;                                                               // variable to safe time of thread start
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thr1);                                      // safe time of thread start
    int foundPrimes = 0;                                                                // so far found primes
    int countCpy;                                                                       // copy the current number to be checked for prime
    while(count <= limit) {                                                             
        int prime = 1;                                                                      // prime status of the number we check is initially true
        
        countCpy = atomic_fetch_add(&count, 1);                                                                 // copy the count and increase count afterwards
                                                                             
        for(int i = 2; i < countCpy; i++) {                                                            
            if(countCpy % i == 0) {                                                             // if the checked number can be divided by any other number (from 2 - checked number) without rest
                prime = 0;                                                                      // checked number is no prime
                break;                                                                          // stop checking 
            }
        }
        if(prime) {                                                                
            //printf("%d (Thread: %d)\n", countCpy, data->threadNumber);                          // print if it is a prime
            foundPrimes++;                                                                      // increase found primes
        }
    }
                                                                                     
    struct timespec thr2;                                                                           // variable to safe time of thread end
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thr2);                                                  // safe time of thread end    
    *data->threadT = (thr2.tv_sec - thr1.tv_sec) + (thr2.tv_nsec - thr1.tv_nsec) / 1000000000.0;    // safe elapsed time in seconds
    *data->threadPrimeCount = foundPrimes;                                                          // safe found primes

    return NULL;
}

int main (int argc, char* argv[]) {
    struct timespec tim1;                                           // variable to save first time of start
    struct timespec tim2;                                           // variable to save time of end
    clock_gettime(CLOCK_MONOTONIC, &tim1);                          // safe time of start 
    int threadCnt;                                                  // variable to save amount of desired threads
    if(argv[1] != NULL && atoi(argv[1]) > 0) {                      // if user added an argument 
        threadCnt = atoi(argv[1]);                                      // safe input (how many threads shall calculate)
        printf("Calculating with %d Thread(s)}\n\n", threadCnt);        // print the amount of calculating threads
    } else {                                                        // user didn't add an argument or argument invalid
        threadCnt = 1;                                                  // set amount of calculating threads to 1
        printf("Calculating with one Thread\n\n");                      // print the amount of calculating threads
    }

    struct threadParam data[threadCnt];                             // struct for thread function parameter 
    pthread_t thread[threadCnt];                                    // array for thread pointers
    double threadTime[threadCnt];                                   // array to save elapsed time for each thread
    int primeCount[threadCnt];                                      // array to save the found primes for each thread

    for(int i = 0; i < threadCnt; i++) {                             // create every thread
        data[i].threadNumber = i;                                       // chronological thread number
        data[i].threadT = &threadTime[i];                               // pointer to safe elapsed thread time
        data[i].threadPrimeCount = &primeCount[i];                      // pointer to safe amount of found primes
        
        pthread_create(&thread[i], NULL, *printPrimes, (void* )&data[i]);   // start thread with struct as parameter
    }
    
    for(int j = 0; j < threadCnt; j++) {                        // wait for all threads to finish
        pthread_join(thread[j], NULL);                  
    }

    clock_gettime(CLOCK_MONOTONIC, &tim2);                      // safe time of end 
    
    double time = (tim2.tv_sec - tim1.tv_sec) + (tim2.tv_nsec - tim1.tv_nsec) / 1000000000.0;   // calculate elapsed time in seconds
    for (int i = 0; i < threadCnt; i++) {                                                       // print thread time for each thread
        printf("\nThread %d: %lf seconds", i, threadTime[i]);
    }

    printf("\n\n%lf seconds elapsed\n", time);                  // print total elapsed time
    int totalPrimes = 0;   
    for(int i = 0; i < threadCnt; i++) {                        // iterate through the array "totalPrimes[threadCnt]" 
        totalPrimes += primeCount[i];                           // add up all elements, every thread safed the amount of found primes in his element of the array
    }
    printf("%d primes found between 2 and %d\n\n", totalPrimes, limit);                   // print all found primes
    
    return 0;
}
