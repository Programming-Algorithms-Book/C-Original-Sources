﻿#include <assert.h>
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

void init(struct CElem m[], unsigned n)             /* Запълва масива със случайни цели числа */
{ unsigned i;
  srand(time(NULL));
  for (i = 0; i < n; i++)
    m[i].key = rand() % n;
}

void binaryInsertion(struct CElem m[], unsigned n)  /* Сортиране с двоично вмъкване */
{ struct CElem x;
  unsigned i, med, r;
  int j, l;
  for (i = 1; i < n; i++) {
    x = m[i];
    l = 0;
    r = i - 1;
    /* Двоично търсене */
    while (l <= (int)r) {
      med = (l + r) / 2;
      if (x.key < m[med].key)
        r = med - 1;
      else
        l = med + 1;
    }
    /* Мястото е намерено. Следва вмъкване чрез изместване надясно */
    for (j = i - 1; j >= l; j--)
      m[j + 1] = m[j];
    m[l] = x;
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
    binaryInsertion(m, MAX);
    printf("Масивът след сортирането:\n");
    print(m, MAX);
    check(m, saveM, MAX);
  }
  return 0;
}