#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX     100
#define BASE   16 /* Основа на бройната система */
#define POW2    4 /* 16 = 1 << 4 */
#define DIG_CNT 8 /* Брой цифри */

struct CElem {
  int key;
  /* .............
     Някакви данни
     ............. */
};

struct CList {
  struct CElem data;
  struct CList *next;
};

struct CList *init(unsigned n) /* Запълва масива със случайни цели числа */
{ struct CList *head, *p;
  unsigned i;
  srand(time(NULL));
  for (head = NULL, i = 0; i < n; i++) {
    p = (struct CList *) malloc(sizeof(struct CList));
    p->data.key = rand();
    assert(p->data.key);
    p->next = head;
    head = p;
  }
  return head;
}

struct CList *radixSort(struct CList *head)
{ struct { struct CList *st, *en; } mod[BASE]; /* Класове на еквивалентност */
  unsigned i, dig, mask, shrM;

  /* 1. Инициализация */
  for (i = 0; i < BASE; i++)
    mod[i].st = (struct CList *) malloc(sizeof(struct CList));

  /* 2. Сортиране */
  mask = BASE-1; shrM = 0;
  for (dig = 1; dig <= DIG_CNT; dig++) {

    /* 2.1. Инициализация */
    for (i = 0; i < BASE; i++)
      mod[i].en = mod[i].st;

    /* 2.2. Разпределяне елементите по списъци */
    while (NULL != head) {
      /* 2.2.1. Намиране i-тата цифра в BASE-ичното представяне на числото */
      i = (head->data.key & mask) >> shrM;
      /* 2.2.2. Включване числото в съответния списък */
      mod[i].en->next = head;
      mod[i].en = mod[i].en->next;

      head = head->next;
    }

    /* 2.3. Обединение на списъците */
    mod[BASE-1].en->next = NULL;
    for (i = BASE - 1; i > 0; i--)
      mod[i-1].en->next = mod[i].st->next;
    head = mod[0].st->next;

    /* 2.4. Изчисляваме новите маски */
    shrM += POW2; mask <<= POW2;
  }

  /* 3. Освобождаване на паметта */
  for (i = 0; i < BASE; i++)
    free(mod[i].st);

  return head;
}

void print(struct CList *head)
{ for (; NULL != head; head = head->next)
    printf("%8d", head->data.key);
  printf("\n");
}

void check(struct CList *head)
{ if (NULL == head) return;
  for (; NULL != head->next; head = head->next)
    assert(head->data.key <= head->next->data.key);
}

void clear(struct CList *head)
{ struct CList *p = head;
  while (NULL != head) {
    head = (p = head) ->next;
    free(p);
  }
}

int main(void) {
  struct CList *head;
  head = init(MAX);
  printf("Масивът преди сортирането:\n");
  print(head);
  head = radixSort(head);
  printf("Масивът след сортирането:\n");
  print(head);
  check(head);
  clear(head);
  return 0;
}