#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 150

/* Брой върхове в графа */
const unsigned n = 7;
const unsigned p = 3;  /* p-център */

/* Матрица на теглата на графа */
int A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 2, 0, 0 },
  { 1, 0, 4, 0, 0, 0, 0 },
  { 0, 4, 0, 3, 0, 5, 0 },
  { 0, 0, 3, 0, 4, 0, 8 },
  { 2, 0, 0, 4, 0, 0, 0 },
  { 0, 0, 5, 0, 0, 0, 2 },
  { 0, 0, 0, 8, 0, 2, 0 }
};

unsigned center[MAXN], pCenter[MAXN], pRadius;

const MAX_VALUE = 10000;

/* Намира дължината на минималния път между всяка двойка върхове */
void floyd(void)
{ unsigned i, j, k;
  /* стойностите 0 се променят на MAX_VALUE */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (A[i][j] == 0) A[i][j] = MAX_VALUE;
  /* Алгоритъм на Флойд */
  for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        if (A[i][j] > (A[i][k] + A[k][j]))
          A[i][j] = A[i][k] + A[k][j];

  for (i = 0; i < n; i++) A[i][i] = 0;
}

/* изчисляваме S за текущо генерираното подмножество */
void checkSol(void)
{ unsigned i, j, cRadius = 0;

  for (j = 0; j < n; j++) {
    int bT = MAX_VALUE;
    for (i = 0; i < p; i++)
      if (A[center[i]][j] < bT) bT = A[center[i]][j];
    if (cRadius < bT) cRadius = bT;
  }

  if (cRadius < pRadius) {
    pRadius = cRadius;
    for (i = 0; i < p; i++) pCenter[i] = center[i];
  }
}

/* комбинации C(n,p) – генериране на всички p-елементни подмножества на G */
void generate(unsigned k, unsigned last)
{ unsigned i;
  for (i = last; i < n - p + k; i++) {
    center[k] = i;
    if (k == p)
      checkSol();
    else
      generate(k + 1, i + 1);
  }
}

/* печатаме p-центъра и p-радиуса */
void printPCenter(void)
{ unsigned i;
  printf("%u-центъра в графа е следното множество от върхове: {", p);
  for (i = 0; i < p; i++) printf("%d ", pCenter[i] + 1);
  printf("}\n");
  printf("%u-радиуса в графа = %u\n", p, pRadius);
}

void main(void) {
  floyd();
  pRadius = MAX_VALUE;
  generate(0, 0);
  printPCenter();
}
