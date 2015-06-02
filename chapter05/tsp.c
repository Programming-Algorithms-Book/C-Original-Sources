#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 150

/* Брой върхове в графа */
const unsigned n = 6;
/* Матрица на теглата на графа */
const int A[MAXN][MAXN] = {
  { 0, 5, 0, 0, 7, 7 },
  { 5, 0, 5, 0, 0, 0 },
  { 0, 5, 0, 6, 5, 0 },
  { 0, 0, 6, 0, 3, 3 },
  { 7, 0, 5, 3, 0, 5 },
  { 7, 0, 0, 3, 5, 0 }
};

const int MAX_VALUE = 10000;

char used[MAXN];
unsigned minCycle[MAXN], cycle[MAXN];
int curSum, minSum;

void printCycle(void)
{ unsigned i;
  printf("Минимален Хамилтонов цикъл: 1");
  for (i = 0; i < n - 1; i++) printf(" %u", minCycle[i] + 1);
  printf(" 1, дължина %d\n", minSum);
}

/* Намира минимален Хамилтонов цикъл */
void hamilton(unsigned i, unsigned level)
{ unsigned k;
  if ((0 == i) && (level > 0)) {
    if (level == n) {
      minSum = curSum;
      for (k = 0; k < n; k++) minCycle[k] = cycle[k];
    }
    return;
  }
  if (used[i]) return;
  used[i] = 1;
  for (k = 0; k < n; k++)
    if (A[i][k] && k != i) {
      cycle[level] = k;
      curSum += A[i][k];
      if (curSum < minSum) /* прекъсване на генерирането */
        hamilton(k, level + 1);
      curSum -= A[i][k];
    }
  used[i] = 0;
}

int main(void) {
  unsigned k;
  for (k = 0; k < n; k++) used[k] = 0;
  minSum = MAX_VALUE;
  curSum = 0;
  cycle[0] = 1;
  hamilton(0, 0);
  printCycle();
  return 0;
}
