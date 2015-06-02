#include <stdio.h>
#include <math.h>
#define MAX 80
#define INFINITY 1e20

double d[MAX][MAX];   /* Разстояния между върховете */
double m[MAX][MAX];   /* Таблица - целева функция */

const struct {        /* Координати на върховете */
  int x;
  int y;
} coord[MAX] = {{1,1},{5,-2},{10,1},{7,7},{1,7}};
const unsigned n = 5; /* Брой върхове */

/* Пресмята разстоянията между всички двойки върхове */
void calcDist(void)
{ unsigned i, j;
  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++)
      d[i][j] = sqrt((coord[i].x - coord[j].x) * (coord[i].x - coord[j].x) +
                     (coord[i].y - coord[j].y) * (coord[i].y - coord[j].y));
}

/* Формира таблица, съдържаща минималния брой умножения, необходими за
 * умножението на всяка двойка матрици, както и индексът, за който се постига */
void solve(void)
{ unsigned i, j, k;
  for (i = 1; i < n; i++)
	 m[i][i] = 0; /* Инициализация */
  for (j = 1; j < n; j++) {            /* Основен цикъл */
    for (i = 1; i < n - j; i++) {
      m[i][i + j] = INFINITY;
      for (k = i; k < i + j; k++) {
        double t = m[i][k] +
          m[k+1][i+j] +
          d[i-1][k] +
          d[k][i+j] +
          d[i-1][i+j];
        if (t < m[i][i+j]) {          /* Подобряване на текущото решение */
          m[i][i+j] = t;
          m[i+j][i] = k;
        }
      }
    }
  }
}

/* Отпечатване на резултата */
void printResult(void)
{ unsigned i;
  double p = d[0][n-1];  /* Пресмятаме периметъра */
  for (i = 0; i < n; i++)
	 p += d[i][i+1];
  printf("\nДължината на минималния разрез е %.2lf", (m[1][n-1] - p) / 2);
}

/* Извеждане на минималния разрез на екрана */
void writeCut(unsigned ll, unsigned rr)
{ if (ll != rr) {
    writeCut(ll, (unsigned) m[rr][ll]);
    writeCut((unsigned) m[rr][ll] + 1, rr);
    if (ll != 1 || rr != n-1)
	  printf("(%u,%u) ", ll, rr + 1);
  }
}

int main(void) {
  calcDist();
  solve();
  printResult();
  printf("\nДиагонали от минималния разрез: ");
  writeCut(1, n-1);
  return 0;
}