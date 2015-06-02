#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 200

/* Брой върхове в графа */
const unsigned n = 14;
const unsigned sv =  1; /* Начален връх */
const unsigned ev = 10; /* Краен връх */

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

int pred[MAXN];
char used[MAXN];

/* Функция за обхождане в ширина от даден връх със запазване на предшественика */
void BFS(unsigned i)
{ unsigned queue[MAXN];
  unsigned currentVert, levelVertex, queueEnd, k, p, j;
  for (k = 0; k < n; k++) queue[k] = 0;
  queue[0] = i;  used[i] = 1;
  currentVert = 0; levelVertex = 1; queueEnd = 1;
  while (currentVert < queueEnd) {  /* докато опашката не е празна */
    for (p = currentVert; p < levelVertex; p++) {
      /* p - взимаме поредния елемент от опашката */
      currentVert++;

      /* за всеки необходен наследник j на queue[p] */
      for (j = 0; j < n; j++)
        if (A[queue[p]][j] && !used[j]) {
          queue[queueEnd++] = j;
          used[j] = 1;
          pred[j] = queue[p];
        }
    }
    levelVertex = queueEnd;
  }
}

/* Отпечатва върховете от минималния път и връща дължината му */
unsigned printPath(unsigned j)
{ unsigned count = 1;
  if (pred[j] > -1) count += printPath(pred[j]);
  printf("%u ", j + 1); /* Oтпечатва поредния връх от намерения път */
  return count;
}

void solve(unsigned start, unsigned end)
{ unsigned k;
  for (k = 0; k < n; k++) { used[k] = 0; pred[k] = -1; }
  BFS(start);
  if (pred[end] > -1) {
    printf("Намереният път е: \n");
    printf("\nДължината на пътя е %u\n", printPath(end));
  }
  else {
    printf("Път между двата върха не съществува! \n");
  }
}

int main(void) {
  solve(sv-1, ev-1);
  return 0;
}

