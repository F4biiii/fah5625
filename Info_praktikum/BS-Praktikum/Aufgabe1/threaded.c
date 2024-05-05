#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define limit 1000000

struct threadParam {
    int start;
    int step;
}; 

void* isPrime(void* args) {
    struct threadParam* data = (struct threadParam*)  args;
    struct timespec sleep = { 0, 1000 };  
    for(int i = data->start; i <= limit; i+=data->step) {
        int prime = 1;
        for(int j = 2; j < i; j++) {
            if(i % j == 0) {
                prime = 0;
                break;
            }
        }
        if(prime && i > 1) {
            printf("%d (Thread: %d)\n", i, data->start-2);
        }
        nanosleep(&sleep, NULL);
    }
    return NULL;
}

int main (int argc, char* argv[]) {
    struct timespec tim1;
    timespec_get(&tim1, TIME_UTC);

    int threadCount;
    if(argv[1] != NULL) {
        threadCount = atoi(argv[1]);                                   // get the desired amount of calculating cores
        printf("Calculating with %d Thread(s)}\n\n", threadCount);
    } else {
        printf("Calculating with one thread...\n\n");
        threadCount = 1;                                               // one thread if no argument
    }

    pthread_t thread[threadCount];                                     // array for threadID
    struct threadParam data[threadCount];                              // struct for thread function parameter (start and end of range)

    if(threadCount < 1) {                            
        threadCount = 1;                                               // set it to 1 if instruction invalid
    }         

    struct timespec sleep = {0, 1000 };  
    for(int i = 0; i < threadCount; i++) {                    
        data[i].start = i+2;
        data[i].step = threadCount;
        pthread_create(&thread[i], NULL, *isPrime, (void* )&data[i]);
        nanosleep(&sleep, NULL);
    }
    
    for(int j = 0; j < threadCount; j++) {                        // wait for all threads to finish
        pthread_join(thread[j], NULL);
    }
    struct timespec tim2;
    timespec_get(&tim2, TIME_UTC);
    
    double time = (tim2.tv_sec - tim1.tv_sec) + (tim2.tv_nsec - tim1.tv_nsec) / 1000000000.0;
    printf("\n%lf seconds elapsed\n", time);
    return 0;
}
