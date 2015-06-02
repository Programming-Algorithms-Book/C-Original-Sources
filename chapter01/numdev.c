#include <stdio.h>

/* Число, което ще се разлага */
unsigned n = 435;

int main(void) {
  unsigned how, i, j;

  printf("%u = ", n);
  i = 1;
  while (n != 1) {
    i++;
    how = 0;
    while ((n % i) == 0) {
      how++;
      n = n / i;
    }
    for (j = 0; j < how; j++) printf("%u ", i);
  }
  printf("\n");
  return 0;
}