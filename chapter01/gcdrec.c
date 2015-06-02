#include <stdio.h>

const unsigned a = 28;
const unsigned b = 49;

unsigned gcd(unsigned a, unsigned b)
{ return (b == 0) ? a : gcd(b, a % b);
}

int main(void) {
  printf("NOD(%u,%u) = %u\n", a, b, gcd(a, b));
  return 0;
}
