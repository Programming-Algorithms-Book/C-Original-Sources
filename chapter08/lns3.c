#include <stdio.h>
#define MAX 100

const int x[MAX] = {100, 10, 15, 5, 25, 22, 12, 22}; /* Редица */
                   /* Нулевият елемент на x[] не се използва! */
const unsigned n = 7; /* Брой елементи в редицата */
int LNS[MAX]; /* LNS[i] - минимален елемент, който може да стои на позиция i */

/* Намира дължината на най-дългата ненамаляваща подредица */
unsigned LNS_Length(void)
{ unsigned i, r, k, l, med;

  for (LNS[1] = x[1], k = 1, i = 2; i <= n; i++) {
    if (x[i] < LNS[1])        /* случай 1 */
      LNS[1] = x[i];
    else if (x[i] >= LNS[k])  /* случай 2 */
      LNS[++k] = x[i];
    else {                    /* случай 3 */
      l = 1;
      r = k;                  /* двоично търсене */
      while (l < r - 1) {
        med = (l + r) / 2;
        if (LNS[med] <= x[i])
		  l = med;
        else
		  r = med;
      }
      LNS[r] = x[i];
    }
  }
  return k;
}

int main(void) {
  printf("Дължина на най-дългата ненамаляваща подредица: %u\n", LNS_Length());
  return 0;
}
