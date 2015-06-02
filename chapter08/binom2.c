#include <stdio.h>

#define MAX 200

/* Динамично оптимиране */
unsigned long m[MAX];
unsigned long binomDynamic(unsigned n, unsigned k)
{ unsigned i, j;
  for (i = 0; i <= n; i++) {
    m[i] = 1;
    if (i > 1) {
      if (k < i - 1) j = k; else j = i - 1;
      for (; j >= 1; j--) m[j] += m[j - 1];
    }
  }
  return m[k];
}

int main(void) {
  printf("%lu\n", binomDynamic(7,3));
  return 0;
}