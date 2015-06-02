#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define TEST_LOOP_CNT 100

struct  CElem {
  int key;
  /* .............
     Някакви данни
     ............. */
};

void init(struct CElem m[], unsigned n) /* Запълва масива със случайни цели числа */
{ unsigned i;
  srand(time(NULL));
  for (i = 1; i <= n; i++)
    m[i].key = rand() % n;
}

void shellSort(struct CElem m[], unsigned l, unsigned r)
{ static unsigned incs[16] = { 1391376, 463792, 198768, 86961, 33936,
                               13776, 4592, 1968, 861, 336, 112, 48,
                                21, 7, 3, 1 };
  unsigned i, j, k, h;
  struct CElem v;

  for (k = 0; k < 16; k++)
    for (h = incs[k], i = l+h; i <= r; i++) {
      v = m[i]; j = i;
      while (j > h && m[j-h].key > v.key) {
        m[j] = m[j-h];
        j -= h;
      }
    m[j] = v;
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
  struct CElem m[MAX+1], saveM[MAX + 1];
  unsigned loopInd;
  printf("start -- \n");
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    init(m,MAX);
    memcpy(saveM, m, (MAX+1)*sizeof(*m)); /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m,MAX);
    shellSort(m,1,MAX);
    printf("Масивът след сортирането:\n");
    print(m,MAX);
    check(m,saveM,MAX);
  }
  return 0;
}