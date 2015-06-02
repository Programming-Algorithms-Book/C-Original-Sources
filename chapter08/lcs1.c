#include <stdio.h>
#include <string.h>
#define MAXN 100
#define MAX(a, b) (((a) > (b)) ? (a) : (b)) /* Връща по-големия аргумент */

char F[MAXN][MAXN];               /* Целева функция */

const char x[MAXN] = "acbcacbcaba";    /* Първа редица */
const char y[MAXN] = "abacacacababa";  /* Втора редица */

/* Намира дължината на най-дългата обща подредица */
unsigned LCS_Length(void)
{ unsigned i, j, m, n;
  m = strlen(x);  /* Дължина на първата редица */
  n = strlen(y);  /* Дължина на втората редица */
  /* Начална инициализация */
  for (i = 1; i <= m; i++)
	F[i][0] = 0;
  for (j = 0; j <= n; j++)
	F[0][j] = 0;
  /* Основен цикъл */
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++)
      if (x[i - 1] == y[j - 1])
        F[i][j] = F[i - 1][j - 1] + 1;
      else
        F[i][j] = MAX(F[i - 1][j], F[i][j - 1]);
  return F[m][n];
}

int main(void) {
  printf("\nДължина на най-дългата обща подредица: %u", LCS_Length());
  return 0;
}
