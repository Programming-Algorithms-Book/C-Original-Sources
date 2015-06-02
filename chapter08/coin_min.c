#include <stdio.h>
#define MAXCOINS  100 /* Максимален брой монети */
#define MAXSUM    100 /* Максимална сума */

unsigned long F[MAXSUM][MAXSUM];    /* Целева функция */
unsigned char exist[MAXSUM];        /* Съществува ли монета с такава стойност */

const unsigned coins[MAXCOINS] = {1,2,3,4,6}; /* Налични типове монети */
const unsigned sum = 6;                       /* Сума, която искаме да получим */
const unsigned n = 5;                         /* Общ брой налични монети */

/* Инициализираща функция */
void init(void)
{ unsigned i, j;
  /* Нулиране на целевата функция */
  for (i = 0; i <= sum; i++)
    for (j = 0; j <= sum; j++)
	   F[i][j] = 0;
  /* Друго представяне на стойностите на монетите за по-бърз достъп */
  for (i = 0; i <= sum; i++)
	 exist[i] = 0;
  for (i = 0; i < n; i++)
	 exist[coins[i]] = 1;
}

/* Намира броя на представянията на sum */
unsigned long count(unsigned sum, unsigned max)
{ unsigned long i;
  if (sum <= 0)
	return 0;
  if (F[sum][max] > 0)
    return F[sum][max];
  else {
    if (sum < max)
	   max = sum;
    if (sum == max && exist[sum])   /* Съществува монета с такава стойност */
      F[sum][max] = 1;
    for (i = max; i > 0; i--)  /* Пресмятаме всички */
      if (exist[i])
		 F[sum][max] += count(sum - i, i);
  }
  return F[sum][max];
}

int main(void) {
  init();
  printf("\nБроят на представянията на %u с наличните монети е %lu",
         sum, count(sum, sum));
  return 0;
}