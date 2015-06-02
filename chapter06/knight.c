#include <stdio.h>
#include <stdlib.h>

/* Максимален размер на дъската */
#define MAXN 10
/* Максимален брой правила за движение на коня */
#define MAXD 10

/* Размер на дъската */
const unsigned n = 6;
/* Стартова позиция */
const unsigned startX = 1;
const unsigned startY = 1;
/* Правила за движение на коня */
const unsigned maxDiff = 8;
const int diffX[MAXD] = { 1, 1, -1, -1, 2, -2, 2, -2 };
const int diffY[MAXD] = { 2, -2, 2, -2, 1, 1, -1, -1 };

unsigned board[MAXN][MAXN];
unsigned newX, newY;

void printBoard(void)
{ unsigned i, j;
  for (i = n; i > 0; i--) {
    for (j = 0; j < n; j++) printf("%3u", board[i-1][j]);
    printf("\n");
  }
  exit(0);  /* изход от програмата */
}

void nextMove(unsigned X, unsigned Y, unsigned i)
{ unsigned k;
  board[X][Y] = i;
  if (i == n * n) { printBoard(); return; }
  for (k = 0; k < maxDiff; k++) {
    newX = X + diffX[k]; newY = Y + diffY[k];
    if ((newX >= 0 && newX < n && newY >= 0 && newY < n) && (0 == board[newX][newY]))
      nextMove(newX, newY, i + 1);
  }
  board[X][Y] = 0;
}

int main(void) {
  unsigned i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) board[i][j] = 0;
  nextMove(startX-1, startY-1, 1);
  printf("Задачата няма решение. \n");
  return 0;
}
