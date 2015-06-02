#include <stdio.h>

unsigned n = 7892;

void printN(unsigned n)
{ if (n >= 10) printN(n / 10);
  printf("%u ", n % 10);
}

int main() {
  printN(n); printf("\n");
  return 0;
}
