#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

struct sync {
    sem_t newWork;
    sem_t newResult;
    void *payloadOffset;
};

struct payload {
    int work;
    int result;
};

int size = sizeof(struct sync) + sizeof(struct payload);
int count = 0;

void producer() {
    int shm_fd = shm_open("/sharedM", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        exit(EXIT_FAILURE);
    }
    
    if (ftruncate(shm_fd, size) == -1) {
        exit(EXIT_FAILURE);
    }
    
    void* shMemory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shMemory == MAP_FAILED) {
        exit(EXIT_FAILURE);
    }

    struct sync* sharedSync = (struct sync*) shMemory;
    struct payload* sharedPayload = (struct payload*)(shMemory + sizeof(struct sync));

    sharedSync->payloadOffset = sharedPayload;

    sem_init(&sharedSync->newWork, 1, 0);
    sem_init(&sharedSync->newResult, 1, 1);
    
    for(int i = 1; i <= count; i++) {
        sem_wait(&sharedSync->newResult);
        sharedPayload->work = i;
        printf("Producer: %d\n", i);
        sem_post(&sharedSync->newWork);
    }

    if (munmap(shMemory, size) == -1) {
        exit(EXIT_FAILURE);
    }

    if (close(shm_fd) == -1) {
        exit(EXIT_FAILURE);
    }
}

void consumer() {
    int shm_fd = shm_open("/sharedM", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        exit(EXIT_FAILURE);
    }    
    
    if (ftruncate(shm_fd, size) == -1) {
        exit(EXIT_FAILURE);
    }
    
    void* shMemory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shMemory == MAP_FAILED) {
        exit(EXIT_FAILURE);
    }
    struct sync* sharedSync = (struct sync*) shMemory;
    struct payload* sharedPayload = sharedSync->payloadOffset;
    
    for(int i = 1; i <= count; i++) {
        sem_wait(&sharedSync->newWork);
        sharedPayload->result = sharedPayload->work * sharedPayload->work;
        printf("Consumer: %d\n\n",sharedPayload->result);
        sem_post(&sharedSync->newResult);
    }

    if (munmap(shMemory, size) == -1) {
        exit(EXIT_FAILURE);
    }

    if (close(shm_fd) == -1) {
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    
    if(argc > 1) {
        count = atoi(argv[1]);
    } else {
        count = 1;
    }

    if(fork() == 0) {
        consumer();
    } else {
        producer();
    }

    return 0;
}