#include <stdio.h>
#include <omp.h>

#define MAX 10010000

int count = 10000000;                                                                   // current iteration (initial value is start of iteration)
int foundPrimes = 0;                                                                    // found primes
int numThreads = 0;

int main(int argc, char** argv) {

    #pragma omp parallel
    {
        numThreads = omp_get_num_threads();

        int countCpy;                                                                   // copy the global variable count in each iteration
        int threadPrimes = 0;                                                           // number of primes found by a single thread
        while(count <= MAX) {                                                            // iterate over given area
            #pragma omp critical                                                        
            {
                countCpy = count++;                                                     // increase global variable count
            }
            int prime = 1;                                                              
            for(int i = 2; i < countCpy; i++) {                                                            
                if(countCpy % i == 0) {                                                             // if the checked number can be divided by any other number (from 2 - checked number) without rest
                    prime = 0;                                                                      // checked number is no prime
                    break;                                                                          // stop checking 
                }
            }
            if(prime) {      
                printf("%d\n", countCpy);                                     
                threadPrimes++;                                                                      // increase threads found primes
            }
        }
        #pragma omp critical
        {
            foundPrimes += threadPrimes;                                                            // add up the found primes of each thread
        }
    }

    printf("\nTotal primes: %d\n", foundPrimes);
    printf("Calculated by %d Thread(s)\n\n", numThreads);
    return 0;
}