#include <stdio.h>
#define  MAXN 30           /* Максимален брой предмети */
#define  MAXM 1000         /* Максимална вместимост на раницата */

unsigned F[MAXN][MAXM];    /* Целева функция */

const unsigned m[MAXN] = {0,1,2,3,5,6,7};      /* Тегло на предметите */
const unsigned c[MAXN] = {0,1,10,19,22,25,30}; /* Цена на предметите */
const unsigned M = 15;           /* Обща вместимост на раницата */
const unsigned N = 6;            /* Брой предмети */

void calculate(void) /* Пресмята стойностите на целевата функция */
{ unsigned i,j;
  for (j = 0; j <= M; j++)
	F[0][j] = 0;
  for (i = 1; i <= N; i++)
    for (j = 0; j <= M; j++)
      if (j >= m[i] && F[i-1][j] < F[i-1][j-m[i]] + c[i])
          F[i][j] = F[i-1][j-m[i]] + c[i];
        else
          F[i][j] = F[i-1][j];
}

void printTable(void) /* Извежда съдържанието на таблицата F[i][j] */
{ unsigned i, j;
  for (i = 1; i <= N; i++) {
    printf("\n");
    for (j = 0; j <= M; j++)
      printf("%4u",F[i][j]);
  }
}

void printSet(void) /* Извежда едно възможно множество от предмети, за което */
{               /* се постига максимална стойност на целевата функция */
   unsigned i = N,
            j = M;
   while (j != 0) {
     if (F[i][j] == F[i-1][j])
       i--;
     else {
       printf("%u ",i);
       j -= m[i];
       i--;
     }
   }
}

int main(void)
{ printf("%s%u","\nБрой предмети: ",N);
  printf("%s%u","\nМаксимално допустимо общо тегло: ",M);
  calculate();
  printf("\nТаблица F[i][j]: ");
  printTable();
  printf("\n%s%u","Максимална постигната стойност: ",F[N][M]);
  printf("\nВземете предметите с номера: "); printSet();
  return 0;
}
