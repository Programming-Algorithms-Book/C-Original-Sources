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

  /* Предполагаме, че и двата списъка съдържат поне по един елемент */
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
{ unsigned long i, n, n2;
  struct list *a, *b, *head, *todo, *t;
  head = (struct list *) malloc(sizeof(struct list));
  head->next = c;
  a = z;
  for (n = 1; a != head->next; n <<= 1) {
    todo = head->next;
    c = head;
    while (todo != z) {
      t = todo;
      /* Отделяне на a[] */
      for (a = t, i = 1; i < n; i++)
		t = t->next;
      /* Отделяне на b[] */
      b = t->next; t->next = z;
      for (t = b, i = 1; i < n; i++)
		t = t->next;
      /* Сливане на a[] и b[] */
      todo = t->next; t->next = z;
      c->next = merge(a, b);
      /* Пропускане на слетия масив */
      for (n2 = n + n, i = 1; i <= n2; i++)
		c = c->next;
    }
  }
  return head->next;
}

int main(void) {
  struct list *h;

  /* Инициализация на z */
  z = (struct list *) malloc(sizeof(struct list));
  z->value = INFINITY;
  z->next = z;

  h = generate(n);
  printf("Преди сортирането:\n");
  printList(h);
  h = mergeSort(h); /* Предполагаме, че списъкът съдържа поне 1 елемент */
  printf("След сортирането:\n");
  printList(h);
  return 0;
}