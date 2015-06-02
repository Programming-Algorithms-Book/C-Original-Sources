#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{ long t = 1000000;  /* брой тестове */
  double r = 10000;  /* радиус на окръжността */
  double r2 = r / 2;
  long k = 0, i;

  for (i = 0; i < t; i++) {
    long a = random(r) - r2 + 1;
    long b = random(r) - r2 + 1;
    if (sqrt(a * a + b * b) <= r2) k++;
  }

  printf("Приближение на p = %.2f\n", (4.0 * k) / t);
  return 0;
}
