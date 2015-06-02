#include <stdio.h>
#define  MAXN 30     /* Максимален брой предмети */
#define  MAXM 1000   /* Максимална вместимост на раницата */

unsigned F[MAXM];    /* Целева функция */
unsigned best[MAXM]; /* Последен добавен предмет при достигане на максимума */

const unsigned m[MAXN] = {0,30,15,50,10,20,40,5,65}; /* Тегло на предметите */
const unsigned c[MAXN] = {0,5,3,9,1,2,7,1,12};       /* Стойност на предметите */
const unsigned M = 70;           /* Обща вместимост на раницата */
const unsigned N = 8;            /* Брой предмети */

char used(unsigned i, unsign/ed j)
{ /* Проверява дали j участва в оптималното множество, определено от F[i] */
   while (i != 0 && best[i] != 0)
     if (best[i] == j)
		return 1;
     else
		i -= m[best[i]];
   return 0;
}

void calculate() /* Пресмята стойностите на целевата функция */
{ unsigned i,j;
 
  /* Инициализация */
  for (i = 0; i <= M; i++)
	 best[i] = 0; 

  /* Основен цикъл */
  for (i = 1; i <= M; i++)              
    for (j = 1; j <= N; j++)
      if (i >= m[j])
        if (F[i] < F[i-m[j]] + c[j])
          if (!used(i-m[j],j)) {
            F[i] = F[i-m[j]] + c[j];
            best[i] = j;
          }
}

void printSet() /* Извежда едно възможно множество от предмети, за което */
{               /* се постига максимална стойност на целевата функция */
   unsigned value = M;
   while (value) {
     printf("%4u ",best[value]);
     value -= m[best[value]];
   }
}

int main() {
   printf("\nБрой предмети: %u",N);
   printf("\nМаксимална допустима обща маса: %u",M);
   calculate();
   printf("\nМаксимална постигната ценност: %u",F[M]);
   printf("\nВземете следните предмети: "); printSet();
   return 0;
}
