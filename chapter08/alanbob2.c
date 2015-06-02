#include <stdio.h>
#define MAX       100 /* Максимален брой предмети */
#define MAXVALUE  200 /* Максимална стойност на отделен предмет */
#define NOT_SET (unsigned)(-1)

unsigned last[MAX * MAXVALUE]; /* Кой предмет е бил добавен последен? */

const unsigned m[MAX] = {3,2,3,2,2,77,89,23,90,11}; /* Стойност на всеки от предметите */
const unsigned n = 10;           /* Общ брой на предметите за поделяне */

void solve(void)
{ unsigned long p; /* Обща стойност на предметите за поделяне */
  unsigned long curSum = 0;
  unsigned i, j;

  /* Пресмятане на сумата p */
  for (p = i = 0; i < n; p += m[i++])
    ;

  /* Начално инициализиране */
  for (last[0] = 0, i = 1; i <= p; i++)
	last[i] = NOT_SET;

  /* Намиране на всевъзможните суми от стойности на подаръците */
  for (i = 0; i < n; i++) {
    for (j = p; j+1 > 0; j--)
      if (NOT_SET != last[j] && NOT_SET == last[j + m[i]])
		last[j + m[i]] = i;
    curSum += m[i];
  }

  /* Намиране на най-близката до p/2 стойност и извеждане на решението */
  for (i = p / 2; i > 1; i--) {
    if (NOT_SET != last[i]) {
      printf("\n%s%u%s%lu", "Сума за Алан: ", i, "; сума за Боб: ", p - i);
      printf("\nАлан взема:");
      while (i > 0) {
        printf(" %u", m[last[i]]);
        i -= m[last[i]];
      }
      printf("\nБоб взема останалите подаръци.");
      return;
    }
  }
}

int main(void)
{ solve();
  return 0;
}