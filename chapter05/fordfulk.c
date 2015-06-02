#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 100

const unsigned n = 10; /* Брой върхове в графа */
const unsigned s = 1;  /* Връх източник */
const unsigned t = 6;  /* Връх консуматор */
/* Матрица на теглата на графа */
int A[MAXN][MAXN] = {
  { 0, 5, 5, 10, 0, 0 },
  { 0, 0, 4, 0, 0, 5 },
  { 0, 9, 0, 0, 7, 0 },
  { 0, 0, 0, 0, 0, 7 },
  { 0, 0, 0, 0, 0, 8 },
  { 0, 0, 0, 0, 0, 0 }
};

const int MAX_VALUE = 10000;

int F[MAXN][MAXN];
unsigned path[MAXN];
char used[MAXN], found;

void updateFlow(unsigned pl)
{ int incFlow = MAX_VALUE;
  unsigned i;
  for (i = 0; i < pl; i++) {
    unsigned p1 = path[i];
    unsigned p2 = path[i + 1];
    if (incFlow > A[p1][p2]) incFlow = A[p1][p2];
  }
  for (i = 0; i < pl; i++) {
    unsigned p1 = path[i];
    unsigned p2 = path[i + 1];
    F[p1][p2] += incFlow;
    F[p2][p1] -= incFlow;
    A[p1][p2] -= incFlow;
    A[p2][p1] += incFlow;
  }
}

void DFS(unsigned i, unsigned level)
{ unsigned k;
  if (found) return;
  if (i == t-1) {
    found = 1;
    updateFlow(level - 1);
  }
  else
    for (k = 0; k < n; k++)
      if (!used[k] && A[i][k] > 0) {
        used[k] = 1;
        path[level] = k;
        DFS(k, level + 1);
        if (found) return;
      }
}

int main(void) {
  unsigned i, j;
  int flow;

  /* 1) инициализира се празен поток */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) F[i][j] = 0;

  /* 2) намира увеличаващ път, докато е възможно */
  do {
    for (i = 0; i < n; i++) used[i] = 0;
    found = 0;
    used[s-1] = 1;
    path[0] = s-1;
    DFS(s-1, 1);
  } while (found);

  /* Отпечатва потока */
  printf("Максимален поток през графа : \n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) printf("%4d", F[i][j]);
    printf("\n");
  }

  printf("\n");

  flow = 0;
  for (i = 0; i < n; i++) flow += F[i][t-1];
  printf("С големина : %d\n", flow);
  return 0;
}
