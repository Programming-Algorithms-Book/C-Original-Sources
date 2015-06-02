#include <stdio.h>

const double base = 3.14;
const unsigned d = 11;

double power(double x, unsigned n)
{ if (0 == n) return 1;
   else
     if (n % 2) return x * power(x, n - 1);
       else return power(x * x, n / 2);
}
int main(void) {
  printf("%lf^%u = %lf\n", base, d, power(base, d));
  return 0;
}

