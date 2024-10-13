#include <stdio.h>
#include <pthread.h>

int isPrime(int a) {
    int i;
    for(i = 2; i < a-1; i++) {
        if(a % i == 0) {
            return 0;
        } 
    }
    return 1;
}

int main (void) {
    int i;
    for(i = 1; i < 1000000; i++) {
        if(isPrime(i)) {
            printf("%d\n", i);
        }
    }
    return 0;
}