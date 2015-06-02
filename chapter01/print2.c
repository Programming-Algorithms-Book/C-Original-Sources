#include <stdio.h>
const unsigned n = 5;
unsigned k = 0;

void printRed(unsigned long result)
{ k++;
  printf("%lu ", result);
  if (k < n) printRed(result * 10);
  printf("%lu ", result);
}

int main(void) {
  printRed(10);
  printf("\n");
  return 0;
}
