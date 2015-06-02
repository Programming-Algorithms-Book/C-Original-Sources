#include <stdio.h>

const unsigned n = 10;

unsigned long factoriel(unsigned n)
{ unsigned i;
  unsigned long r = 1;
  for (i = 2; i <= n; i++) r *= i;
  return r;
}

int main() {
  printf("%u! = %lu\n", n, factoriel(n));
  return 0;
}