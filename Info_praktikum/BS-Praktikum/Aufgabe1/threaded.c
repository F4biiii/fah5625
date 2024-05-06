#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define limit 100000

struct threadParam {
    int threadID;
    int start;
    int step;
    double* threadT;
}; 

void* isPrime(void* args) {
    struct threadParam* data = (struct threadParam*)  args;
    struct timespec sleep = { 0, 1000 }; 
    struct timespec thr1;                                         
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thr1); 
    for(int i = data->start; i <= limit; i+=data->step) {
        int prime = 1;
        for(int j = 2; j < i; j++) {
            if(i % j == 0) {
                prime = 0;
                break;
            }
        }
        if(prime && i > 1) {
            printf("%d (Thread: %d)\n", i, data->threadID);
        }
        nanosleep(&sleep, NULL);
    }
    struct timespec thr2;                                         
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thr2); 
    *data->threadT = (thr2.tv_sec - thr1.tv_sec) + (thr2.tv_nsec - thr1.tv_nsec) / 1000000000.0;  // get elapsed time in seconds

    return NULL;
}

int main (int argc, char* argv[]) {
    struct timespec tim1;
    struct timespec tim2;   
    struct timespec sleep = {0, 1000 };  
    clock_gettime(CLOCK_MONOTONIC, &tim1);

    int threadCount = atoi(argv[1]);                                                   // input, how many threads shall calculate
    printf("Calculating with %d Thread(s)}\n\n", threadCount);

    pthread_t thread[threadCount];                                     // array for threadID
    double threadTime[threadCount];                                    // save elapsed time for each thread
    struct threadParam data[threadCount];                              // struct for thread function parameter (threadId, start, step range, time)      
    
    int threadStart = 2;
    for(int i = 0; i < threadCount; i++) {                      
        data[i].threadID = i;
        data[i].start = threadStart;
        data[i].step = threadCount;
        data[i].threadT = &threadTime[i];

        pthread_create(&thread[i], NULL, *isPrime, (void* )&data[i]);
        threadStart ++;
        nanosleep(&sleep, NULL);
    }
    
    for(int j = 0; j < threadCount; j++) {                        // wait for all threads to finish
        pthread_join(thread[j], NULL);
    }
                                          
    clock_gettime(CLOCK_MONOTONIC, &tim2);
    
    double time = (tim2.tv_sec - tim1.tv_sec) + (tim2.tv_nsec - tim1.tv_nsec) / 1000000000.0;  // get elapsed time in seconds
    printf("\n%lf seconds elapsed\n", time);
    for (int i = 0; i < threadCount; i++) {
        printf("Thread %d: %lf seconds\n", i, threadTime[i]);
    }
    return 0;
}
