#include <stdio.h>

#define MAXN 100

const int n = 7;
const int s[MAXN] = { 3, 7, 5, 9, 13, 15, 17 };
const int f[MAXN] = { 8, 10, 12, 14, 15, 19, 20 };

void solve(void)
{ int i = 1, j = 1;
  printf(" Избрани лекции: %d ", 1);

  while (j++ <= n)
    if (s[j - 1] > f[i - 1]) printf("%d ", i = j);
  printf("\n");
}

int main(void) {
  solve();
  return 0;
}
