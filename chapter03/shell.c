#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define TEST_LOOP_CNT 100

#define STEPS_CNT 4
#define steps0 40
const unsigned steps[STEPS_CNT] = { steps0, 13, 4, 1 };

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

void shellSort(struct CElem m[], unsigned n)
{ int i,j,k,s;
  unsigned stepInd;
  struct CElem x;

  for (stepInd = 0; stepInd < STEPS_CNT; stepInd++) {
    s = -(k = steps[stepInd]); /* Ограничител */
    for (i = k + 1; i <= (int)n; i++) {
      x = m[i]; 
      j = i - k;
      if (0 == s)
        s = -k;
      m[++s] = x;
      while (x.key < m[j].key) {
         m[j + k] = m[j];
         j -= k;
      }
      m[j + k] = x;
    }
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
  struct CElem pm[MAX + steps0 + 2], saveM[MAX + 1], *m;
  unsigned loopInd;
  m = pm + steps0 + 1;
  printf("start -- \n");
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    init(m,MAX);
    memcpy(saveM, m, (MAX+1)*sizeof(*m)); /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m,MAX);
    shellSort(m,MAX);
    printf("Масивът след сортирането:\n");
    print(m,MAX);
    check(m,saveM,MAX);
  }
  return 0;
}