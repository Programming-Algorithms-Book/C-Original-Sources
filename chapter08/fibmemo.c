#include <stdio.h>
#include <string.h>

#define MAX 256

const unsigned n = 10; /* търсим 10-тото число на Фибоначи */

unsigned long m[MAX + 1];

/* Бърз рекурсивен линеен вариант, запаметяващ вече пресметнатото */
unsigned long fibMemo(unsigned n) 
{ if (n < 2)
    m[n] = n;
  else if (0 == m[n])
    m[n] = fibMemo(n - 1) + fibMemo(n - 2);
  return m[n];
}

int main(void) {
  memset(m, 0, MAX * sizeof(*m));
  printf("\n%u-тото число на Фибоначи е: %lu", n, fibMemo(n));
  return 0;
}
