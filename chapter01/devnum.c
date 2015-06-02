#include <stdio.h>

#define MAXN 100

const unsigned n = 7;

unsigned mp[MAXN + 1];

void print(unsigned length)
{ unsigned i;
  for (i = 1; i < length; i++) printf("%u+", mp[i]);
  printf("%u\n", mp[length]);
}

void devNum(unsigned n, unsigned pos)
{ unsigned k;
  for (k = n; k >= 1; k--) {
    if (n != k) {
      mp[pos] = k;
      if (mp[pos] <= mp[pos - 1]) {
        devNum(n - k, pos + 1);
      }
    }
    else {
      mp[pos] = k;
      if (mp[pos] <= mp[pos - 1]) print(pos);
    }
  }
}

int main(void) {
  mp[0] = n+1;
  devNum(n, 1);
  return 0;
}
