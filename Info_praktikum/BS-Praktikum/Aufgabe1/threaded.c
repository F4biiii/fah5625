#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define limit 1000000


struct threadParam {
    int start;
    int threadCount;
    double* threadT;
}; 

void* isPrime(void* args) {
    struct threadParam* data = (struct threadParam*)  args;
    struct timespec thr1;                                         
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &thr1); 
    int range = 500;
    
    for(int i = data->start * range; i < limit; i+=range*data->threadCount) {
        //printf("%d Thread: %d\n", i, data->start);
        for(int j = i; j < i+range; j++) {          
            int prime = 1;
            for(int k = 2; k < j; k++) {
                if(j % k == 0) {
                    prime = 0;
                    break;
                }
            }
            if(prime && j > 1) {
                printf("%d (Thread: %d)\n", j, data->start);
            }
        }
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
    int threadCnt;
    if(argv[1] != NULL && atoi(argv[1]) > 0) {
        threadCnt = atoi(argv[1]);                                                   // input, how many threads shall calculate
        printf("Calculating with %d Thread(s)}\n\n", threadCnt);
    } else {
        threadCnt = 1;
        printf("Calculating with one Thread\n\n");
    }


    pthread_t thread[threadCnt];                                     // array for threadID
    double threadTime[threadCnt];                                    // save elapsed time for each thread
    struct threadParam data[threadCnt];                              // struct for thread function parameter (threadId, start, step range, time)      
    
   
    for(int i = 0; i < threadCnt; i++) {                      
        data[i].start = i;
        data[i].threadCount = threadCnt;
        data[i].threadT = &threadTime[i];

        pthread_create(&thread[i], NULL, *isPrime, (void* )&data[i]);
        nanosleep(&sleep, NULL);
    }
    
    for(int j = 0; j < threadCnt; j++) {                        // wait for all threads to finish
        pthread_join(thread[j], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &tim2);
    
    double time = (tim2.tv_sec - tim1.tv_sec) + (tim2.tv_nsec - tim1.tv_nsec) / 1000000000.0;  // get elapsed time in seconds
    printf("\n%lf seconds elapsed\n", time);
    for (int i = 0; i < threadCnt; i++) {
        printf("Thread %d: %lf seconds\n", i, threadTime[i]);
    }
    return 0;
}
