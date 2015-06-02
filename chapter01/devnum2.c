#include <stdio.h>

/* Максимален брой на множителите, най-много log2n (минималният е 2). */
#define MAXLN 20

/* Число, което ще разбираме */
const unsigned n = 50;

unsigned mp[MAXLN];

void print(unsigned length)
{ unsigned i;
  for (i = 1; i < length; i++) printf("%u * ", mp[i]);
  printf("%d\n", mp[length]);
}

void devNum(unsigned n, unsigned pos)
{ unsigned k;
  for (k = n; k > 1; k--) {
    if (n != k) {
      mp[pos] = k;
      if (mp[pos] <= mp[pos - 1])
        if (n % k == 0) devNum(n / k, pos + 1);
    }
    else {
      mp[pos] = k;
      if (mp[pos] <= mp[pos - 1]) print(pos);
    }
  }
}

int main(void) {
  mp[0] = n + 1;
  devNum(n, 1);
  return 0;
}
