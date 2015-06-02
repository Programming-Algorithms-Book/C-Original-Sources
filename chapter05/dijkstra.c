#include <stdio.h>

/* Максимален брой върхове в графа */
#define MAXN 150

/* Брой върхове в графа */
const unsigned n = 10;
const unsigned s = 1;
/* Матрица на теглата на графа */
const unsigned A[MAXN][MAXN] = {
  { 0, 23,  0, 0,  0,  0,  0,  8, 0,  0 },
  { 0,  0,  0, 3,  0,  0, 34,  0, 0,  0 },
  { 0,  0,  0, 0,  0,  0,  0, 25, 0,  0 },
  { 0,  0,  6, 0,  0,  0,  0,  0, 0,  0 },
  { 0,  0,  0, 0,  0, 10,  0,  0, 0,  0 },
  { 0,  0,  0, 0, 12,  0,  0,  0, 0,  0 },
  { 0,  0,  0, 0,  0,  0,  0,  0, 0,  0 },
  { 0,  0, 25, 0,  0,  0,  0,  0, 0, 30 },
  { 0,  0,  0, 0,  0,  0,  0,  0, 0,  0 },
  { 0,  0,  0, 0,  0,  0,  0,  0, 0,  0 }
};

const int MAX_VALUE = 10000;

unsigned T[MAXN], d[MAXN];
int pred[MAXN];

/* Алгоритъм на Дейкстра - минимален път от s до всички върхове от графа */
void dijkstra(unsigned s)
{ unsigned i;
  for (i = 0; i < n; i++) /* инициализация: d[i]=A[s][i], за всяко iОV, i!=s */
    if (A[s][i] == 0) {
      d[i] = MAX_VALUE; pred[i] = -1;
    }
    else {
      d[i] = A[s][i]; pred[i] = s;
    }
  for (i = 0; i < n; i++) T[i] = 1; /* създаваме T, съдържащо всички върхове */
  T[s] = 0;
  pred[s] = -1;                     /* от графа, с изключение на s */

  while (1) {           /* докато T има поне един елемент i, за който d[i]<MAXINT */
    /* избираме върха j от T, за който d[j] е минимално */
    int j = -1;
    int di = MAX_VALUE;

    for (i = 0; i < n; i++)
      if (T[i] && d[i] < di) {
        di = d[i];
        j = i;
      }
    if (j == -1) break; /* ако всички d[i], за i от T, са равни на MAXINT - изход */
    T[j] = 0;           /* изключваме j от T */

    /* за всяко i от T изпълняваме D[i]=min (d[i], d[j]+A[j][i]) */
    for (i = 0; i < n; i++)
      if (T[i] && A[j][i] != 0)
        if (d[i] > d[j] + A[j][i]) {
          d[i] = d[j] + A[j][i];
          pred[i] = j;
        }
  }
}

void printPath(unsigned s, unsigned j)
{ if (pred[j] != s) printPath(s, pred[j]);
  printf("%u ", j+1);
}

/* Отпечатва намерените минимални пътища */
void printResult(unsigned s)
{ unsigned i;
  for (i = 0; i < n; i++) {
    if (i != s) {
      if (d[i] == MAX_VALUE)
        printf("Няма път между върховете %u и %u\n", s+1, i+1);
      else {
        printf("Минимален път от връх %u до %u:  %u ", s+1, i+1, s+1);
        printPath(s, i);
        printf(", дължина на пътя: %u\n", d[i]);
      }
    }
  }
}

void main(void) {
  dijkstra(s-1);
  printResult(s-1);
}
