#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 5;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 1 },
  { 1, 0, 1, 1, 1 },
  { 0, 1, 0, 1, 0 },
  { 0, 1, 1, 0, 1 },
  { 1, 1, 0, 1, 0 }};

unsigned col[MAXN], maxCol, count = 0;
char foundSol = 0;

void showSol(void)
{ unsigned i;
  count++;
  printf("Минимално оцветяване на графа: \n");
  for (i = 0; i < n; i++) printf("Връх %u - с цвят %u \n", i + 1, col[i]);
}

void nextCol(unsigned i)
{ unsigned k, j, success;
  if (i == n) { showSol(); return; }
  for (k = 1; k <= maxCol; k++) {
    col[i] = k;
    success = 1;
    for (j = 0; j < n; j++)
      if (1 == A[i][j] && col[j] == col[i]) {
        success = 0;
        break;
      }
    if (success) nextCol(i + 1);
    col[i] = 0;
  }
}

int main(void) {
  unsigned i;
  for (maxCol = 1; maxCol <= n; maxCol++) {
    for (i = 0; i < n; i++) col[i] = 0;
    nextCol(0);
    if (count) break;
  }
  printf("Общ брой намерени оцветявания с %u цвята: %u \n", maxCol, count);
  return 0;
}
