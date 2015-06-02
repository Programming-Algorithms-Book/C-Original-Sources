#include <stdio.h>
#include <math.h>

/* Брой числа в редицата */
const unsigned n = 8;
/* Редица */
int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
/* Търсена сума */
int sum = 0;

void checkSol(void)
{ unsigned i;
  int tempSum = 0;
  for (i = 0; i < n; i++) tempSum += a[i];
  if (tempSum == sum) { /* намерено е решение => отпечатваме го */
    for (i = 0; i < n; i++)
      if (a[i] > 0) printf("+%d ", a[i]);
        else printf("%d ", a[i]);
    printf(" = %d\n", tempSum);
  }
}

void variate(unsigned i)
{ if (i >= n) {
    checkSol();
    return;
  }
  a[i] = abs(a[i]);  variate(i + 1);
  a[i] = -abs(a[i]); variate(i + 1);
}

int main(void) {
  variate(0);
  return 0;
}
