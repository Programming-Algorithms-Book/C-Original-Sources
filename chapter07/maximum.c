#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int m[MAX];

const unsigned n = 100; /* Брой елементи в масива */

void init(int m[], unsigned n) /* Запълва масива със случайни числа */
{ unsigned i;
  for (i = 0; i < n; i++)
    m[i] = rand() % (2*n + 1);
}

void print(int m[], unsigned n) /* Извежда масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i]);
}

int findMax(int m[], unsigned n) /* Намира максималния елемент */
{ unsigned i;
  int max;
  for (max = m[0], i = 1; i < n; i++)
    if (m[i] > max)
       max = m[i];
  return max;
}

int findMin(int m[], unsigned n) /* Намира минималния елемент */
{ unsigned i;
  int min;
  for (min = m[0], i = 1; i < n; i++)
    if (m[i] < min)
       min = m[i];
  return min;
}

void findMinMax(int *min, int *max, const int m[], const unsigned n)
/* Намира едновременно максималния и минималния елементи */
{ unsigned i, n2;
  for (*min = *max = m[n2 = n/2], i = 0; i < n2; i++)
    if (m[i] > m[n-i-1]) {
      if (m[i] > *max)
        *max = m[i];
      if (m[n-i-1] < *min)
        *min = m[n-i-1];
    }
    else {
      if (m[n-i-1] > *max) 
        *max = m[n-i-1];
      if (m[i] < *min)
        *min = m[i];
    }
}

void swap(int *el1, int *el2) /* Разменя стойностите на две променливи */
{ int tmp = *el1; *el1 = *el2; *el2 = tmp; }

int findSecondMax(int m[], unsigned n) /* Намира втория по големина елемент */
{ int x,y;
  unsigned i;
  x = m[0]; y = m[1];
  if (y > x)
    swap(&x,&y);
  for (i = 2; i < n; i++)
    if (m[i] > y)
      if ((y = m[i]) > x)
        swap(&x,&y);
  return y;
}

int main(void) {
  int max, min;
  init(m,n);
  printf("Масивът:\n"); print(m,n);
  printf("Максимален елемент: %d\n", findMax(m,n));
  printf("Минимален елемент: %d\n", findMin(m,n));
  findMinMax(&min, &max, m, n);
  printf("Минимален и максимален елемент едновременно: %d %d\n", min, max);
  printf("Втори по големина елемент: %d\n", findSecondMax(m,n));
  return 0;
}