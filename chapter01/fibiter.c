//n->const, FibIter -> fibIter
#include <stdio.h>

const unsigned n = 7;

unsigned long fibIter(unsigned n)
{ unsigned long f1 = 0, f2 = 1;
  unsigned i = 0;
  while (i < n) {
    f2 = f1 + f2;
    f1 = f2 - f1;
    i++;
  }
  return f2;
}

int main() {
  printf("fib(%u) = %lu\n", n, fibIter(n));
  return 0;
}
