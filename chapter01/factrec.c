#include <stdio.h>

const unsigned n = 6;

unsigned i;
unsigned long fact(void)
{ if (i == 1) return 1;
  return --i * fact();
}

int main(void) {
  i = n + 1;
  printf("%u! = %lu \n", n, fact());
  return 0;
}
