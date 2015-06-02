#include <stdio.h>

#define MAXN 100

const unsigned n = 6;
const unsigned perm[MAXN] = { 5, 3, 6, 4, 2, 1 };
const unsigned long code = 551;

unsigned long codePerm(unsigned n, unsigned perm[])
{ unsigned p[MAXN], i, pos;
  unsigned long r, result;
  result = 0;
  for (i = 0; i < n; i++) p[i] = i + 1;
  for (pos = 0; pos < n; pos++) {
    r = 0;
    while (perm[pos] != p[r]) r++;
    result = result * (n - pos) + r;
    for (i = r + 1; i < n; i++) p[i - 1] = p[i];
  }
  return result;
}

void decodePerm(unsigned long num, unsigned n, unsigned perm[])
{ unsigned long r, m, k;
  unsigned i, p[MAXN];
  for (i = 0; i < n; i++) p[i] = i + 1;
  k = n;
  do {
    m = n - k + 1;
    perm[k - 1] = num % m;
    if (k > 1) num /= m;
  } while (--k > 0);
  k = 0;
  do {
    m = perm[k]; perm[k] = p[m];
    if (k < n)
      for (i = m + 1; i < n; i++) p[i - 1] = p[i];
  } while (++k < n);
}

int main(void) {
  unsigned i;
  printf("Дадената пермутация се кодира като %lu \n", codePerm(n, perm));
  printf("Декодираме пермутацията отговаряща на числото %lu: ", code);
  decodePerm(code, n, perm);
  for (i = 0; i < n; i++) printf("%u ", perm[i]);
  printf("\n");
  return 0;
}
