#include <stdio.h>
#include <stdlib.h>

#define N 211

typedef int data;
typedef long int keyType;
/* стойност, връщана от функцията get, когато елементът не се намира в хеш-таблицата*/
#define NOT_EXIST -1

struct list {
  keyType key;
  data info;
  struct list *next;
};

struct list *hashTable[N];

/* включва елемент в началото на свързан списък */
void insertBegin(struct list **L, keyType key, data x)
{ struct list *temp;
  temp = (struct list *) malloc(sizeof(*temp));
  if (NULL == temp) {
    fprintf(stderr, "Няма достатъчно памет за създаване на нов елемент!\n");
    return;
  }

  temp->next = *L;
  (*L) = temp;
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

/* търси по ключ елемент в свързан списък */
struct list* search(struct list *L, keyType key)
{ while (L != NULL) {
    if (L->key == key) return L;
    L = L->next;
  }
  return NULL;
}

int hashFunction(keyType key)
{ return(key % N);
}

void initHashTable(void)
{ int i;
  for (i = 0; i < N; i++) hashTable[i] = NULL;
}

void put(keyType key, data x)
{ int place = hashFunction(key);
  insertBegin(&hashTable[place], key, x);
}

data get(keyType key)
{ int place = hashFunction(key);
  struct list *l = search(hashTable[place], key);
  return (NULL != l) ? l->info : NOT_EXIST;
}

int main(void) {
  initHashTable();
  put(1234, 100);       /* -> в слот 179 */
  put(1774, 120);       /* -> в слот 86 */
  put(86, 180);         /* -> в слот 86 -> колизия */
  printf("Отпечатва данните на елемента с ключ   86: %d \n", get(86));
  printf("Отпечатва данните на елемента с ключ 1234: %d \n", get(1234));
  printf("Отпечатва данните на елемента с ключ 1774: %d \n", get(1774));
  printf("Отпечатва данните на елемента с ключ 1773: %d \n", get(1773));
  return 0;
}
