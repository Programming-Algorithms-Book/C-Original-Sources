#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 6;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 1, 1, 0, 0, 0 },
  { 1, 0, 1, 0, 0, 0 },
  { 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 1 },
  { 0, 0, 0, 1, 0, 1 },
  { 0, 0, 0, 1, 1, 0 }
};

char used[MAXN];

/* модифицирано DFS */
void DFS(unsigned i)
{ unsigned k;
  used[i] = 1;
  printf("%u ", i + 1);
  for (k = 0; k < n; k++)
    if (A[i][k] && !used[k]) DFS(k);
}

int main(void) {
  unsigned i, comp;
  /* инициализация */
  for (i = 0; i < n; i++) used[i] = 0;
  printf("\nЕто всички компоненти на свързаност: \n");
  comp = 0;
  for (i = 0; i < n; i++)
    if (!used[i]) {
      comp++;
      printf("{ ");
      DFS(i);
      printf("}\n");
    }
  if (1 == comp)
    printf("Графът е звързан.\n");
  else
    printf("Брой на свързаните компоненти в графа: %d \n", comp);
  return 0;
}
