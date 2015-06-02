#include <stdio.h>
#include <math.h>

const unsigned long n = 123;

int main(void)
{ float digits = 0;
  unsigned i;
  for (i = 1; i <= n; i++) {
    digits += log10(i);
  }

  /* операцията [x] ще реализираме, като използваме превръщане до тип unsigned long */
  printf("Броят на цифрите на %lu! е %lu\n", n, (unsigned long) digits + 1);
  return 0;
}
