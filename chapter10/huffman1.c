#include <stdio.h>
#include <stdlib.h>

#define MAX 256
#define MSG "afbabcdefacbabcdecde"

struct tree {
  char sym;                  /* Символ (буква) */
  unsigned freq;             /* Честота на срещане на символа */
  struct tree *left, *right; /* Ляв и десен наследници */
};
 
struct {
  unsigned weight;           /* Тегло на дървото */
  struct tree *root;         /* Родител */
} forest[MAX];               /* Гора: масив от дървета */

unsigned treeCnt;            /* Брой дървета в гората */
char code[MAX];              /* Код на Хъфман за съответия символ */

void initModel(char *msg)    /* Намира честотата на срещане на символите */
{ char *c = msg;
  unsigned freqs[MAX];       /* Честоти на срещане на символите */
  unsigned i;

  /* Построяване на таблица на честотите на срещане */
  for (i = 0; i < MAX; i++)
    freqs[i] = 0;
  while (*c)
    freqs[(unsigned char) *c++]++;

  /* За всеки символ с ненулева честота на срещане се създава тривиално дърво */
  for (treeCnt = i = 0; i < MAX; i++)
    if (freqs[i]) {
      forest[treeCnt].weight = freqs[i];
      forest[treeCnt].root = (struct tree *) malloc(sizeof(struct tree));
      forest[treeCnt].root->left = NULL;
      forest[treeCnt].root->right = NULL;
      forest[treeCnt].root->freq = freqs[i];
      forest[treeCnt++].root->sym = i;
    }
}

void findMins(unsigned *min,
              unsigned *secondMin) /* Намира двата най-редки елемента */
{ unsigned i;
  if (forest[0].weight <= forest[1].weight) {
    *min = 0;
    *secondMin = 1;
  }
  else {
    *min = 1;
    *secondMin = 0;
  }
  for (i = 2; i < treeCnt; i++)
    if (forest[i].weight < forest[*min].weight) {
      *secondMin = *min;
      *min = i;
    }
    else if (forest[i].weight < forest[*secondMin].weight)
      *secondMin = i;
}

void huffman(void)
{ unsigned i,j;
  struct tree *t;

  while (treeCnt > 1) {
    findMins(&i,&j);  /* Намиране на двата най-редки върха */

    /* Създаване на нов възел - обединение на двата най-редки */
    t = (struct tree *) malloc(sizeof(*t));
    t->left = forest[i].root;
    t->right = forest[j].root;
    t->freq = forest[i].weight += forest[j].weight;
    forest[i].root = t;

    /* j-тото дърво не е нужно повече. Заместване с последното. */
    forest[j] = forest[--treeCnt];
  }
}

void printTree(struct tree *t, unsigned h) /* Извежда дървото на екрана */
{ unsigned i;
  if (t) {
    printTree(t->left,h+1);
    for (i = 0; i < h; i++)
      printf("   ");
    printf("%4d",t->freq);
    if (NULL == t->left)
      printf(" %c",t->sym);
    printf("\n");
    printTree(t->right,h+1); }
}

void writeCodes(struct tree *t, unsigned index) /* Извежда кодовете */
{ if (t) {
    code[index] = '0'; 
    writeCodes(t->left,index+1);
    if (NULL == t->left) {/* Всеки връх на Хъфм. дърво има 0 или 2 наследника */
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
  printTree(forest[0].root,0);
  writeCodes(forest[0].root,0);
  return 0;
}