#include <stdio.h>
#define MAX 100

const int x[MAX] = {100, 10, 15, 5, 25, 22, 12, 22}; /* Редица */
                   /* Нулевият елемент на x[] не се използва! */
const unsigned n = 7; /* Брой елементи в редицата */
int LNS[MAX][MAX];    /* Целева функция */

/* Намира дължината на най-дългата ненамаляваща подредица */
unsigned LNS_Length(void)
{ unsigned i, j, r;

  /* Начална инициализация */
  for (i = 0; i <= n; i++) {
    for (j = 1; j <= n; j++)
	  LNS[i][j] = MAX + 1;
    LNS[i][0] = -1;
  }

  /* Основен цикъл */
  r = 1;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (LNS[i - 1][j - 1] <= x[i] && x[i] <= LNS[i - 1][j]
          && LNS[i - 1][j - 1] <= LNS[i - 1][j]) {
        LNS[i][j] = x[i];
        if (r < j)
		  r = j;
      }
      else
		LNS[i][j] = LNS[i - 1][j];
    }
  }

  return r;
}

/* Извежда най-дългата ненамаляваща подредица (в обратен ред) */
void LNS_Print(unsigned j)
{ unsigned i = n;
  do {
    if (LNS[i][j] == LNS[i - 1][j])
	  i--;
    else {
      printf("%d ", x[i]);
	  j--;
    }
  } while (i > 0);
}

/* Извежда най-дългата ненамаляваща подредица */
void LNS_Print2(unsigned i, unsigned j)
{ if (0 == i) return;
  if (LNS[i][j] == LNS[i - 1][j])
    LNS_Print2(i - 1, j);
  else {
    LNS_Print2(i, j - 1);
    printf("%d ", x[i]);
  }
}

int main(void) {
  unsigned len = LNS_Length();
  printf("\nДължина на най-дългата ненамаляваща подредица: %u", len);
  printf("\nПодредицата (обърната): "); LNS_Print(len);
  printf("\nПодредицата: "); LNS_Print2(n, len);
  return 0;
}
