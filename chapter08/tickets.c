#include <stdio.h>
#define MAXN      1000
#define MIN(a, b) ((a) < (b) ? (a) : (b))

unsigned F[MAXN]; /* Целева функция */

const unsigned T[MAXN] = {8,5,3,9,2,1,4,4,1,17}; /* Време за обслужване на един фен */
const unsigned R[MAXN] = {1,3,9,4,2,4,9,3,8}; /* Време за обслужване на двойка фенове */
unsigned n = 10; /* Брой фенове */

/* Пресмята стойностите на целевата функция */
void solve(void)
{ unsigned i;
  F[0] = 0; F[1] = T[0];
  for (i = 2; i <= n; i++)
    F[i] = MIN(F[i - 1] + T[i - 1], F[i - 2] + R[i - 2]);
}

/* Извежда решението на екрана */
void print(void)
{ printf("\nМинимално време за обслужване на опашката: %u", F[n]);
  do
    if (F[n - 1] + T[n - 1] == F[n])
      printf("\n%u", n--);
    else {
      printf("\n(%u,%u)", n - 1, n);
      n -= 2;
    }
  while (n > 0);
}

int main(void) {
  solve();
  print();
  return 0;
}