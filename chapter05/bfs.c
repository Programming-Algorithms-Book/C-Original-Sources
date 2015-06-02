#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 14;
/* Обхождане в ширина с начало връх v */
const unsigned v = 5;
/* Матрица на съседство на графа */
const char A[MAXN][MAXN] = {
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}
};

char used[MAXN];

/* Функция за обхождане в ширина от даден връх */
void BFS(unsigned i)
{ unsigned k, j, p, queue[MAXN], currentVert, levelVertex, queueEnd;
  for (k = 0; k < n; k++) queue[k] = 0;
  for (k = 0; k < n; k++) used[k] = 0;
  queue[0] = i;  used[i] = 1;
  currentVert = 0; levelVertex = 1; queueEnd = 1;
  while (currentVert < queueEnd) {  /* докато опашката не е празна */
    for (p = currentVert; p < levelVertex; p++) {
      /* p – взимаме поредния елемент от опашката */
      printf("%u ", queue[p]+1);
      currentVert++;

      /* за всеки необходен наследник j на queue[p] */
      for (j = 0; j < n; j++)
        if (A[queue[p]][j] && !used[j]) {
          queue[queueEnd++] = j;
          used[j] = 1;
        }
    }
    printf("\n");
    levelVertex = queueEnd;
  }
}

int main(void) {
  printf("Обхождане в ширина от връх %u: \n", v);
  BFS(v-1);
  return 0;
}
