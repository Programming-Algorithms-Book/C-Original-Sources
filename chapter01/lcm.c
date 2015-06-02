#include <stdio.h>

unsigned n = 4;
unsigned A[] = { 10, 8, 5, 9 };

unsigned gcd(unsigned a, unsigned b)
{ return (b == 0) ? a : gcd(b, a % b);
}

unsigned lcm(unsigned a[], unsigned n)
{ unsigned b;
  if (n == 2)
    return(a[0] * a[1]) / (gcd(a[0], a[1]));
  else {
    b = lcm(a, n - 1);
    return(a[n - 1] * b) / (gcd(a[n - 1], b));
  }
}

int main(void)
{ printf("%u\n", lcm(A, n));
  return 0;
}

