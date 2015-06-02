#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 6;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
  { 0, 10, 0,  5,  0,  0 },
  { 0,  0, 5,  0,  0, 15 },
  { 0,  0, 0, 10,  5,  0 },
  { 0, 10, 0,  0, 10,  0 },
  { 0,  5, 0,  0,  0,  0 },
  { 0,  0, 0,  0,  0,  0 }};

unsigned vertex[MAXN], savePath[MAXN];
char used[MAXN];
int maxLen, tempLen, si;

void addVertex(unsigned i)
{ unsigned j, k;
  if (tempLen > maxLen) { /* намерили сме по-дълъг път => запазваме го */
    maxLen = tempLen;
    for (j = 0; j < i; j++) savePath[j] = vertex[j];
    si = i;
  }
  for (k = 0; k < n; k++) {
    if (!used[k]) {       /* ако върхът k не участва в пътя до момента */
      if (0 == i || A[vertex[i - 1]][k] > 0) {  /* ако върхът, който добавяме, е съседен на последния от маршрута */
        if (i > 0) tempLen += A[vertex[i - 1]][k];
        used[k] = 1;    /* маркираме k като участващ в пътя; */
        vertex[i] = k;  /* добавяме върха k към пътя; */
        addVertex(i + 1);
        used[k] = 0;    /* връщане от рекурсията */
        if (i > 0) tempLen -= A[vertex[i - 1]][k];
      }
    }
  }
}

int main(void) {
  unsigned i;
  maxLen = 0; tempLen = 0; si = 0;
  for (i = 0; i < n; i++) used[i] = 0;
  addVertex(0);
  printf("Най-дългият път е: \n");
  for (i = 0; i < si; i++) printf("%u ", savePath[i] + 1);
  printf("\nс обща дължина %d\n", maxLen);
  return 0;
}
