#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX           100
#define TEST_LOOP_CNT 100

struct  CElem {
  int key;
  /* .............
     Някакви данни
     ............. */
};

void swap(struct CElem *x1, struct CElem *x2)
{ struct CElem tmp = *x1; *x1 = *x2; *x2 = tmp; }

void init(struct CElem m[], unsigned n) /* Запълва масива със случайни цели числа */
{ unsigned i;
  srand(time(NULL));
  for (i = 1; i <= n; i++)
    m[i].key = rand() % n;
}

/* Отсяване на елемента от върха на пирамидата */
void sift(struct CElem m[], unsigned l, unsigned r)
{ unsigned i = l,
       	   j = i+i;
  struct CElem x = m[i];
  while (j <= r) {
	if (j < r)
	  if (m[j].key < m[j+1].key)
        j++;
	if (x.key >= m[j].key)
      break;
	m[i] = m[j];
    i = j;
    j <<= 1;
  }
  m[i] = x;
}

void heapSort(struct CElem m[], unsigned n) /* Пирамидално сортиране */
{ unsigned k;

  /* 1. Построяване на пирамидата */
  for (k = n/2 + 1; k > 1; k--)
    sift(m,k-1,n);

  /* 2. Построяване на сортирана последователност */
  for (k = n; k > 1; k--) {
    swap(m+1,m+k);
    sift(m,1,k-1);
  }
}

void print(struct CElem m[], unsigned n) /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 1; i <= n; i++)
    printf("%8d", m[i].key);
}

void check(const struct CElem m[], const struct CElem saveM[], unsigned n)
{ unsigned i, j;
  char *found; /* третира се като масив от булев тип */

  /* 1. Проверка за наредба във възходящ ред */
  for (i = 1; i < n; i++)
    assert(m[i].key <= m[i+1].key);

  /* 2. Проверка за пермутация на изходните елементи */
  found = (char *) calloc(n+1,sizeof(*found));
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++)
      if (!found[j] && m[i].key == saveM[j].key) {
	    found[j] = 1;
	    break;
      }
    assert(j <= n); /* Пропада, ако не е намерен съответен */
  }
  free(found);
}

int main(void) {
  struct CElem m[MAX+1], saveM[MAX+1];
  unsigned loopInd;
  printf("start -- \n");
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    init(m,MAX);
    memcpy(saveM, m, sizeof(m)); /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m,MAX);
    heapSort(m,MAX);
    printf("Масивът след сортирането:\n");
    print(m,MAX);
    check(m,saveM,MAX);
  }
  return 0;
}