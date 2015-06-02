// da oprawq w teksta
// fib(7) dawaha razlichno - da checkna koe e po definiciqta!!!
#include <stdio.h>

const unsigned n = 7;

unsigned long fib(unsigned n)
{ if (n < 2) return 1;
    else return fib(n - 1) + fib(n - 2);
}

int main() {
  printf("fib(%u) = %lu\n", n, fib(n));
  return 0;
}
