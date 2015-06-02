#include <stdio.h>

#define MAXN 100

const unsigned n = 3;

char used[MAXN];
unsigned mp[MAXN];

void print(void)
{ unsigned i;
  for (i = 0; i < n; i++) printf("%u ", mp[i] + 1);
  printf("\n");
}

void permute(unsigned i)
{ unsigned k;
  if (i >= n) { print(); return; }
  for (k = 0; k < n; k++) {
    if (!used[k]) {
      used[k] = 1;
      mp[i] = k;
      permute(i+1); /* if (ако има смисъл да продължава генерирането) {permute(i+1);} */
      used[k] = 0;
    }
  }
}

int main(void) {
  unsigned i;
  for (i = 0; i < n; i++) used[i] = 0;
  permute(0);
  return 0;
}
