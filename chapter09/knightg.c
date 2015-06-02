#include <stdio.h>

#define MAXN      100
#define MAX_MOVES   8

const unsigned n = 12;
const int moveX[MAX_MOVES] = { +1, -1, +1, -1, +2, +2, -2, -2 };
const int moveY[MAX_MOVES] = { +2, +2, -2, -2, +1, -1, +1, -1 };

int a[MAXN][MAXN], x, y, p;

int countMoves(int x, int y)
{ int i, number = 0;
  if (x < 0 || y < 0 || x >= n || y >= n || a[x][y] != 0)
    return MAX_MOVES + 1;  /* невалиден ход */
  for (i = 0; i < MAX_MOVES; i++) {
    int nx = x + moveX[i], ny = y + moveY[i];
    if (nx >= 0 && ny >= 0 && nx < n && ny < n && a[nx][ny] == 0) number++;
  }
  return number;
}

void solve(void) {
  unsigned i, j, n2;

  /* инициализация */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) a[i][j] = 0;
  x = 0;
  y = 0;
  a[0][0] = 1;
  p = 1;

  /* повтаря "алчната" стъпка, докато попълни цялата дъска */
  n2 = n * n;
  while (p < n2) {
    int min = MAX_MOVES + 1, choose;
    for (i = 0; i < MAX_MOVES; i++) {
      int temp = countMoves(x + moveX[i], y + moveY[i]);
      if (temp < min) {
        min = temp;
        choose = i;
      }
    }
    x += moveX[choose];
    y += moveY[choose];
    a[x][y] = ++p;
  }

  /* отпечатва резултата */
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) printf("%4d", a[i][j]);
    printf("\n");
  }
}

int main(void) {
  solve();
  return 0;
}
