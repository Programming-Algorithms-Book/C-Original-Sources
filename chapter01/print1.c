#include <stdio.h>
const unsigned n = 5;

void printRed(unsigned k, unsigned long result)
{ printf("%lu ", result);
  if (k < n) printRed(k + 1, result * 10);
  printf("%lu ", result);
}

int main(void) {
  printRed(1, 10);
  printf("\n");
  return 0;
}
