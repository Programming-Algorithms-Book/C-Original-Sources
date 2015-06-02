#include <stdio.h>

#define MAXN 10000
const unsigned n = 500;

unsigned primes[MAXN], pN = 0;

char isPrime(unsigned n)
{ unsigned i = 0;
  while (i < pN && primes[i] * primes[i] <= n) {
    if (n % primes[i] == 0) return 0;
    i++;
  }
  return 1;
}

void findPrimes(unsigned n)
{ unsigned i = 2;
  while (i < n) {
    if (isPrime(i)) {
      primes[pN] = i;
      pN++;
      printf("%5u", i);
    }
    i++;
  }
}

int main(void) {
  findPrimes(n);
  printf("\n");
  return 0;
}

