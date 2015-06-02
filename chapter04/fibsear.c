#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define NOT_FOUND (unsigned)(-1)

#define DataType int
struct CElem { 
  int key;
  DataType data;
  /* ... */
} m[MAX+1];        /* Масив от записи */
unsigned n;        /* Брой елементи в масива */
unsigned fib[MAX]; /* Числата на Фибоначи, ненадвишаващи n */

void fibInit(void) { n = 0; }                    /* Инициализация */

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

unsigned findFib(unsigned n)                    /* Намира числата на Фибоначи */ 
{ unsigned k;
  fib[0] = 0;
  fib[1] = 1;
  for (k = 2; ; k++) {
    if ((fib[k] = fib[k-1] + fib[k-2]) > n)
      return k-1;
  }
  return 0;
}

unsigned fibSearch(int key)                      /* Извършва Фибоначиево търсене */
{ int p,q,r,k;
  k = findFib(n);
  p = fib[k-1];
  q = fib[k-2];
  r = fib[k-3];
  if (key > m[p].key)
    p += n - fib[k] + 1;
  while (p > 0)
    if (key == m[p].key)
      return p;
    else
      if (key < m[p].key)
        if (0 == r)
          p = 0;
        else {
          int t;
          p -= r;
          t = q;
          q = r;
          r = t-r;
        }
      else
        if (1 == q)
          p = 0;
        else {
          p += r;
          q -= r;
          r -= q;
        }
  return NOT_FOUND;
}
	
void fibInsert(int key, int data)               /* Добавяне на нов елемент */
{ m[++n].key = key;
  m[n].data = data;
}

void fibPrint(void)                             /* Извежда списъка на екрана */
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
    if (NOT_FOUND == (ind = fibSearch(elem2Search)))
      printf("%s","Елемент с такъв ключ не съществува!\n");
    else
      printf("%Елементът е намерен! Стойност на инф. част: %d\n", m[ind].data);
  }
}

int main(void) {
  unsigned ind;
  fibInit();
  for (ind = 0; ind < MAX; ind++)
    fibInsert(rand() % (MAX*2), ind);
  sort();
  printf("Списъкът съдържа следните елементи: \n"); fibPrint();
  printf("\nТестване:\n");
  performSearchTest();
  return 0;
}