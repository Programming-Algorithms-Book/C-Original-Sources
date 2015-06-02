#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX           100
#define TEST_LOOP_CNT 100
#define FACTOR 5
#define MAX_VALUE (MAX*FACTOR)

void init(unsigned m[], unsigned n) /* Запълва масива със случайни цели числа */
{ unsigned i;

  /* 1. Запълвване със случайни стойности в нарастващ ред */
  srand(time(NULL));
  m[0] = rand() % FACTOR;
  for (i = 1; i < n; i++)
    m[i] = 1 + m[i-1] + rand() % FACTOR;

  /* 2. Разменяме многократно произволни двойки елементи */
  for (i = 1; i < n; i++) {
    unsigned ind1, ind2;
    unsigned tmp;

    /* 2.1. Избиране на два случайни индекса */
    ind1 = rand() % n;
    ind2 = rand() % n;

    /* 2.2. Разменяме ги */
    tmp = m[ind1];
    m[ind1] = m[ind2];
    m[ind2] = tmp;
  }
}

void setSort(unsigned m[], unsigned n) /* Сортира масив с използване на множество */
{ char set[MAX_VALUE];
  unsigned i,j;

  /* 0. Инициализиране на множеството */
  for (i = 0; i < MAX_VALUE; i++)
    set[i] = 0;

  /* 1. Формиране на множеството */
  for (j = 0; j < n; j++) {
    assert(m[j] >= 0 && m[j] < MAX_VALUE);
    assert(0 == set[m[j]]);
    set[m[j]] = 1;
  }

  /* 2. Генериране на сортирана последователност */
  for (i = j = 0; i < MAX_VALUE; i++)
    if (set[i])
      m[j++] = i;

  assert(j == n);
}

void print(unsigned m[], unsigned n) /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8u", m[i]);
}

void check(const unsigned m[], const unsigned saveM[], unsigned n)
{ unsigned i, j;
  char *found; /* третира се като масив от булев тип */

  /* 1. Проверка за наредба във възходящ ред */
  for (i = 0; i < n-1; i++)
    assert(m[i] <= m[i+1]);

  /* 2. Проверка за пермутация на изходните елементи */
  found = (char *) calloc(n,sizeof(*found));
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      if (!found[j] && m[i] == saveM[j]) {
	found[j] = 1;
	break;
      }
    assert(j < n); /* Пропада, ако не е намерен съответен */
  }

  free(found);
}

int main(void) {
  unsigned m[MAX], saveM[MAX];
  unsigned loopInd;
  for (loopInd = 1; loopInd <= TEST_LOOP_CNT; loopInd++) {
    printf("\n<<<<< Тест %u >>>>>\n", loopInd);
    init(m,MAX);
    memcpy(saveM, m, sizeof(m)); /* Запазва се копие на масива */
    printf("Масивът преди сортирането:\n");
    print(m,MAX);
    setSort(m,MAX);
    printf("Масивът след сортирането:\n");
    print(m,MAX);
    check(m,saveM,MAX);
  }
  return 0;
}