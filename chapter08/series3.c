#include <stdio.h>

#define MAX 100
#define NOT_CALCULATED (-1)
#define q (1 - (p))                 /* Вероятност B да спечели отделен мач */
const float p = 0.5;                /* Вероятност A да спечели отделен мач */
const unsigned n = 5;

float PS[MAX][MAX];

float pDyn(unsigned i, unsigned j)  /* Динамично оптимиране */
{ if (PS[i][j] < 0)
    PS[i][j] = p * pDyn(i - 1, j) + q * pDyn(i, j - 1);
  return PS[i][j];
}

float pDynamic2(unsigned i, unsigned j)
{ unsigned k, l;
  for (k = 1; k <= i; k++)
    for (l = 1; l <= j; l++)
       PS[k][l] = NOT_CALCULATED;
  for (k = 1; k <= i; k++) 
    PS[k][0] = 0.0;
  for (k = 1; k <= j; k++)
    PS[0][k] = 1.0;

  return pDyn(i, j);
}

int main(void) {
  unsigned  i, j;
  pDynamic2(n,n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%f ", PS[i][j]);
    printf("\n");
  }
  return 0;
}