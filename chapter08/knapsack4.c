#include <stdio.h>
#define  MAXN 30     /* Максимален брой предмети */
#define  MAXM 1000   /* Максимална вместимост на раницата */

unsigned F[MAXM];    /* Целева функция */
unsigned best[MAXM]; /* Последен добавен предмет при достигане на максимума */

const unsigned m[MAXN] = {0,30,15,50,10,20,40,5,65}; /* Тегло на предметите */
const unsigned c[MAXN] = {0,5,3,9,1,2,7,1,12};       /* Стойност на предметите */
const unsigned M = 70;           /* Обща вместимост на раницата */
const unsigned N = 8;            /* Брой предмети */

void calculate(void) /* Пресмята стойностите на целевата функция */
{ unsigned i,j;

  /* Инициализация */
  for (i = 0; i <= M; i++)
	 F[i] = 0; 

  /* Основен цикъл */
  for (j = 1; j <= N; j++)
    for (i = 1; i <= M; i++)
      if (i >= m[j])
        if (F[i] < F[i-m[j]] + c[j]) {
          F[i] = F[i-m[j]] + c[j];
          best[i] = j;
        }
}

void printSet(void)  /* Извежда едно възможно множество от предмети, за което */
{                    /* се постига максимална стойност на целевата функция */
   unsigned value = M;
   printf("\nВземете следните предмети: ");
   while (value) {
     printf("%4u ", best[value]);
     value -= m[best[value]];
   }
}

int main(void) {
   printf("%s%u","\nБрой предмети: ",N);
   printf("%s%u","\nМаксимална допустима обща маса: ",M);
   calculate();
   printf("\n%s%u","Максимална постигната стойност: ",F[M]);
   printSet();
   return 0;
}