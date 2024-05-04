#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define limit 10000000

struct timespec {
    time_t tv_sec; /* Sekunden */
    long tv_nsec; /* Nanosekunden */
};

void* isPrime(void* args) {
    uintptr_t *a = (uintptr_t *)args;
    for(int i = 2; i < *a-1; i++) {
        if(*a % i == 0) {
            printf("%d\n", *a);
        } 
    }
}

int main (int argc, char* argv[]) {
    int threadCount = atoi(argv[1]);
    if(threadCount > 8 || threadCount < 1) { 
        threadCount = 1;
    }
    
    pthread_t thread[threadCount];
    int i;
    for(i = 0; i < threadCount-1; i++) {
        pthread_create(&thread[i], NULL, *isPrime, NULL);
    }

    
    return 0;
}