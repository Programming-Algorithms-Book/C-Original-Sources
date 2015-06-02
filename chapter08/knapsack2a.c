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

void calculate(void)
{ unsigned maxValue;                  /* Максимална постигната стойност */
  unsigned maxIndex;                  /* Индекс, за който е постигната */
  unsigned i, j;

  memset(set, 0, sizeof(set));        /* Инициализиране на множествата с предмети */

  /* Пресмятане на стойностите на целевата функция */
  for (i = 1; i <= M; i++) { /* Търсим максималната стойност на F(i) */
    maxValue = 0;
    maxIndex = 0;
    for (j = 1; j <= N; j++)
      if (m[j] <= i && !set[i - m[j]][j])
        if (c[j] + Fn[i - m[j]] > maxValue) {
          maxValue = c[j] + Fn[i - m[j]];
          maxIndex = j;
        }

    if (maxIndex > 0) {  /* Съществува ли предмет с тегло, по-малко от i? */
      Fn[i] = maxValue;

      /* Новото множество set[i] се получава от set[i-m[maxIndex]]
       * чрез добавяне на елемента maxIndex
       */
      memcpy(set[i], set[i - m[maxIndex]], N);
      set[i][maxIndex] = 1;
    }

    if (Fn[i] < Fn[i - 1]) { /* Раницата побира всички предмети и дори още */
      Fn[i] = Fn[i - 1];
      memcpy(set[i], set[i - 1], N);
    }
  }

  /* Извеждане на резултата */
  printf("\nВземете предметите с номера:\n");
  for (i = 1; i <= N; i++)
    if (set[M][i])
	   printf("%5u", i);
  printf("\n%s%u", "Максимална постигната ценност: ", Fn[M]);
}

int main(void) {
  printf("%s%u", "\nБрой предмети: ", N);
  printf("%s%u", "\nВместимост на раницата: ", M);
  calculate();
  return 0;
}
