#include <stdio.h>
#define MAX 100
#define BASE 10 /* Основа на бройната система */
unsigned succ[MAX];  /* Наследници за всеки връх */
unsigned F[BASE];    /* F[i]: текуща макс. дължина на подредица с най-старша цифра i */
unsigned ind[BASE];  /* ind[i]: индекс на първия член на редицата с първа цифра i */

const unsigned n = 17;  /* Брой елементи в редицата */
const unsigned x[MAX] = {0, 72, 121, 1445, 178, 123, 3462, 762, 33434, 444,
                         472, 4, 272, 4657, 7243, 7326, 3432, 3465};              /* Редица */

/* Намира максимална домино-редица */
void solve(void)
{ unsigned i, l, r;
  
  for (i = 0; i < BASE; i++)
	F[i] = ind[i] = 0;

  /* Намиране дължините на редиците, започващи с всяка от цифрите от 0 до 9 */
  for (i = n; i > 0; i--) {
    /* Определяне на най-старшата и най-младшата цифри на числото */
    r = x[i] % BASE;
    l = x[i];
    while (l > BASE)
	   l /= BASE;
    /* Евентуално актуализиране на редицата, започваща със старшата цифра */
    if (F[r] >= F[l]) {
      F[l] = F[r] + 1;
      succ[i] = ind[r];
      ind[l] = i;
    }
  }
}

void print(void)
{ unsigned i, bestInd;

  /* Определяне на най-дългата редица */
  bestInd = 0;
  for (i = 1; i < BASE; i++) /* Никое число не започва с 0 */
    if (F[i] > F[bestInd])
	  bestInd = i;

  /* Извеждане на редицата на екрана */
  printf("\nДължина на максималната домино-подредица: %u", F[bestInd]);
  printf("\nЕто и самата подредица: ");
  i = ind[bestInd];
  do {
    printf("%u ", x[i]);
    i = succ[i];
  } while (i > 0);
}

int main(void) {
  solve();
  print();
  return 0;
}