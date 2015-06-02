#include <stdio.h>
#define MAXSIZE 100
#define NOT_CALCULATED (unsigned)(-1)

struct {  /* Целева функция */
  unsigned value;
  int action;
} F[MAXSIZE][MAXSIZE];

unsigned sizeX, sizeY; /* Размерност на парчето */

/* Инициализираща функция */
void init(void)
{ unsigned x, y;
  /* Входни данни */
  sizeX = 13;
  sizeY = 9;
  /* Инициализация */
  for (x = 1; x <= sizeX; x++)
    for (y = 1; y <= sizeY; y++) {
      F[x][y].value = NOT_CALCULATED;
      F[x][y].action = 0;
    }
  /* Входни данни */
  F[11][1].value = 28; F[5][3].value = 31;
  F[1][2].value = 4;  F[2][1].value = 2;
  F[3][1].value = 7;  F[10][1].value = 23;
  F[3][2].value = 14;  F[3][3].value = 17;
  F[5][4].value = 41;  F[5][7].value = 96;
}

/* Намира максималния доход от парчето (x,y) */
unsigned solve(unsigned x, unsigned y)
{ int bestAction;
  unsigned i, bestSol, x2 = x / 2, y2 = y / 2;
  if (NOT_CALCULATED != F[x][y].value) return F[x][y].value; /* Вече е пресмятана */
  bestSol = 0;
  if (x > 1) {  /* Срязваме го хоризонтално и викаме рекурсия за двете части */
    for (i = 1; i <= x2; i++)
      if (solve(i, y) + solve(x - i, y) > bestSol) {
        bestSol = solve(i, y) + solve(x - i, y);
        bestAction = i;
      }
  }
  if (y > 1) {  /* Срязваме го вертикално и викаме рекурсия за двете части */
    for (i = 1; i <= y2; i++)
      if (solve(x, i) + solve(x, y - i) > bestSol) {
        bestSol = solve(x, i) + solve(x, y - i);
        bestAction = -(int)i;
      }
  }
  F[x][y].value = bestSol;
  F[x][y].action = bestAction;
  return bestSol;
}

/* Извежда резултата на екрана */
void printSolution(int x, int y)
{ if (x > 0 && y > 0 && F[x][y].value > 0) {
    if (F[x][y].action > 0) {
      printSolution(F[x][y].action, y);
      printSolution(x - F[x][y].action, y);
    }
    else if (F[x][y].action < 0) {
      printSolution(x, -F[x][y].action);
      printSolution(x, y - (-F[x][y].action));
    }
    else
      printf("(%2u,%2u) --> %2u  ", x, y, F[x][y].value);
  }
}

int main(void) { 
  init();
  printf("\nМаксимална цена %u", solve(sizeX, sizeY));
  printf("\nРазмери (X,Y)-->Цена\n");
  printSolution(sizeX, sizeY);
  return 0;
}