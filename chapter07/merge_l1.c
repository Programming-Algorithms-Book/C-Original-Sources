#include <stdio.h>
#include <stdlib.h>

struct list { /* Тип свързан списък */
  int value;
  struct list *next;
} *empty; /* Празен елемент */

const unsigned long n = 100;

struct list *generate(unsigned long n) { /* Генерира примерно множество */
  struct list *p, *q;
  unsigned long i;
  for (p = NULL, i = 0; i < n; i++) {
    q = (struct list *) malloc(sizeof(struct list));
    q->value = rand() % (2*n + 1);
	q->next = p;
	p = q;
  }
  return p;
}

struct list *merge(struct list *a, struct list *b)
{ struct list *head, *tail;

  /* Предполага се, че и двата списъка съдържат поне по един елемент */
  tail = head = empty;
  for (;;) {
    if (a->value < b->value) {
      tail->next = a;
      a = a->next;
      tail = tail->next;
      if (NULL == a) {
        tail->next = b;
        break;
      }
    }
    else {
      tail->next = b;
      b = b->next;
      tail = tail->next;
      if (NULL == b) {
        tail->next = a;
        break;
      }
    }
  }
  return head->next;
}

struct list *mergeSort(struct list *c, unsigned long n)
{ struct list *a, *b;
  unsigned long i, n2;

  /* Ако списъкът съдържа само един елемент: не се прави нищо */
  if (n < 2)
	return c;

  /* Разделяне на списъка на две части */
  for (a = c, n2 = n / 2, i = 2; i <= n2; i++)
	c = c->next;
  b = c->next;
  c->next = NULL;

  /* Сортиране поотделно на двете части, последвано от сливане */
  return merge(mergeSort(a, n2), mergeSort(b, n - n2));
}

void printList(struct list *p) { /* Извежда списъка на екрана */
  for (; p != NULL; p = p->next)
    printf("%4d", p->value);
}

int main(void) {
  struct list *l;
  empty = (struct list *) malloc(sizeof(struct list)); 
  l = generate(n);
  printf("Преди сортирането:\n"); printList(l);
  l = mergeSort(l,n);
  printf("След сортирането:\n"); printList(l);
  return 0;
}