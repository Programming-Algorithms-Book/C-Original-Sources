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

void binInit(void) { n = 0; }                    /* Инициализация */

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

unsigned getMaxPower2(unsigned k)
{ unsigned pow2;
  for (pow2 = 1; pow2 <= k; pow2 <<= 1) ;
  return pow2 >> 1;
}
	
unsigned binSearch(int key)                      /* Извършва двоично търсене */
{ unsigned i, l, ind;
  i = getMaxPower2(n);
  l = m[i].key >= key ? 0 : n - i + 1;
  while (i > 0) {
    i = i >> 1; 
    ind = l + i;
    if (m[ind].key == key)
      return ind;
    else if (m[ind].key < key)
      l = ind;
  }
  return NOT_FOUND;
}
	
void binInsert(int key, int data)               /* Добавяне на нов елемент */
{ m[n].key = key;
  m[n++].data = data;
}

void binPrint(void)                             /* Извежда списъка на екрана */
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
    if (NOT_FOUND == (ind = binSearch(elem2Search)))
      printf("%s","Елемент с такъв ключ не съществува!\n");
    else
      printf("%Елементът е намерен! Стойност на инф. част: %d\n", m[ind].data);
  }
}

int main(void) {
  unsigned ind;
  binInit();
  for (ind = 0; ind < MAX; ind++)
    binInsert(rand() % (MAX*2), ind);
  sort();
  printf("Списъкът съдържа следните елементи: \n"); binPrint();
  printf("\nТестване:\n");
  performSearchTest();
  return 0;
}