#include <stdio.h>
#define MAX 100

const int x[MAX] = {100, 10, 15, 5, 25, 22, 12, 22}; /* Редица */
                   /* Нулевият елемент на x[] не се използва! */
const unsigned n = 7; /* Брой елементи в редицата */

unsigned LNS[MAX]; /* Дължина на максималната редица с начало x[i] */
unsigned next[MAX]; /* Индекс на следващ елемент */

/* Намира дължината на най-дългата ненамаляваща подредица */
unsigned LNS_Length(unsigned *start)
{ unsigned i, j;
  unsigned l;       /* В момента на разглеждане на xi, 
                    /* l е дължината на максималната подредица с начало xj: */
                    /*    1) i < j <= n и */
                    /*    2) xi <= xj     */
  unsigned len = 0; /* Максимална (за момента) дължина на ненамаляваща подредица */
  for (i = n; i >= 1; i--) {
    for (l = 0, j = i + 1; j <= n; j++)
      if (x[j] >= x[i] && LNS[j] > l) {
        l = LNS[j];
        next[i] = j;
      }
    LNS[i] = l + 1;
    if (LNS[i] > len) {
      len = LNS[i];
      *start = i;
    }
  }
  return len;
}

/* Извежда най-дългата ненамаляваща подредица */
void LNS_Print(unsigned start)
{ for (; LNS[start] >= 1; start = next[start])
    printf(" %d", x[start]);
}

int main(void) {
  unsigned start;
  printf("Дължина на най-дългата ненамаляваща подредица: %u\n", LNS_Length(&start));
  printf("Подредицата: "); LNS_Print(start);
  return 0;
}
