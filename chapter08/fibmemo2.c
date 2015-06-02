#include <stdio.h>
#include <string.h>

#define MAX 250
#define SQR(X) ((X)*(X))

unsigned long m[MAX+1];

const unsigned n = 10;

/* Бърз рекурсивен логаритмичен вариант, запаметяващ вече изчисленото */
unsigned long fMemo2(unsigned n)
{ if (n < 2)
    m[n] = 1;
  else if (0 == m[n])
    if (1 == n % 2)
      m[n] = fMemo2(n - 1) + fMemo2(n - 2);
    else
      m[n] = SQR(fMemo2(n / 2)) + SQR(fMemo2(n / 2 - 1));
  return m[n];
}

int main(void) {
  memset(m, 0, MAX * sizeof(m[0]));
  printf("\n%u-тото число на Фибоначи е: %lu", n, fMemo2(n - 1));
  return 0;
}
