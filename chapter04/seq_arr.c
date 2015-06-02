#include <stdio.h>
#include <stdlib.h>

#define MAX 100

#define DataType int
struct CElem {
  int key;
  DataType data;
  /* ... */
} m[MAX + 1]; /* Масив от записи */
unsigned n;   /* Брой елементи в масива */

void seqInit(void) { n = 0; }              /* Инициализация */

unsigned seqSearch(int key)            /* Последователно търсене */
{ unsigned x;
  m[0].key = key; /* Ограничител */
  for (x = n + 1; key != m[--x].key; ) ;
  return x;
}

void seqInsert(int key, DataType data) /* Добавя нов елемент */
{ m[++n].key = key;
  m[n].data = data;
}

void seqPrint(void)                    /* Извежда списъка на екрана */
{ unsigned i;
  char buf[9];
  for (i = 1; i <= n; i++) {
    sprintf(buf, "%d|%d", m[i].key, m[i].data);
    printf("%8s", buf);
  }
}

void performSearchTest(void)
{ unsigned ind, elem2Search;

  for (elem2Search = 0; elem2Search < 2*MAX; elem2Search++) {
    printf("Търсим елемент с ключ %u.\n", elem2Search);
    if (0 == (ind = seqSearch(elem2Search)))
      printf("%s","Елемент с такъв ключ не съществува!\n");
    else
      printf("%Елементът е намерен! Стойност на инф. част: %d\n", m[ind].data);
  }
}

int main(void) {
  unsigned ind;
  seqInit();
  for (ind = 0; ind < MAX; ind++)
    seqInsert(rand() % (MAX*2), ind);
  printf("Списъкът съдържа следните елементи: \n"); seqPrint();
  printf("\nТестване:\n");
  performSearchTest();
  return 0;
}
