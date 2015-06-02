#include <stdio.h>

#define MAXN 100

const unsigned long n = 10;

unsigned long M[MAXN+1];
void stirling(unsigned n)
{ unsigned i, j;
  if (n == 0) M[0] = 1;
    else M[0] = 0;
  for (i = 1; i <= n; i++) {
    M[i] = 1;
    for (j = i - 1; j >= 1; j--) M[j] = j * M[j] + M[j - 1];
  }
}

unsigned long bell(unsigned n)
{ unsigned i;
  unsigned long result = 0;
  for (i = 0; i <= n; i++) result += M[i];
  return result;
}

int main(void) {
  stirling(n);
  printf("bell(%lu)= %lu\n", n, bell(n));
  return 0;
}
