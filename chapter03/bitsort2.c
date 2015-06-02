#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX           100
#define TEST_LOOP_CNT 100

struct CElem {
  int key;
  /* .............
     Някакви данни
     ............. */
} m[MAX];

void swap(struct CElem *x1, struct CElem *x2)
{ struct CElem tmp = *x1; *x1 = *x2; *x2 = tmp; }

void init(struct CElem m[], unsigned n) /* Запълва масива със случайни цели числа */
{ unsigned i;
  srand(time(NULL));
  for (i = 0; i < n; i++)
    m[i].key = rand() % n;
}

void bitSort2(int l, int r, unsigned bitMask)
{ int i,j;
  if (r > l && bitMask > 0) {
    i = l; j = r;
    while (j != i) {
      while (!(m[i].key & bitMask) && i < j) i++;
      while ((m[j].key & bitMask) && j > i) j--;
      swap(&m[i], &m[j]);
    }
    if (!(m[r].key & bitMask)) j++;
    bitSort2(l,j-1,bitMask >> 1);
    bitSort2(j,r,bitMask >> 1);
  }
}

void print(struct CElem m[], unsigned n) /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i].key);
}

void check(const struct CElem m[], const struct CElem saveM[], unsigned n)
{ unsigned i, j;
  char *found; /* третира се като масив от булев тип */

  /* 1. Проверка за наредба във възходящ ред */
  for (i = 0; i < n-1; i++)
    assert(m[i].key <= m[i+1].key);

  /* 2. Проверка за пермутация на изходните елементи */
  found = (char *) calloc(n,sizeof(*found));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      if (!found[j] && m[i].key == saveM[j].key) {
	found[j] = 1;
	break;
      }
    assert(j < n); /* Пропада, ако не е намерен съответен */
  }

  free(found);
}

int main(void) {
  struct CElem saveM[MAX];
  unsigned loopInd;
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    printf("\n<<<<< Тест %u >>>>>\n", loopInd);
    init(m,MAX);
    memcpy(saveM, m, sizeof(m)); /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m,MAX);
    bitSort2(0,MAX-1,1 << 8*sizeof(m[0].key)-1);
    printf("Масивът след сортирането:\n");
    print(m,MAX);
    check(m,saveM,MAX);
  }
  return 0;
}