#include <string.h>
#include <stdio.h>
#define NOT_CALCULATED  (unsigned) (-1)
#define MAXN            30    /* Максимален брой предмети */
#define MAXM            1000  /* Максимална вместимост на раницата */

char set[MAXM][MAXN];           /* Множество от предмети за всяко k=1..M */
unsigned Fn[MAXM];              /* Целева функция */

const unsigned m[MAXN] = { 0, 30, 15, 50, 10, 20, 40, 5, 65 };  /* Тегло на предметите */
const unsigned c[MAXN] = { 0, 5, 3, 9, 1, 2, 7, 1, 12 };        /* Стойност на предметите */
const unsigned M = 70;          /* Обща вместимост на раницата */
const unsigned N = 8;           /* Брой предмети */

/* Пресмята стойността на функцията за k */
void F(unsigned k)
{ unsigned i, bestI, fnBest, fnCur;
  /* Пресмятане на най-голямата стойност на F */
  for (bestI = fnBest = 0, i = 1; i <= N; i++) {
    if (k >= m[i]) {
      if (NOT_CALCULATED == Fn[k - m[i]]) F(k - m[i]);
      if (!set[k - m[i]][i])
        fnCur = c[i] + Fn[k - m[i]];
      else
        fnCur = 0;
      if (fnCur > fnBest) {
        bestI = i;
        fnBest = fnCur;
      }
    }
  }
  /* Регистрация на най-голямата стойност на функцията */
  Fn[k] = fnBest;
  if (bestI > 0) {
    memcpy(set[k], set[k - m[bestI]], N);
    set[k][bestI] = 1;
  }
}

/* Пресмятане на стойността на функцията */
void calculate(void) {
  unsigned i, sumM;

  /* Инициализация */
  memset(set, 0, sizeof(set));  /* Инициализиране на множествата с предмети */
  for (i = 0; i <= M; i++)      /* Инициализиране на стойностите на целевата функция */
    Fn[i] = NOT_CALCULATED;

  /* Дали не можем да вземем всички предмети? */
  for (sumM = m[1], i = 2; i <= N; i++)
    sumM += m[i];
  if (M >= sumM) {
    printf("\nМожете да вземете всички предмети!");
    return;
  }
  else {
    F(M); /* Пресмятане на стойността */

    /* Отпечатване на резултата */
    printf("\nВземете предметите с номера:\n");
    for (i = 1; i <= N; i++)
      if (set[M][i])
		printf("%5u", i);
    printf("\nМаксимална постигната стойност: %u", Fn[M]);
  }
}

int main(void) {
  printf("%s%u", "\nБрой предмети: ", N);
  printf("%s%u", "\nВместимост на раницата: ", M);
  calculate();
  return 0;
}
