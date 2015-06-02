#include <stdio.h>

/* Неефективен рекурсивен вариант */
unsigned long binom(unsigned n, unsigned k) 
{ if (k > n) return 0;
    else if (0 == k || k == n) return 1;
    else return binom(n-1, k-1) + binom(n-1, k);
}

int main(void) {
  printf("%lu\n", binom(7,3));
  return 0;
}

