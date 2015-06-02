#include <stdio.h>
#define  MAXN 30           /* Максимален брой предмети */
#define  MAXM 1000         /* Максимална вместимост на раницата */

unsigned F[MAXN][MAXM];    /* Целева функция */

const unsigned m[MAXN] = {0,6,3,10,2,4,8,1,13,3};  /* Тегло на предметите */
const unsigned c[MAXN] = {0,5,3,9,1,2,7,1,12,3};   /* Цена на предметите */
const unsigned M = 14;           /* Обща вместимост на раницата */
const unsigned N = 9;            /* Брой предмети */

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

unsigned set[MAXN]; /* Множество от предмети, за които се постига max */

void printAll(unsigned i, unsigned j, unsigned k)
{   /* Извежда ВСИЧКИ възможни множества от предмети, за които */
    /* се постига максимална стойност на целевата функция */
   if (0 == j) {
     printf("\nВземете следните предмети: ");
     for (i = 0; i < k; i++)
       printf("%u ",set[i]);
   }
   else {
     if (F[i][j] == F[i-1][j])
       printAll(i-1,j,k);
     if (j >= m[i] && F[i][j] == F[i-1][j-m[i]] + c[i]) {
       set[k] = i;
       printAll(i-1,j-m[i],k+1);
     }
   }
}

int main(void) {
   printf("%s%u","\nБрой предмети: ",N);
   printf("%s%u","\nМаксимална допустима обща маса: ",M);
   calculate();
   printf("\nТаблица F[i][j]: ");
   printTable();
   printf("\n%s%u","Максимална постигната стойност: ",F[N][M]);
   printf("\nСледват всевъзможните множества от решения:");
   printAll(N,M,0);
   return 0;
}
