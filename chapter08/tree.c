#include <stdio.h>
#define MAX 100
#define INFINITY (unsigned long)(-1)

unsigned long m[MAX][MAX];                      /* Таблица - целева функция */

const unsigned long f[MAX+1] = {2,7,1,3,4,6,5}; /* Честоти на срещане */
const unsigned n = 7;                           /* Брой честоти */

/* Построява оптимално двоично дърво за претърсване */
void solve(void)
{ unsigned i, j, k;
  unsigned long t;

  /* Инициализация */
  for (i = 1; i <= n; i++) {
    m[i][i] = f[i-1];
	m[i][i-1] = 0;
  }
  m[n+1][n] = 0;
  
  /* Основен цикъл */
  for (j = 1; j <= n - 1; j++) {
    for (i = 1; i <= n - j; i++) {
      m[i][i + j] = INFINITY;
      for (k = i; k <= i + j; k++) {
		/* Подобряваме текущото решение */
        if ((t = m[i][k - 1] + m[k + 1][i + j]) < m[i][i + j]) {
          m[i][i + j] = t;
          m[i + j + 1][i] = k;
        }
      }
      for (k = i-1; k < i + j; k++)
		m[i][i+j] += f[k];
    }
  }
}

/* Извежда матрицата на минимумите на екрана */
void PrintMatrix(void)
{ unsigned i,j;
  printf("\nМатрица на минимумите:");
  for (i = 1; i <= n+1; i++) {
    printf("\n");
    for (j = 1; j <= n; j++)
      printf("%8lu", m[i][j]);
  }
}

/* Извежда оптималното дърво на екрана */
void getOrder(unsigned ll, unsigned rr, unsigned h)
{ unsigned i;
  if (ll > rr)
	return;
  if (ll == rr) {
    for (i = 0; i < h; i++)
	  printf("   ");
    printf("d%u\n", rr);
  }
  else {
    getOrder(ll, m[rr + 1][ll] - 1, h + 1);
    for (i = 0; i < h; i++)
	   printf("   ");
    printf("d%lu\n", m[rr + 1][ll]);
    getOrder(m[rr + 1][ll] + 1, rr, h + 1);
  }
}

int main(void) {
   solve();
   printf("\nМинималната дължина на претегления вътрешен път е: %lu",m[1][n]);
   PrintMatrix();
   printf("\nОптимално дърво за претърсване:\n"); getOrder(1,n,0);
   return 0;
}