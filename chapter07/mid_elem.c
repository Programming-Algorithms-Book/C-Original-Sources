#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int m[MAX];

const unsigned n = 100; /* Брой елементи в масива */
const unsigned k = 10;  /* Пореден номер на търсения елемент */

void init(int m[], unsigned n) /* Запълва масива със случайни числа */
{ unsigned i;
  for (i = 0; i < n; i++)
    m[i] = rand() % (2*n+1);
}

void swap(int *el1, int *el2) /* Разменя стойностите на две променливи */
{ int tmp = *el1; *el1 = *el2; *el2 = tmp; }

void find(int m[], unsigned n, unsigned k) /* намира k-ия елемент */
{ int i,j,l,r;
  int x;
  l = 0; r = n - 1;
  while (l < r) {
    x = m[k]; i = l; j = r;
    for(;;) {
      while (x > m[i]) i++;
      while (x < m[j]) j--;
      if (i > j)
        break;
      swap(m + i, m + j);
      i++;
      j--;
    }
    if (j < (int)k)
      l = i;
    if ((int)k < i)
      r = j;
  }
}

void print(int m[], unsigned n) /* Извежда масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i]);
}

int main(void) {
  init(m,n);
  printf("Масивът преди търсенето:"); print(m,n);
  printf("\nТърсим k-ия елемент: k=%u", k);
  find(m,n,k);
  printf("\nМасивът след търсенето:"); print(m,n);
  printf("\nk-ият елемент е: %d", m[k]);
  return 0;
}