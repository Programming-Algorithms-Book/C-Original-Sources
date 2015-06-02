#include <stdio.h>

#define MAXN 100
const unsigned n = 10;
const float M = 10.5;
const float c[MAXN] = { 10.3, 9.0, 12.0, 8.0, 4.0, 8.4, 9.1, 17.0, 6.0, 9.7 };
const float m[MAXN] = { 4.0, 2.6, 3.0, 5.3, 6.4, 2.0, 4.0, 5.1, 3.0, 4.0 };

unsigned taken[MAXN], saveTaken[MAXN], tn, sn;
float VmaX, Vtemp, Ttemp, totalV;

void generate(unsigned i)
{ unsigned k;
  if (Ttemp > M) return;
  if (Vtemp + totalV < VmaX) return;
  if (i == n) {
    if (Vtemp > VmaX) { /* запазване на оптималното решение */
      VmaX = Vtemp; sn = tn;
      for (k = 0; k < tn; k++) saveTaken[k] = taken[k];
    }
    return;
  }
  taken[tn++] = i;  Vtemp += c[i];  totalV -= c[i];  Ttemp += m[i];
  generate(i + 1);
  tn--;  Vtemp -= c[i];  Ttemp -= m[i];
  generate(i + 1);
  totalV += c[i];
}

int main(void) {
  unsigned i;
  tn = 0; VmaX = 0; totalV = 0;
  for (i = 0; i < n; i++) totalV += c[i];
  generate(0);
  printf("Максимално тегло: %.2f\nИзбрани предмети: \n", VmaX);
  for (i = 0; i < sn; i++) printf("%u ", saveTaken[i] + 1);
  printf("\n");
  return 0;
}
