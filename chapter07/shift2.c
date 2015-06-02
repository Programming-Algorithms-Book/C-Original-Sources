#include <assert.h>
#include <stdio.h>

#define MAX 100

struct CElem {
  int data;
  /* ... */
} m[MAX];

const unsigned n = 10; /* Брой елементи в масива */
const unsigned k = 2;  /* Брой позицции на отместване */

void init(void)
{ unsigned i;
  for (i = 0; i < n; i++)
    m[i].data = i;
}

void swap(unsigned a, unsigned b, unsigned l)
{ /* Разменя местата на подмасивите m[a..a+l-1] и m[b..b+l-1] */
  unsigned i;
  struct CElem tmp;
  for (i = 0; i < l; i++) {
    tmp = m[a + i];
    m[a + i] = m[b + i];
    m[b + i] = tmp;
  }
}

void shiftLeft2(unsigned k)
{ /* Измества масива m[] на k позиции наляво. 
   * рекурсивен процес, реализиран итеративно } */
  unsigned i, j, p;
  p = i = k;
  j = n - k;
  while (i != j)
    if (i > j) {
      swap(p - i, p, j);
      i -= j;
    }
    else {
      swap(p - i, p + j - i, i);
      j -= i;
    }
  swap(p - i, p, i);
}

void print(void)
{ unsigned i;
  for (i = 0; i < n; i++)
    printf("%d ", m[i].data);
  printf("\n");
}

int main(void) {
  init();
  shiftLeft2(k);
  print();
  return 0;
}