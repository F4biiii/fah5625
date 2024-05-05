#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define limit 100000

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
            printf("%d (Thread: %d, %d)\n", i, data->start-2, data->step);
        }
        nanosleep(&sleep, NULL);
    }
    return NULL;
}

int main (int argc, char* argv[]) {
    struct timespec tp;
    int tim1 = clock_gettime(CLOCK_REALTIME, &tp);
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

    if(threadCount > 8 || threadCount < 1) {                            
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
    int tim2 = clock_gettime(CLOCK_REALTIME, &tp);
    printf("%d\n", tim2);
    return 0;
}
