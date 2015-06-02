#include <stdio.h>

#define MAX 100
#define q (1 - (p))                 /* Вероятност B да спечели отделен мач */
const float p = 0.5;                /* Вероятност A да спечели отделен мач */
const unsigned n = 5;

float pDynamic3(unsigned i, unsigned j)
{ float P[MAX][MAX];
  unsigned s, k;
  P[0][0] = 0.0; /* Това е излишно. Не ни трябва */
  for (s = 1; s <= i + j; s++) {
    P[0][s] = 1.0;
    P[s][0] = 0.0;
    for (k = 1; k <= s - 1; k++)
      P[k][s - k] = p * P[k - 1][s - k] + q * P[k][s - k - 1];
  }
  return P[i][j];
}

int main(void) {
  unsigned  i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%f ", pDynamic3(i,j));
    printf("\n");
  }
  return 0;
}