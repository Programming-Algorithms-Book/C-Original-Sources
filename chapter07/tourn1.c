#include <stdio.h>
#define MAX 100

unsigned m[MAX][MAX];

void copyMatrix(unsigned stX, unsigned stY, unsigned cnt, unsigned add)
{ unsigned i, j;
  for (i = 0; i < cnt; i++)
    for (j = 0; j < cnt; j++)
	  m[i + stX][j + stY] = m[i + 1][j + 1] + add;
}

void findSolution(unsigned n) /* Построява таблицата */
{ unsigned i;
  m[1][1] = 0;
  for (i = 1; i <= n; i <<= 1) {
    copyMatrix(i + 1, 1, i, i);
    copyMatrix(i + 1, i + 1, i, 0);
    copyMatrix(1, i + 1, i, i);
  }
}

void print(unsigned n)        /* Извежда резултата */
{ unsigned i, j;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++)
	  printf("%3u", m[i][j]);
    printf("\n");
  }
}

int main(void) {
  const unsigned n = 8;
  findSolution(n);
  print(n);
  return 0;
}