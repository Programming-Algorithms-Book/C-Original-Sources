#include <stdio.h>
#define MAX   100
#define MAX2  MAX * (MAX + 1) / 2
#define INFINITY (unsigned)(-1)

unsigned p[MAX2];         /* Минимална цена за достигане на възел I */
unsigned pred[MAX2];      /* Предшественик на възел I в мин. път */

/* Цени за преминаване през върховете */
const unsigned v[MAX2] = {0,1,22,33,5,6,77,8,22,7,225,177,738,737,778,39,28,9,10,11,12,13};
const unsigned n = 6;             /* Брой редове в триъгълника */

void compare(unsigned ind1, unsigned ind2)
{ if (p[ind1] > p[ind2] + v[ind1]) {
    p[ind1] = p[ind2] + v[ind1];
    pred[ind1] = ind2;
  }
}

/* Намира минималния път до всеки възел */
void findMinPath(void)
{ unsigned i, j, sum;
  /* До първия връх се стига непосредствено */
  for (p[1] = v[1], sum = 0, i = 1; i <= n; i++) {
    for (j = 1; j <= i; j++) {
      if (j > 1)
		compare(sum + j + i - 1, sum + j);
      compare(sum + j + i, sum + j);
      compare(sum + j + i + 1, sum + j);
    }
    sum += i;
  }
}

/* Извежда триъгълника на минималните пътища на екрана */
void print(const unsigned m[])
{ unsigned i, j, sum;
  for (sum = 0, i = 1; i <= n; printf("\n"), sum += i++)
    for (j = 1; j <= i; j++)
	  printf("%8u", m[sum + j]);
}

/* Извежда минималния път до върха x */
void writePath(unsigned x)
{ printf("\n%s%u%s%u", "Пътят до връх номер ", x, " е минимален: ", p[x]);
  printf("\nПътят, изведен в обратен ред (индекси): ");
  while (x != 1) {
    printf("%u ", x);
    x = pred[x];
  }
  printf("1");
}

/* Намира връх от последния ред с минимален път */
void findMinLastRow(void)
{ unsigned i, minInd, end = n * (n + 1) / 2;
  for (i = 1 + (minInd = end-n+1); i <= end; i++)
    if (p[i] < p[minInd])
	  minInd = i;
  writePath(minInd);
}

int main(void) {
  unsigned i;
  for (i = 0; i < (n + 3)*(n + 2)/2; i++)
	p[i] = INFINITY;
  printf("Изходен триъгълник:\n"); print(v);
  findMinPath();
  printf("\nТриъгълник на минималните пътища:\n"); print(p);
  findMinLastRow();
  return 0;
}