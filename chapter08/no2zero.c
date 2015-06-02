#include <stdio.h>
#define MAX         100
#define NOT_SOLVED  (unsigned long)(-1)

unsigned long F[MAX];   /* Целева функция */
unsigned long pow[MAX]; /* Степените на k */

const unsigned n = 10;
const unsigned k = 7;

void init(void)
{ unsigned i;
  for (i = pow[0] = 1; i <= n; i++) {
    pow[i] = k * pow[i - 1];
    F[i] = NOT_SOLVED;
  }
}

unsigned long solve(unsigned s)
{ unsigned i;
  if (NOT_SOLVED == F[s]) {
    F[s] = pow[s - 2];
    for (i = 1; i < s - 1; i++)
      F[s] += solve(i - 1) * (k - 1) * pow[s - i - 2];
    F[s] = pow[s] - F[s];
  }
  return F[s];
}

int main(void) {
  init();
  F[0] = 1; F[1] = k; F[2] = k * k - 1;
  printf("%lu\n", (k - 1) * solve(n - 1));
  return 0;
}