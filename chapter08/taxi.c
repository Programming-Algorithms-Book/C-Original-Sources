#include <stdio.h>
#define MAXN    100     /* Максимален брой километри */
#define MAXK    20      /* Максимален брой спирки */
#define INFINITY (unsigned)(-1)

struct {
  unsigned last;         /* Последна измината отсечка */
  unsigned value;        /* Цена на разстоянието */
} dist[MAXN];

const unsigned values[MAXK+1] = {0,12,21,31,40,49,58,69,79,90,101};
const unsigned n = 15;
const unsigned k = 10;

void solve(unsigned n) /* Решава задачата чрез динамично оптимиране */
{ unsigned i, j;
  dist[0].value = 0;
  for (i = 1; i <= n; i++) {
    dist[i].value = INFINITY;
    for (j = 1; j <= k && j <= i; j++)
      if (dist[i - j].value + values[j] < dist[i].value) {
        dist[i].value = dist[i - j].value + values[j];
        dist[i].last = j;
      }
  }
}

void print(unsigned n)  /* Извежда резултата на екрана */
{ printf("\n%s%u", "Обща стойност на пътуването: ", dist[n].value);
  printf("\nДължина и стойности на отделните отсечки:");
  while (n > 0) {
    printf("\n%u %u", dist[n].last, values[dist[n].last]);
    n -= dist[n].last;
  }
}

int main(void) {
  solve(n);
  print(n);
  return 0;
}