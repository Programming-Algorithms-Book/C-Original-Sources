#include <stdio.h>

#define MAXN 500

unsigned long n = 7;
unsigned long k = 3;

unsigned long pN, primes[MAXN], counts[MAXN];

void modify(long int x, int how)
{ unsigned i;
  for (i = 0; i < pN; i++)
    if (x == primes[i]) { counts[i] += how; return; }
  counts[pN] = how;
  primes[pN++] = x;
}

void solve(unsigned long start, unsigned long end, unsigned long inc)
{ unsigned long prime, mul, how, i, max;
  for (i = start; i <= end; i++) {
    mul = i;
    prime = 2;
    while (mul != 1) {
      for (how = 0; mul % prime == 0; mul /= prime, how++);
      if (how > 0) modify(prime, inc * how);
      prime++;
    }
  }
}

long int calc(void)
{ int i, j;
  long int result = 1;
  for (i = 0; i < pN; i++)
    for (j = 0; j < counts[i]; j++) result *= primes[i];
  return result;
}

int main(void) {
  printf("C(%lu,%lu)= ", n, k);
  pN = 0;
  if (n - k < k) k = n - k;
  solve(n - k + 1, n, 1); /* Факторизира числителя (n–k+1),...,n */
  solve(1, k, -1);        /* Факторизира знаменателя 1,...,k */
  printf("%lu\n", calc());
  return 0;
}

