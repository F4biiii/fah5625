#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

struct sync {                                                                           // everything necessary for synchornizing
    sem_t newWork;
    sem_t newResult;
    void *payloadOffset;
};

struct payload {                                                                        // work and result for producer and consumer
    int work;
    int result;
};

int size = sizeof(struct sync) + sizeof(struct payload);
int count = 0;

void producer() {
    int shm_fd = shm_open("/sharedM", O_CREAT | O_RDWR, 0666);                          // create the shared memory
    ftruncate(shm_fd, size);                                                            // resize the shared memory
    void* shMemory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);   // map the sized memory to producer

    struct sync* sharedSync = (struct sync*) shMemory;                                  // place the struct sync to begin of shared memory
    struct payload* sharedPayload = (struct payload*)(shMemory + sizeof(struct sync));  // place the payload struct right after the sync struct

    sharedSync->payloadOffset = sharedPayload;                                          // safe the address of payload struct in sync struct

    sem_init(&sharedSync->newWork, 1, 0);                                               // initialize semaphore to release consumer, shared memory mode, value 0    
    sem_init(&sharedSync->newResult, 1, 1);                                             // initialize semaphore to release producer, shared memory mode, value 1 
    
    for(int i = 1; i <= count; i++) {                                                   
        sem_wait(&sharedSync->newResult);                                               // wait until consumer releases (not at the first time because value initially 1)
        sharedPayload->work = i;                                                        // place number in the payload
        printf("Producer: %d\n", i);                                                    // print it
        sem_post(&sharedSync->newWork);                                                 // release the consumer
    }

    munmap(shMemory, size);                                                             // unmap the shared memory
    close(shm_fd);                                                                      // close the shared memory
}

void consumer() {
    int shm_fd = shm_open("/sharedM", O_CREAT | O_RDWR, 0666);                          // create the shared memory            
    ftruncate(shm_fd, size);                                                            // resize the shared memory    
    void* shMemory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);   // map the sized memory to producer

    struct sync* sharedSync = (struct sync*) shMemory;                                  // producer put the struct sync to begin of shared memory, apply that knowledge
    struct payload* sharedPayload = sharedSync->payloadOffset;                          // consumer knows where the payload is (address is saved in sync->payloadOffset)
    
    for(int i = 1; i <= count; i++) {
        sem_wait(&sharedSync->newWork);                                                 // wait until producer releases
        sharedPayload->result = sharedPayload->work * sharedPayload->work;              // get number of payload->work, square it and put it in payload->result
        printf("Consumer: %d\n\n",sharedPayload->result);                               // print result
        sem_post(&sharedSync->newResult);                                               // release the producer
    }       

    munmap(shMemory, size);                                                             // unmap the shared memory
    close(shm_fd);                                                                      // close the shared memory

}

int main(int argc, char* argv[]) {
    
    if(argc > 1) {                  // progamm input (how many repetitions)                                                    
        count = atoi(argv[1]);
    } else {
        count = 1;                  // 1 if invalid
    }

    if(fork() == 0) {               // create two processes and distinguish between parent and child process
        consumer();
    } else {
        producer();
    }

    return 0;
}