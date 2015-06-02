#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 150

/* Брой върхове в графа */
const unsigned n = 9;
/* Матрица на теглата на графа */
const int A[MAXN][MAXN] = {
  { 0,  1, 0,  2,  0,  0,  0, 0,  0 },
  { 1,  0, 3,  0, 13,  0,  0, 0,  0 },
  { 0,  3, 0,  4,  0,  3,  0, 0,  0 },
  { 2,  0, 4,  0,  0, 16, 14, 0,  0 },
  { 0, 13, 0,  0,  0, 12,  0, 1, 13 },
  { 0,  0, 3, 16, 12,  0,  1, 0,  1 },
  { 0,  0, 0, 14,  0,  1,  0, 0,  0 },
  { 0,  0, 0,  0,  1,  0,  0, 0,  0 },
  { 0,  0, 0,  0, 13,  1,  0, 0,  0 }
};

const int MAX_VALUE = 10000;

char used[MAXN];
unsigned prev[MAXN];
int T[MAXN];

void prim(void)
{ int MST = 0;  /* в променливата ще натрупваме цената на минималното покриващо дърво */
  unsigned i, k;
  /* инициализация */
  for (i = 0; i < n; i++) { used[i] = 0; prev[i] = 0; }
  used[0] = 1;  /* избираме произволен начален връх */
  for (i = 0; i < n; i++)
    T[i] = (A[0][i]) ? A[0][i] : MAX_VALUE;
  for (k = 0; k < n - 1; k++) {
    /* търсене на следващо минимално ребро */
    int minDist = MAX_VALUE, j = -1;
    for (i = 0; i < n; i++)
      if (!used[i])
        if (T[i] < minDist) {
          minDist = T[i];
          j = i;
        }
    used[j] = 1;
    printf("(%u,%u) ", prev[j] + 1, j + 1);
    MST += minDist;
    for (i = 0; i < n; i++)
      if (!used[i] && A[j][i]) {
        if (T[i] > A[j][i]) {
          T[i] = A[j][i];
          /* запазване на предшественика, за евентуално отпечатване на следващо минимално ребро */
          prev[i] = j;
        }
      }
  }

  printf("\nЦената на минималното покриващо дърво е %d.\n", MST);
  printf("\n");
}

int main(void) {
  prim();
  return 0;
}
