#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 100

/* Брой върхове в графа */
const unsigned n = 8;
/* Матрица на съседство на графа */
char A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 0, 1, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0 }
};

/* Проверява дали е възможно да има Ойлеров цикъл (по теоремата на Ойлер) */
char isEulerGraph(void)
{ unsigned i, j;
  for (i = 0; i < n; i++) {
    int din = 0, dout = 0;
    for (j = 0; j < n; j++) {
      if (A[i][j]) din++;
      if (A[j][i]) dout++;
    }
    if (din != dout) return 0;
  }
  return 1;
}

/* Намира Ойлеров цикъл */
void findEuler(int i)
{ unsigned cStack[MAXN * MAXN], stack[MAXN * MAXN];
  unsigned k, j, cTop = 0, sTop = 1;
  stack[sTop] = i;
  while (sTop > 0) {
    i = stack[sTop];
    for (j = 0; j < n; j++)
      if (A[i][j]) {
        A[i][j] = 0; i = j;
        break;
      }
    if (j < n)
      stack[++sTop] = i;
    else
      cStack[++cTop] = stack[sTop--];
  }
  printf("Ойлеровият цикъл е: ");
  for (k = cTop; k > 0; k--) {
    printf("%u ", cStack[k] + 1);
  }
  printf("\n");
}

int main(void) {
  if (isEulerGraph()) findEuler(0);
  else
    printf("Графът не е Ойлеров!");
  return 0;
}
