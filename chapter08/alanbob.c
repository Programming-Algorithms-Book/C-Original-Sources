#include <stdio.h>
#define MAX       100 /* Максимален брой предмети */
#define MAXVALUE  200 /* Максимална стойност на отделен предмет */

unsigned char can[MAX * MAXVALUE]; /* Може ли да се получи съответната сума? */

const unsigned m[MAX] = {3,2,3,2,2,77,89,23,90,11}; /* Стойност на всеки от предметите */
const unsigned n = 10;           /* Общ брой на предметите за поделяне */

void solve(void)
{ unsigned long p; /* Обща стойност на предметите за поделяне */
  unsigned i, j;

  /* Пресмятане на сумата p */
  for (p = i = 0; i < n; p += m[i++])
    ;

  /* Начално инициализиране */
  for (i = 1; i <= p; i++)
	can[i] = 0;
  can[0] = 1;

  /* Намиране на всевъзможните суми от стойности на подаръците */
  for (i = 0; i < n; i++)
    for (j = p; j+1 > 0; j--)
      if (can[j])
		 can[j + m[i]] = 1;

  /* Намиране на най-близката до p/2 стойност */
  for (i = p / 2; i > 1; i--)
    if (can[i]) {
      printf("\n%s%u%s%lu", "сума за Алан: ", i, "; сума за Боб: ", p - i);
      return;
    }
}

int main(void)
{ solve();
  return 0;
}