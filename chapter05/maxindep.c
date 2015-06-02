#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 8;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 1, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 1, 0, 1, 0, 0 },
  { 1, 1, 0, 0, 1, 0, 1, 1 },
  { 0, 0, 0, 1, 0, 1, 0, 0 },
  { 1, 0, 0, 0, 0, 1, 0, 0 }
};

unsigned S[MAXN], T[MAXN], sN, tN;

void print(void)
{ unsigned i;
  printf("{ ");
  for (i = 0; i < n; i++)
    if (T[i]) printf("%u ", i + 1);
  printf("} \n");
}

void maxSubSet(unsigned last)
{ unsigned i, j;
  if (sN + tN == n) {
    print(); /* SuT=V -> отпечатва се решението */
    return;
  }
  for (i = last; i < n; i++) {
    if (!S[i] && !T[i]) {
      for (j = 0; j < n; j++)
        if (A[i][j] && !S[j]) {
          S[j] = last+1; sN++;
        }
      T[i] = 1; tN++;
      maxSubSet(i+1);     /* рекурсия */
      T[i] = 0; tN--;
      for (j = 0; j < n; j++)
        if (S[j] == last+1) { S[j] = 0; sN--; }
    }
  }
}

void main(void) {
  unsigned i;
  printf("Ето всички максимални независими множества в графа:\n");
  sN = tN = 0;
  for (i = 0; i < n; i++) S[i] = T[i] = 0;
  maxSubSet(0);
}
