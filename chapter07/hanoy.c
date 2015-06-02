#include <stdio.h>

const unsigned n = 4;

void diskMove(unsigned n, char a, char b)
{ printf("Преместете диск %u от %c на %c.\n", n, a, b); }

void hanoy(char a, char c, char b, unsigned numb)
{ if (1 == numb)
    diskMove(1, a, c);
  else {
    hanoy(a, b, c, numb - 1);
    diskMove(numb, a, c);
    hanoy(b, c, a, numb - 1);
  }
}

int main(void) {
  printf("Брой дискове: %u\n", n);
  hanoy('A', 'C', 'B', n);
  return 0;
}