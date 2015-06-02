#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 9;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0, 0 }
};

char used[MAXN], base[MAXN];

void DFS(unsigned i)
{ unsigned k;
  used[i] = 1;
  for (k = 0; k < n; k++)
    if (A[i][k] && !used[k]) {
      base[k] = 0;
      DFS(k);
    }
}

void solve(void) {
  unsigned i, j;
  for (i = 0; i < n; i++) base[i] = 1;
  for (i = 0; i < n; i++)
    if (base[i]) {
      for (j = 0; j < n; j++) used[j] = 0;
      DFS(i);
    }
}

void print() {
  unsigned i, count = 0;
  printf("Ето върховете, образуващи база в графа:\n");
  for (i = 0; i < n; i++)
    if (base[i]) { printf("%u ", i + 1); count++; }
  printf("\nБрой на върховете в базата: %u\n", count);
}

int main(void) {
  solve();
  print();
  return 0;
}
