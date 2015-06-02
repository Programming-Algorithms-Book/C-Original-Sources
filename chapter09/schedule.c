#include <stdio.h>

#define MAXN 1000

const int n = 5;
const int v[MAXN] = { 50, 40, 30, 20, 15 };
const int d[MAXN] = {  2,  1,  2,  2,  1 };
/* оригинална номерация на задачите */
const int p[MAXN] = {  5,  1,  2,  4,  3 };

int index[MAXN], taken[MAXN], tn;

char feasible(int k)
{ int s = 0, i;
  for (i = 0; i < n; i++) {
    s += index[i];
    if (i == d[k] - 1) s += 1;
    if (s > i + 1) return 0;
  }

  return 1;
}

void solve(void)
{ int k, i, income;
  for (k = 0; k < n; k++)
    if (feasible(k)) {
      taken[tn++] = k;
      index[d[k] - 1]++;
    }

  printf("Оптимално разписание: ");

  income = 0;
  for (i = 0; i < tn; i++) {
    printf("%d ", p[taken[i]]);
    income += v[taken[i]];
  }

  printf("\nОбщ доход: %d\n", income);
}

int main(void) {
  int i;
  for (i = 0; i < n; i++) index[i] = 0;
  tn = 0;
  solve();
  return 0;
}
