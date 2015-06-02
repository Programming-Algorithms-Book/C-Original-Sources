#include <stdio.h>

const float p = 0.5;                /* Вероятност A да спечели отделен мач */
const unsigned n = 5;

/* Неефективен рекурсивен вариант */
float P(unsigned i, unsigned j)
{ if (0 == j)
    return 0.0;
  else if (0 == i)
    return 1.0;
  else
    return p * P(i - 1, j) + (1 - p) * P(i, j - 1);
}

int main(void) {
  unsigned  i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%f ", P(i,j));
    printf("\n");
  }
  return 0;
}