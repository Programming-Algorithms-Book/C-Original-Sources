#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 100
#define FACTOR 5
#define MAX_VALUE (MAX*FACTOR)
#define NO_INDEX (unsigned)(-1)

struct CElem {
  int key;
  /* .............
     Някакви данни
     ............. */
};

void init(struct CElem m[], unsigned n) /* Запълва масива със случайни цели числа */
{ unsigned i;

  /* 1. Запълване със случайни стойности в нарастващ ред */
  srand(time(NULL));
  m[0].key = rand() % FACTOR;
  for (i = 1; i < n; i++)
    m[i].key = 1 + m[i-1].key + rand() % FACTOR;

  /* 2. Разменяме елементи */
  for (i = 1; i < n; i++) {
    unsigned ind1, ind2;
    struct CElem tmp;

    /* 2.1. Избиране на два случайни индекса */
    ind1 = rand() % n;
    ind2 = rand() % n;

    /* 2.2. Разменяме ги */
    tmp = m[ind1];
    m[ind1] = m[ind2];
    m[ind2] = tmp;
  }

}

void print(struct CElem m[], unsigned n) /* Извежда ключовете на масива на екрана */
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%8d", m[i].key);
}

void do4Elem(const struct CElem e)
{ printf("%8d", e.key); }

void setSort(struct CElem m[], unsigned n) /* Сортира масив с използване на множество */
{ unsigned indSet[MAX_VALUE]; /* Индексно множество */
  unsigned i,j;

  /* 0. Инициализиране на множеството */
  for (i = 0; i < MAX_VALUE; i++)
    indSet[i] = NO_INDEX;

  /* 1. Формиране на множеството */
  for (j = 0; j < n; j++) {
    assert(m[j].key >= 0 && m[j].key < MAX_VALUE);
    assert(NO_INDEX == indSet[m[j].key]);
    indSet[m[j].key] = j;
  }

  /* 2. Генериране на сортирана последователност */
  for (i = j = 0; i < MAX_VALUE; i++)
    if (NO_INDEX != indSet[i])
      do4Elem(m[indSet[i]]);
}

int main(void) {
  struct CElem m[MAX];
  init(m, MAX);
  printf("Масивът преди сортирането:\n");
  print(m,MAX);
  printf("Масивът след сортирането:\n");
  setSort(m, MAX);
  return 0;
}