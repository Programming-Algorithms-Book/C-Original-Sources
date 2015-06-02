#include <assert.h>
#include <stdio.h>
#include <string.h>

#define SQR(X) ((X) * (X))

const unsigned n = 10;

unsigned long matrE[2][2] = { { 1, 1 }, { 1, 0 } }; /* Изходна матрица */
unsigned long matr[2][2]; /* Резултатна матрица */

void fibMatr(unsigned n, unsigned long matr[][2])
{ static unsigned long sq12;         /* Помощна променлива */
  static unsigned long lMatr[2][2];  /* Помощна матрица */

  if (n < 2)
    memcpy(matr, matrE, 4 * sizeof(matr[0][0]));
  else if (0 == n % 2) {
    fibMatr(n / 2, lMatr);
    sq12 = SQR(lMatr[0][1]);
    matr[0][0] = SQR(lMatr[0][0]) + sq12;
    matr[1][1] = SQR(lMatr[1][1]) + sq12;
    matr[0][1] = matr[0][0] - matr[1][1];
    matr[1][0] = matr[0][1];
  }
  else {
    fibMatr(n - 1, lMatr);
    matr[1][1] = lMatr[0][1];
    matr[0][1] = lMatr[0][0];
    matr[0][0] = lMatr[0][0] + lMatr[1][0];
    matr[1][0] = lMatr[0][1];
  }
}

int main(void) { 
  fibMatr(n - 1, matr);
  printf("\n%u-тото число на Фибоначи е: %lu", n, matr[0][0]);
  return 0;
}
