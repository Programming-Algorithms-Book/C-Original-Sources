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
};

void swap(struct CElem *x1, struct CElem *x2)
{ struct CElem tmp = *x1; *x1 = *x2; *x2 = tmp; }

void init(struct CElem m[], unsigned n)             /* Запълва масива със случайни цели числа */
{ unsigned i;
  srand(time(NULL));
  for (i = 0; i < n; i++)
    m[i].key = rand() % n;
}

void straightSelection(struct CElem m[], unsigned n)
{ unsigned i, j, ind;
  struct CElem x;
  for (i = 0; i < n - 1; i++)
    for (x = m[ind = i], j = i + 1; j < n; j++)
      if (m[j].key < x.key) {
        x = m[ind = j];
        m[ind] = m[i];
        m[i] = x;
      }
}

void print(struct CElem m[], unsigned n)            /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i].key);
}

void check(const struct CElem m[],
           const struct CElem saveM[],
           unsigned n)
{ unsigned i, j;
  char *found; /* третира се като масив от булев тип */

  /* 1. Проверка за наредба във възходящ ред */
  for (i = 0; i < n-1; i++)
    assert(m[i].key <= m[i + 1].key);

  /* 2. Проверка за пермутация на изходните елементи */
  found = (char *) calloc(n + 1, sizeof(*found));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      if (!found[j] && m[i].key == saveM[j].key) {
        found[j] = 1;
        break;
      }

    assert(j < n);               /* Пропада, ако не е намерен съответен */
  }

  free(found);
}

int main(void)
{ struct CElem m[MAX], saveM[MAX];
  unsigned loopInd;
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    printf("\n<<<<< Тест %u >>>>>\n", loopInd);
    init(m, MAX);
    memcpy(saveM, m, sizeof(m));  /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m, MAX);
    straightSelection(m, MAX);
    printf("Масивът след сортирането:\n");
    print(m, MAX);
    check(m, saveM, MAX);
  }
  return 0;
}