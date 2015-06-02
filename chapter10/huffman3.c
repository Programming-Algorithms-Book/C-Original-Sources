#include <stdio.h>
#include <stdlib.h>

#define MAX 256
#define MSG "afbabcdefacbabcdecde"

struct tree {
  char sym;                  /* Символ */
  struct tree *left, *right; /* Ляв и десен наследници */
};

struct CForest {
  unsigned weight;           /* Тегло на дървото */
  struct tree *root;         /* Родител */
} forest[MAX];               /* Гора: масив от дървета */

unsigned treeCnt;            /* Брой дървета в гората */
char code[MAX];              /* Код на Хъфман за съответния символ */

/***********************************************************/
/************** Функции за работа с пирамиди ***************/
/***********************************************************/

void siftUp(unsigned k) /* "Отсява" елемент НАГОРЕ по пирамидата */
{ struct CForest save = forest[k]; /* Помощна променлива */
  unsigned parent = k/2;           /* "Баща" на разглеждания елемент */
  while (parent >= 1) {
    if (save.weight < forest[parent].weight) { /* Придвижване към върха на пирамидата */
      forest[k] = forest[parent];
      k = parent;
    }
    parent /= 2;
  }
  forest[k] = save; /* Намерено е окончателното място за вмъкване */
}

void siftDown(void) /* "Отсява" елемент НАДОЛУ по пирамидата */
{ unsigned parent = 1,         /* "Баща" */
           child  = 2;         /* "Дете" */
  struct CForest save = forest[1]; /* Помощна променлива */
  while (child <= treeCnt) {
    if (child+1 <= treeCnt) /* Търсене на по-големия наследник */
      if (forest[child+1].weight < forest[child].weight)
        child++;
    if (save.weight > forest[child].weight) { /* Отсяване на елемента надолу */
      forest[parent] = forest[child];
      parent = child;
      child *= 2;
    }
    else
      break;
  }
  forest[parent] = save; /* Намерено е окончателното място за вмъкване */
}

void removeMin(void) /* Премахва върха на пирамидата */
{ forest[1] = forest[treeCnt--];
  siftDown();
}

/*********************************************/
/************* Основна програма **************/
/*********************************************/

void initModel(char *msg)   /* Намира честотата на срещане на символите */
{ char *c = msg;
  unsigned freqs[MAX]; /* Честоти на срещане на символите */
  unsigned i;

  /* Построяваме таблица на честотите на срещане */
  for (i = 0; i < MAX; i++)
    freqs[i] = 0;
  while (*c)
    freqs[(unsigned char) *c++]++;

  /* За всеки символ с ненулева честота на срещане създаваме тривиално дърво */
  treeCnt = 0;
  for (i = 0; i < MAX; i++)
    if (freqs[i]) {
      forest[++treeCnt].weight = freqs[i];
      forest[treeCnt].root = (struct tree *) malloc(sizeof(struct tree));
      forest[treeCnt].root->left = NULL;
      forest[treeCnt].root->right = NULL;
      forest[treeCnt].root->sym = i;
      siftUp(treeCnt);
    }
}

void huffman(void)
{ struct CForest min1, min2;
  while (treeCnt > 1) {
    /* Намиране и премахване на двата най-леки върха */
    min1 = forest[1];
    removeMin();
    min2 = forest[1];
    removeMin();
    /* Създаване на нов възел - обединение на двата най-редки */
    forest[++treeCnt].root = (struct tree *) malloc(sizeof(struct tree));
    forest[treeCnt].root->left = min1.root;
    forest[treeCnt].root->right = min2.root;
    forest[treeCnt].weight = min1.weight + min2.weight;
    /* Вмъкване на възела */
    siftUp(treeCnt);
  }
}

void printTree(struct tree *t, unsigned h)
/* Извежда дървото на екрана, връща като резултат теглото му */
{ unsigned i;
  if (NULL != t) {
    printTree(t->left,h+1);
    for (i = 0; i < h; i++)
      printf("   ");
    printf(" -- ");
    if (NULL == t->left)
      printf(" %c", t->sym);
    printf("\n");
    printTree(t->right,h+1);
  }
}

void writeCodes(struct tree *t, unsigned index) /* Извежда кодовете */
{ if (NULL != t) {
    code[index] = '0';
    writeCodes(t->left,index+1);
    if (NULL == t->left) { /* Всеки връх на Хъфм. дърво има 0 или 2 наследника */
      code[index] = '\0';
      printf("%c = %s\n",t->sym,code);
    }
    code[index] = '1';
    writeCodes(t->right,index+1);
  }
}

int main(void) {
  initModel(MSG);
  huffman();
  printf("Дърво на Хъфман за %s:\n",MSG);
  printTree(forest[1].root,0);
  writeCodes(forest[1].root,0);
  return 0;
}