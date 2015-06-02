#include <stdio.h>
#define MAX 100
#define NOT_SOLVED (unsigned long)(-1)

unsigned long m[MAX][MAX];    /* Таблица - целева функция */

const unsigned long r[MAX+1] = {12,13,35,3,34,2,21,10,21,6}; /* Размерности на матриците */
const unsigned n = 9;         /* Брой матрици */

long solveMemo(unsigned i, unsigned j)
{ unsigned k;
  unsigned long q;
  if (NOT_SOLVED != m[i][j]) /* Стойността вече е била пресметната */
    return m[i][j];
  if (i == j)                /* В този интервал няма матрица */
    m[i][j] = 0;
  else {                     /* Пресмятаме рекурсивно */
    for (k = i; k <= j - 1; k++)
      if ((q = solveMemo(i, k) + solveMemo(k + 1, j) + r[i-1] * r[k] * r[j]) < m[i][j])
		m[i][j] = q;
  }
  return m[i][j];
}

long solveMemoization(void)
{ unsigned i, j;
  for (i = 1; i <= n; i++)
    for (j = i; j <= n; j++)
	  m[i][j] = NOT_SOLVED;
  return solveMemo(1, n);
}

void printMatrix(void) /* Извежда матрицата на минимумите на екрана */
{ unsigned i,j;
  printf("\nМатрица на минимумите:");
  for (i = 1; i <= n; i++) {
    printf("\n");
    for (j = 1; j <= n; j++)
      printf("%8lu", m[i][j]);
  }
}

int main(void) {
  printf("\nМинималният брой умножения е: %lu", solveMemoization());
  printMatrix();
  return 0;
}
