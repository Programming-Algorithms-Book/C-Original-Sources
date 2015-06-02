#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define NOT_FOUND (unsigned)(-1)

#define DataType int
struct CElem { 
  int key;
  DataType data;
  /* ... */
} m[MAX];   /* Масив от записи */
unsigned n; /* Брой елементи в масива */

const unsigned step = 10;

void jmpInit(void) { n = 0; }                    /* Инициализация */

void sort(void)                                  /* Сортиране */
{ unsigned i,j;
  for (i = 0; i < n-1; i++)
    for (j = i + 1; j < n; j++)
      if (m[i].key > m[j].key) {
        struct CElem tmp = m[i];
        m[i] = m[j];
        m[j] = tmp;
      }
}
	
unsigned seqSearch(unsigned l, unsigned r, int key)  /* Последователно търсене */
{ while (l <= r)
    if (m[l++].key == key)
      return l-1;
  return NOT_FOUND;
}

unsigned jmpSearch(int key, unsigned step)                /* Търсене със скокове */
{ unsigned ind;
  for (ind = 0; ind < n && m[ind].key < key; ind += step) ;
  return seqSearch(ind + 1 < step ? 0 : ind + 1 - step, n < ind ? n : ind, key);
}
	
void jmpInsert(int key, int data)               /* Добавяне на нов елемент */
{ m[n].key = key;
  m[n++].data = data;
}

void jmpPrint(void)                             /* Извежда списъка на екрана */
{ unsigned i;
  char buf[9];
  for (i = 0; i < n; i++) {
    sprintf(buf, "%d|%d", m[i].key, m[i].data);
    printf("%8s", buf);
  }
}

void performSearchTest(void)
{ unsigned ind, elem2Search;
  for (elem2Search = 0; elem2Search < 2*MAX; elem2Search++) {
    printf("Търсим елемент с ключ %u.\n", elem2Search);
    if (NOT_FOUND == (ind = jmpSearch(elem2Search,step)))
      printf("%s","Елемент с такъв ключ не съществува!\n");
    else
      printf("%Елементът е намерен! Стойност на инф. част: %d\n", m[ind].data);
  }
}

int main(void) {
  unsigned ind;
  jmpInit();
  for (ind = 0; ind < MAX; ind++)
    jmpInsert(rand() % (MAX*2), ind);
  sort();
  printf("Списъкът съдържа следните елементи: \n"); jmpPrint();
  printf("\nТестване:\n");
  performSearchTest();
  return 0;
}