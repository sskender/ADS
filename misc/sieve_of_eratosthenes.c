/* https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes */
#include <stdio.h>

#define MAX 1000


int main(void) {
    int i, j;
    int primes[MAX+1];

    /* initial setup */
    primes[0] = 0;
    primes[1] = 0;
    for(i = 2; i <= MAX; i++) {
        primes[i] = 1;                          /* assume all numbers are prime in the start */
    }

    /* find primes */
    for(i = 2; i <= MAX; i++) {
        if (primes[i]) {
            for(j = 2; i * j <= MAX; j++) {     /* find multiples */
                primes[i * j] = 0;      
            }
        }
    }

    /* display primes */
    for(i = 0; i <= MAX; i++) {
        if (primes[i]) {
            printf("%5d ", i);
        }
    }

    return 0;
}
