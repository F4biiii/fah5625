#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count = 0;

const size_t MAX_CNT = 10000000;


void* increment(void* args) {
    int maxCnt = *(int* ) args;
    for(int i = 0; i < maxCnt; i++) {
        count++;
    }
    return NULL;
}

void* decrement(void* args) {
    int maxCnt = *(int* ) args;
    for(int i = 0; i < maxCnt; i++) {
        count--;
    }
    return NULL;
}

int main(void) {
    printf("Count vor Bearbeitung: %d\n", count);

    pthread_t p1; 
    pthread_t p2;

    pthread_create(&p1, NULL, *increment, (void* )&MAX_CNT);
    pthread_create(&p2, NULL, *decrement, (void* )&MAX_CNT);

    printf("...\n");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Count nach Bearbeitung: %d\n", count);

    return 0;
}