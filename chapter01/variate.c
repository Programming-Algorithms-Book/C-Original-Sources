#include <stdio.h>

#define MAXN 100

/* Вариации на n елемента от клас k */
const unsigned n = 4;
const unsigned k = 2;

int taken[MAXN];

void print(unsigned i)
{ unsigned k;
  printf("( ");
  for (k = 0; k <= i - 1; k++) printf("%u ", taken[k] + 1);
  printf(")\n");
}

/* рекурсия */
void variate(unsigned i)
{ unsigned j;
  /* без if (i>=k) и return; тук (а само print(i); ако искаме всички
   * генерирания с дължина 1,2, …, k, а не само вариациите с дължина k */
  if (i >= k) { print(i); return; }
  for (j = 0; j < n; j++) {
    /* if (allowed(k)) { */
    taken[i] = j;
    variate(i + 1);
  }
}

int main(void) {
  variate(0);
  return 0;
}

