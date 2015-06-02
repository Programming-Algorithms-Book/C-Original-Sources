#include <stdio.h>
#include <stdlib.h>

typedef int data;
typedef int keyType;

struct list {
  keyType key;
  data info;
  struct list *next;
};

/* включва елемент в началото на свързан списък */
void insertBegin(struct list **L, keyType key, data x)
{ struct list *temp;
  temp = (struct list *) malloc(sizeof(*temp));
  if (NULL == temp) {
    sprintf(stderr, "Няма достатъчно памет за създаване на нов елемент!\n");
    return;
  }

  temp->next = *L;
  (*L) = temp;
  (*L)->key = key;
  (*L)->info = x;
}

/* включва след даден елемент */
void insertAfter(struct list **L, keyType key, data x)
{ struct list *temp;

  if (NULL == *L) {      /* ако списъкът е празен => специален случай */
    insertBegin(L, key, x);
    return;
  }

  temp = (struct list *) malloc(sizeof(*temp));
  /* създаване на новия елемент */
  if (NULL == temp) {
    fprintf(stderr, "Няма достатъчно памет за новия елемент!\n");
    return;
  }

  temp->key = key;
  temp->info = x;
  temp->next = (*L)->next;
  (*L)->next = temp;
}

/* включва преди даден елемент */
void insertBefore(struct list **L, keyType key, data x)
{ struct list *temp;

  if (NULL == *L) {      /* елементът трябва да се вмъкне преди първия */
    insertBegin(L, key, x);
    return;
  }

  temp = (struct list *) malloc(sizeof(*temp));
  /* създаване на новия елемент */
  if (NULL == temp) {
    fprintf(stderr, "Няма достатъчно памет за новия елемент!\n");
    return;
  }

  *temp = **L;
  (*L)->next = temp;
  (*L)->key = key;
  (*L)->info = x;
}

/* изтрива елемент от списъка */
void deleteNode(struct list **L, keyType key)
{ struct list *current = *L;
  struct list *save;
  if ((*L)->key == key) {  /* трябва да се изтрие първият елемент */
    current = (*L)->next;
    free(*L);
    (*L) = current;
    return;
  }

  /* намира елемента, който ще се трие */
  while (current->next != NULL && current->next->key != key) {
    current = current->next;
  }

  if (NULL == current->next) {
    fprintf(stderr, "Грешка: Елементът за изтриване не е намерен! \n");
    return;
  }
  else {
    save = current->next;
    current->next = current->next->next;
    free(save);
  }
}

/* отпечатва елементите на свързан списък */
void print(struct list *L)
{ while (NULL != L) {
    printf("%d(%d) ", L->key, L->info);
    L = L->next;
  }
  printf("\n");
}

/* търси по ключ елемент в свързан списък */
struct list* search(struct list *L, keyType key)
{ while (L != NULL) {
    if (L->key == key) return L;
    L = L->next;
  }
  return NULL;
}

int main(void) {
  struct list *L = NULL;
  int i, edata;
  insertBegin(&L, 0, 42);
  for (i = 1; i < 6; i++) {
    edata = rand() % 100;
    printf("Вмъкване преди: %d(%d)\n", i, edata);
    insertBefore(&L, i, edata);
  }

  for (i = 6; i < 10; i++) {
    edata = rand() % 100;
    printf("Вмъкване след: %d(%d)\n", i, edata);
    insertAfter(&L, i, edata);
  }

  print(L);
  deleteNode(&L, 9); print(L);
  deleteNode(&L, 0); print(L);
  deleteNode(&L, 3); print(L);
  deleteNode(&L, 5); print(L);
  deleteNode(&L, 5);
  return 0;
}
