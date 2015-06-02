#include <stdio.h>
#define MAX 8000
#define NOT_CALCULATED  (unsigned long)(-1)

unsigned long minPrice[MAX];  /* Минимална цена на билета от началната до текущата гара */

const unsigned long dist[MAX] = {0,3,7,8,13,15,23}; /* Разстояние от началната гара */
const unsigned long l1 = 3,  l2 = 6,  l3 = 8,
                    c1 = 20, c2 = 30, c3 = 40;
const unsigned n = 7;
const unsigned end = 6;
unsigned start = 2;

unsigned long calc(unsigned cur)
{ unsigned i;
  unsigned long price;
  if (NOT_CALCULATED == minPrice[cur]) {
    /* Търсим най-лявата гара и пресмятаме евентуалната цена, ако вземем билет тип 1 */
    for (i = cur - 1; i >= start && (dist[cur] - dist[i]) <= l1; i--);
    if (++i < cur)
      if ((price = calc(i) + c1) < minPrice[cur])
		 minPrice[cur] = price;
    /* Търсим най-лявата гара и пресмятаме евентуалната цена, ако вземем билет тип 2 */
    for (; i >= start && (dist[cur] - dist[i]) <= l2; i--);
    if (++i < cur)
      if ((price = calc(i) + c2) < minPrice[cur]) minPrice[cur] = price;
    /* Търсим най-лявата гара и пресмятаме евентуалната цена, ако вземем билет тип 3 */
    for (; i >= start && (dist[cur] - dist[i]) <= l3; i--);
    if (++i < cur)
      if ((price = calc(i) + c3) < minPrice[cur]) minPrice[cur] = price;
  }
  return minPrice[cur];
}

int main(void) {
  unsigned i;
  /* Иницализация */
  for (i = 0; i < start; i++)
	minPrice[i] = 0;
  for (; i < n; i++)
	minPrice[i] = NOT_CALCULATED;
  /* Решаване на задачата */
  start--;
  printf("Минимална цена: %lu\n", calc(end-1));
  return 0;
}