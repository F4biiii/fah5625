#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int count = 0;

sem_t sem;

const size_t MAX_CNT = 10000000;


void* increment(void* args) {
    int maxCnt = *(int* ) args;
    for(int i = 0; i < maxCnt; i++) {
        sem_wait(&sem);
        count++;
        sem_post(&sem);
    }
    return NULL;
}

void* decrement(void* args) {
    int maxCnt = *(int* ) args;
    for(int i = 0; i < maxCnt; i++) {
        sem_wait(&sem);
        count--;
        sem_post(&sem);
    }
    return NULL;
}

int main(void) {
    
    sem_init(&sem, 0, 1);
    printf("Count vor Bearbeitung: %d\n", count);

    pthread_t p1; 
    pthread_t p2;

    pthread_create(&p1, NULL, *increment, (void* )&MAX_CNT);
    pthread_create(&p2, NULL, *decrement, (void* )&MAX_CNT);

    printf("...\n");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    sem_destroy(&sem);

    printf("Count nach Bearbeitung: %d\n", count);


    return 0;
}