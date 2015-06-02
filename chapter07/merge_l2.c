#include <stdio.h>
#include <stdlib.h>
#define INFINITY (int)((1 << (sizeof(int)*8 - 1)) - 1)


struct list { /* Тип свързан списък */
  int value;
  struct list *next;
} *z; /* Празен елемент */

const unsigned long n = 100;

/* Генерира примерно множество */
struct list *generate(unsigned long n)
{ struct list *p, *q;
  unsigned long i;
  for (p = z, i = 0; i < n; i++) {
    q = (struct list *) malloc(sizeof(struct list));
    q->value = rand() % (2*n + 1);
    q->next = p;
    p = q;
  }
  return p;
}

void printList(struct list *p) /* Извежда списъка на екрана */
{ for (; p != z; p = p->next)
    printf("%4d", p->value);
}

struct list *merge(struct list *a, struct list *b)
{ struct list *c;
  c = z;

  /* Предполага се, че и двата списъка съдържат поне по един елемент */
  do {
    if (a->value < b->value) {
      c->next = a;
	  c = a;
	  a = a->next;
    }
    else {
      c->next = b;
	  c = b;
	  b = b->next;
    }
  } while (c != z);
  c = z->next;
  z->next = z;
  return c;
}

struct list *mergeSort(struct list *c)
{ struct list *a, *b;

  /* Ако списъкът съдържа само един елемент: не се прави нищо */
  if (c->next == z)
	return c;

  /* Списъкът се разделя на две части */
  for (a = c, b = c->next->next->next; b != z; c = c->next)
	b = b->next->next;
  b = c->next;
  c->next = z;

  /* Сортиране поотделно на двете части, последвано от сливане */
  return merge(mergeSort(a), mergeSort(b));
}

int main(void) {
  struct list *l;

  /* Инициализация на z */
  z = (struct list *) malloc(sizeof(struct list));
  z->value = INFINITY;
  z->next = z;

  l = generate(n);
  printf("Преди сортирането:\n");
  printList(l);
  l = mergeSort(l); /* Предполага се, че списъкът съдържа поне 1 елемент */
  printf("След сортирането:\n");
  printList(l);
  return 0;
}