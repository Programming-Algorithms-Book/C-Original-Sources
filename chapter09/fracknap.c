#include <stdio.h>

#define MAXN 1000

 int n = 3;                       /* брой на предметите */
 float c[MAXN] = { 25, 12, 16 };  /* себестойност на предметите */
 float m[MAXN] = { 10, 8, 8 };    /* количества от предметите */
 float M = 16;                    /* ограничително тегло на раницата */

float ratio[MAXN];

void swap(float *a, float *b)
{ float s = *a; *a = *b; *b = s; }

/* сортира предметите по себестойност */
void sort(void)
{ int i, j;
  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++)
      if (ratio[j] > ratio[i]) {
        swap(&c[i], &c[j]);
        swap(&m[i], &m[j]);
        swap(&ratio[i], &ratio[j]);
      }
}

/* намира решението */
void solve(void)
{ int i = 0;
  float T = 0, V = 0;;
  while (T + m[i] <= M) {     /* взима цели предмети, докато може */
    printf("Избира 100%% от предмет със стойност %.2f и тегло %.2f \n", c[i], m[i]);
    T += m[i]; V += c[i];
    i++;
  }
  printf("Избира се %.2f%% от предмет със стойност %.2f и тегло %.2f \n",
                                       ((M - T) / m[i]) * 100, c[i], m[i]);
  V += (M - T) * (c[i] / m[i]);
  printf("Обща получена цена: %.2f\n", V);
}

int main(void) {
  int i;
  for (i = 0; i < n; i++) ratio[i] = c[i] / m[i];
  sort();
  solve();
  return 0;
}
