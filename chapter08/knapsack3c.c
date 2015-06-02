#include <stdio.h>
#define MAXN            30    /* Максимален брой предмети */
#define MAXM            1000  /* Максимална вместимост на раницата */

const unsigned m[MAXN] = {0,1,2,3,5,6,7};      /* Тегло на предметите */
const unsigned c[MAXN] = {0,1,10,19,22,25,30}; /* Стойност на предметите */
const unsigned M = 15;              /* Обща вместимост на раницата */
const unsigned N = 6;               /* Брой предмети */

unsigned calculate(void) /* Пресмята стойностите на целевата функция */
{ unsigned F[MAXM], OldF[MAXM]; /* Целева функция */
  unsigned i,j,k;

  for (j = 0; j <= M; j++)
	OldF[j] = 0;
  for (i = 1; i <= N; i++) {
     for (j = 0; j <= M; j++)
        if (j >= m[i] && OldF[j] < OldF[j-m[i]] + c[i])
           F[j] = OldF[j-m[i]] + c[i];
        else F[j] = OldF[j];
     for (k = 0; k < M; k++)
        OldF[k] = F[k];
  }
  return F[M];
}

int main(void) {
   printf("%s%u","\nБрой предмети: ",N);
   printf("%s%u","\nМаксимална допустима обща маса: ",M);
   printf("\n%s%u","Максимална постигната ценност: ",calculate());
   return 0;
}