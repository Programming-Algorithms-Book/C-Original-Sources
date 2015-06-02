#include <stdio.h>
#include <stdlib.h>
#define MAX  100

int a[MAX],          /* Основен масив - за сортиране */
    b[MAX];          /* Помощен масив */

const unsigned n = 100; /* Брой елементи за сортиране */

/* Генерира примерно множество */
void generate(void)
{ unsigned i;
  for (i = 0; i < n; i++)
	a[i] = rand() % (2*n + 1);
}

/* Извежда списъка на екрана */
void printList(void)
{ unsigned i;
  for (i = 0; i < n; i++)
	printf("%4d", a[i]);
}

/* Сортиране */
void mergeSort(unsigned left, unsigned right)
{ unsigned i, j, k, mid;
  if (right <= left) return;  /* Проверка дали има какво да се сортира */
  mid = (right + left) / 2;
  mergeSort(left, mid);       /* Сортиране на левия дял */
  mergeSort(mid + 1, right);  /* Сортиране на десния дял */

  /* Копиране на елементите на a[] в помощния масив b[] */
  for (i = mid + 1; i > left; i--)
	b[i - 1] = a[i - 1];           /* Права посока */
  for (j = mid; j < right; j++)
	b[right + mid - j] = a[j + 1]; /* Обратна посока */

  /* Сливане на двата масива в a[] */
  for (k = left; k <= right; k++)
	a[k] = (b[i] < b[j]) ? b[i++] : b[j--];
}

int main(void) {
  generate();
  printf("Преди сортирането:\n");
  printList();
  mergeSort(0, n-1);
  printf("След сортирането:\n");
  printList();
  return 0;
}