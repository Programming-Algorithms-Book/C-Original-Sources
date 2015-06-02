#include <stdio.h>

const unsigned n = 10;

int main(void) {
  unsigned zeroes = 0, p = 5;
  while (n >= p) {
    zeroes += n / p;
    p *= 5;
  }
  printf("Броят на нулите в края на %u! е %u\n", n, zeroes);
  return 0;
}
