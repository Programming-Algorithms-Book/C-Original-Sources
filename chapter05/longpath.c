#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 150

/* Брой върхове в графа */
const unsigned n = 6;
/* Матрица на теглата на графа */
const unsigned A[MAXN][MAXN] = {
  { 0, 12,  0, 0,  0,  0 },
  { 0,  0, 40, 0, 17,  0 },
  { 0,  0,  0, 0,  0,  0 },
  { 0,  0,  0, 0, 30,  0 },
  { 0,  0,  0, 0,  0, 20 },
  { 0,  0, 20, 0,  0,  0 }
};

int savePath[MAXN], maxDist[MAXN];

void DFS(unsigned i)
{ int max, d;
  unsigned j;
  if (maxDist[i] > 0) return;
  max = maxDist[i];
  for (j = 0; j < n; j++)
    if (A[i][j]) {
      DFS(j);
      d = maxDist[j] + A[i][j];
      if (d > max) {
        max = d;
        savePath[i] = j;
      }
    }

  maxDist[i] = max;
}

void solve(void)
{ unsigned i, maxi;
  /* инициализация */
  for (i = 0; i < n; i++) {
    maxDist[i] = 0;
    savePath[i] = -1;
  }

  for (i = 0; i < n; i++)
    if (maxDist[i] == 0) DFS(i);

  maxi = 0;
  for (i = 0; i < n; i++)
    if (maxDist[i] > maxDist[maxi]) maxi = i;

  printf("Дължината на критичния път е %d\nПътят е: ", maxDist[maxi]);
  while (savePath[maxi] >= 0) {
    printf("%d ", maxi + 1);
    maxi = savePath[maxi];
  }

  printf("%u\n", maxi + 1);
}

int main(void) {
  solve();
  return 0;
}
