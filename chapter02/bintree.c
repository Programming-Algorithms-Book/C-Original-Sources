#include <stdio.h>
#include <stdlib.h>

typedef char *data;
typedef int keyType;

struct tree {
  keyType key;
  data info;
  struct tree *left;
  struct tree *right;
};

/* Търсене в двоично дърво */
struct tree *search(keyType key, struct tree *T)
{ if (NULL == T)
    return NULL;
  else if (key < T->key)
    return search(key, T->left);
  else if (key > T->key)
    return search(key, T->right);
  else
    return T;
}

/* Включване в двоично дърво */
void insertKey(keyType key, data x, struct tree **T)
{ if (NULL == *T) {
    *T = (struct tree *) malloc(sizeof(**T));
    (*T)->key = key;
    (*T)->info = x;
    (*T)->left = NULL;
    (*T)->right = NULL;
  }
  else if (key < (*T)->key)
    insertKey(key, x, &(*T)->left);
  else if (key > (*T)->key)
    insertKey(key, x, &(*T)->right);
  else
    fprintf(stderr, "Елементът е вече в дървото!\n");
}

/* Изключване от двоично дърво Ј */

/* Намиране на минималния елемент в дърво */
struct tree *findMin(struct tree *T)
{ while (NULL != T->left) T = T->left;
  return T;
}

void deleteKey(keyType key, struct tree **T)
{ if (NULL == *T) {
    fprintf(stderr, "върхът, който трябва да се изключи, липсва! \n");
  } else {
    if (key < (*T)->key)
      deleteKey(key, &(*T)->left);
    else if (key > (*T)->key)
      deleteKey(key, &(*T)->right);
    else  /* елемента за изключване е намерен */
    if ((*T)->left && (*T)->right) {       /* елементът има и ляво и дясно поддърво */
      /* намира се върхът за размяна */
      struct tree *replace = findMin((*T)->right);
      (*T)->key = replace->key;
      (*T)->info = replace->info;
      deleteKey((*T)->key, &(*T)->right);    /* върхът се изключва */
    }
    else {  /* елементът има нула или едно поддървета */
      struct tree *temp = *T;
      if ((*T)->left)
        *T = (*T)->left;
      else
        *T = (*T)->right;
      free(temp);
    }
  }
}

void printTree(struct tree *T)
{ if (NULL == T) return;
  printf("%d ", T->key);
  printTree(T->left);
  printTree(T->right);
}

int main(void) {
  struct tree *T = NULL, *result;
  int i;

  /* включва 10 върха с произволни ключове */
  for (i = 0; i < 10; i++) {
    int ikey = random(20) + 1;
    printf("Вмъква се елемент с ключ %d \n", ikey);
    insertKey(ikey, "someinfo", &T);
  }

  printf("Дърво: ");

  printTree(T);
  printf("\n");

  /* претърсва за елемента с ключ 5 */
  result = search(5, T);
  printf("намерен е: %s\n", result->info);

  /* изтрива произволни 10 върха от дървото */
  for (i = 0; i < 10; i++) {
    int ikey = random(20) + 1;
    printf("Изтрива се елемента с ключ %d \n", ikey);
    deleteKey(ikey, &T);
  }

  printf("Дърво: ");

  printTree(T);
  printf("\n");
  return 0;
}