#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Максимален брой ребра в графа */
#define MAXM 2000

const unsigned n = 9;  /* Брой върхове в графа */
const unsigned m = 14; /* Брой на ребрата в графа */

typedef struct {
  unsigned i, j;
  int f;
} arc;

arc S[MAXM] = {  /* Списък от ребрата на графа и техните тегла */
  { 1, 2, 1 },
  { 1, 4, 2 },
  { 2, 3, 3 },
  { 2, 5, 13 },
  { 3, 4, 4 },
  { 3, 6, 3 },
  { 4, 6, 16 },
  { 4, 7, 14 },
  { 5, 6, 12 },
  { 5, 8, 1 },
  { 5, 9, 13 },
  { 6, 7, 1 },
  { 6, 9, 1 }
};

int prev[MAXN + 1];

int getRoot(int i)
{ int root, savei;
  /* намиране на корена на дървото */
  root = i;
  while (-1 != prev[root]) root = prev[root];
  /* свиване на пътя */
  while (i != root) {
    savei = i;
    i = prev[i];
    prev[savei] = root;
  }
  return root;
}

void kruskal(void)
{ int MST = 0;
  unsigned i, j;
  /* сортира списъка с ребрата в нарастващ ред по тяхното тегло */
  quickSort(A, 0, M);

  printf("Ето ребрата, които участват в минималното покриващо дърво:\n");
  for (i = 0; i < m; i++) {
    int r1 = getRoot(S[i].i);
    int r2 = getRoot(S[i].j);
    if (r1 != r2) {
      printf("(%u,%u) ", S[i].i, S[i].j);
      MST += S[i].f;
      prev[r2] = r1;
    }
  }
  printf("\nЦената на минималното покриващо дърво е %d.\n", MST);
}

int main(void) {
  unsigned i;
  for (i = 0; i < n + 1; i++) prev[i] = -1;
  kruskal();
  return 0;
}
