#include <stdio.h>

const unsigned a = 28;
const unsigned b = 49;

unsigned gcd(unsigned a, unsigned b)
{ unsigned swap;
  while (b > 0) {
    swap = b;
    b = a % b;
    a = swap;
  }
  return a;
}

int main(void) {
  printf("NOD(%u,%u) = %u\n", a, b, gcd(a, b));
  return 0;
}
