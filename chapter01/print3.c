#include <stdio.h>
const unsigned n = 5;
unsigned long result = 1;
unsigned k = 0;

void printRed(void)
{ k++;
  result *= 10;
  printf("%lu ", result);
  if (k < n) printRed();
  printf("%lu ", result);
  result /= 10;
}

int main(void) {
  printRed();
  printf("\n");
  return 0;
}
