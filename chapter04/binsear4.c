#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define NOT_FOUND (unsigned)(-1)

#define DataType int
struct CElem { 
  int key;
  DataType data;
  /* ... */
} m[MAX+1]; /* Масив от записи */
unsigned n; /* Брой елементи в масива */

void binInit(void) { n = 0; }                    /* Инициализация */

void sort(void)                                  /* Сортиране */
{ unsigned i,j;
  for (i = 1; i < n; i++)
    for (j = i + 1; j <= n; j++)
      if (m[i].key > m[j].key) {
        struct CElem tmp = m[i];
        m[i] = m[j];
        m[j] = tmp;
      }
}
	
unsigned binSearch(int key)                     /* Извършва двоично търсене */
{ unsigned l = 0;
  if (m[512].key   < key) l = 1000-512+1;
  if (m[l+256].key < key) l += 256;
  if (m[l+128].key < key) l += 128;
  if (m[l+ 64].key < key) l +=  64;
  if (m[l+ 32].key < key) l +=  32;
  if (m[l+ 16].key < key) l +=  16;
  if (m[l+  8].key < key) l +=   8;
  if (m[l+  4].key < key) l +=   4;
  if (m[l+  2].key < key) l +=   2;
  if (m[l+  1].key < key) l +=   1;
  return (l < 1000 && m[++l].key == key ? l : NOT_FOUND);
}
	
void binInsert(int key, int data)               /* Добавяне на нов елемент */
{ m[++n].key = key;
  m[n].data = data;
}

void binPrint(void)                             /* Извежда списъка на екрана */
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