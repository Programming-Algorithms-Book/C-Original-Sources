#include <stdio.h>

/* Максимален размер на триъгълника */
#define MAXN 1000

unsigned n = 7;
unsigned k = 3;

unsigned long lastLine[MAXN + 1];

int main(void) {
  unsigned i, j;
  lastLine[0] = 1;
  for (i = 1; i <= n; i++) {
    lastLine[i] = 1;
    for (j = i - 1; j >= 1; j--)
      lastLine[j] += lastLine[j - 1];
  }
  printf("C(%u,%u) = %lu\n", n, k, lastLine[k]);
  return 0;
}
