#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 6;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 1, 1, 0, 1, 0 },
  { 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 1 },
  { 0, 1, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0 }
};

unsigned cover[MAXN];
char T[MAXN];

void printSet(void)
{ unsigned i;
  printf("{ ");
  for (i = 0; i < n; i++)
    if (T[i]) printf("%u ", i + 1);
  printf("}\n");
}

char ok(void)
{ unsigned i, j;
  for (i = 0; i < n; i++) if (T[i]) {
    /* проверка дали покритието се запазва при премахване на връх i */
    if (0 == cover[i]) continue;
    for (j = 0; j < n; j++) if (cover[j]) {
      if (!(cover[j] - A[i][j]) && !T[j]) break; /* съществува връх, който остава непокрит */
    }
    if (j == n) return 0;
  }
  return 1;
}

void findMinDom(unsigned last)
{ unsigned i, j;
  /* проверява се дали е намерено решение */
  for (i = 0; i < n; i++)
    if (!cover[i] && !T[i]) break;
  if (i == n) { printSet(); return; }
  /* не - продължаваме да конструираме доминиращото множество */
  for (i = last; i < n; i++) {
    T[i] = 1;
    for (j = 0; j < n; j++) if (A[i][j]) cover[j]++;
    if (ok()) findMinDom(i + 1);
    for (j = 0; j < n; j++) if (A[i][j]) cover[j]--;
    T[i] = 0;
  }
}

void main(void)
{ unsigned i;
  printf("Минималните доминиращи множества в графа са: \n");
  for (i = 0; i < n; i++) { cover[i] = 0; T[i] = 0; }
  findMinDom(0);
}
