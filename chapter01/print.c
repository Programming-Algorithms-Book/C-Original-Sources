#include <stdio.h>

unsigned n = 7892;

int main(void)
{ unsigned dig[10], i, k = 0;
  while (n > 0) {
    dig[k] = n % 10;
    n = n / 10;
    k++;
  }
  for (i = k; i > 0; i--) printf("%u ", dig[i-1]);
  printf("\n");
  return 0;
}
