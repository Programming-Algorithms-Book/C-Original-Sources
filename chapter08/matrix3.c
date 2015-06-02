#include <stdio.h>
#define MAX 100
#define INFINITY (unsigned long)(-1)

unsigned long m[MAX][MAX];    /* Таблица - целева функция */
struct {
  unsigned left, right;
} order[MAX * MAX];           /* Ред на умножение на матриците */
unsigned long cnt;            /* Брой действия за пресмятането */

const unsigned long r[MAX+1] = {12,13,35,3,34,2,21,10,21,6}; /* Размерности на матриците */
const unsigned n = 9;         /* Брой матрици */

/* Формира таблица, съдържаща минималния брой умножения, необходими за
 * умножението на всяка двойка матрици, както и индексът, за който се постига */
void solve(void)
{ unsigned i, j, k;
  /* Инициализация */
  for (i = 1; i <= n; i++)
	m[i][i] = 0; 
  /* Основен цикъл */
  for (j = 1; j <= n; j++) {            
    for (i = 1; i <= n - j; i++) {
      m[i][i + j] = INFINITY;
      for (k = i; k < i + j; k++) {
        unsigned long t = m[i][k] + m[k + 1][i + j] + r[i-1] * r[k] * r[i + j];
		/* Подобряване на текущото решение */
        if (t < m[i][i + j]) {          
          m[i][i + j] = t;
          m[i + j][i] = k;
        }
      }
    }
  }
}

unsigned buildOrder(unsigned ll, unsigned rr) /* Формира алгоритъм за умножение */
{ long ret = cnt++;
  if (ll < rr) {
    order[ret].left = buildOrder(ll, m[rr][ll]);
    order[ret].right = buildOrder(m[rr][ll] + 1, rr);
  }
  else {
    order[ret].left = ll;
    order[ret].right = rr;
  }
  return ret;
}

void printMatrix(void) /* Извежда матрицата на минимумите на екрана */
{ unsigned i, j;
  printf("\nМатрица на минимумите :");
  for (i = 1; i <= n; i++) {
    printf("\n");
    for (j = 1; j <= n; j++)
	   printf("%8lu", m[i][j]);
  }
}

void printMultiplyPlan(void) /* Извежда план за умножение на матриците */
{ unsigned long i;
  printf("\nПлан за умножение на матриците:");
  for (i = 0; i < cnt; i++) {
    if (order[i].left == order[i].right)
      printf("\nL[%lu] = M%u", i, order[i].left);
    else
      printf("\nL[%lu] = L[%u] * L[%u]", i, order[i].left, order[i].right);
  }
}

void getOrder(unsigned ll, unsigned rr) /* Изразява реда на умножение с помощта на скоби */
{ if (ll == rr)
    printf("M%u", ll);
  else {
    printf("(");
    getOrder(ll, m[rr][ll]);
    printf("*");
    getOrder(m[rr][ll] + 1, rr);
    printf(")");
  }
}

int main(void) {
  solve();
  cnt = 0;
  buildOrder(1, n);
  printf("\nМинималният брой умножения е: %lu", m[1][n]);
  printMatrix();
  printMultiplyPlan();
  printf("\nРед на умножение на матриците: ");
  getOrder(1, n);
  return 0;
}