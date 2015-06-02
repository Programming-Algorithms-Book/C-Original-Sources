#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 5;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 1 },
  { 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 }
};

char used[MAXN];

/* модифицирано DFS */
void DFS(unsigned i)
{ unsigned k;
  used[i] = 1;
  for (k = 0; k < n; k++)
    if (A[i][k] && !used[k]) DFS(k);
  printf("%u ", i + 1);
}

int main(void) {
  unsigned i;
  /* инициализация */
  for (i = 0; i < n; i++) used[i] = 0;
  printf("Топологично сортиране (в обратен ред): \n");
  for (i = 0; i < n; i++)
    if (!used[i]) DFS(i);
  printf("\n");
  return 0;
}
