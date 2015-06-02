#include <stdio.h>
#define MAX 100

unsigned long M[MAX][MAX];  /* Целева функция */

const unsigned n = 10;

/* Намира броя на представянията на n като сума от естествени числа */
unsigned long getNum(unsigned n)
{ unsigned i, j;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (1 == j)
        M[i][j] = 1;
      else if (1 == i)
        M[i][j] = 1;
      else if (i < j)
        M[i][j] = M[i][i];
      else if (i == j)
        M[i][j] = 1 + M[i][i - 1];
      else
        M[i][j] = M[i][j - 1] + M[i - j][j];
  return M[n][n];
}

int main(void)
{ 
  printf("Броят на представянията на %u като сума от естествени числа е: %lu",
         n, getNum(n));
  return 0;
}