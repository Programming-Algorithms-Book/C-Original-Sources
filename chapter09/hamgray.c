#include <stdio.h>

#define MAXN 1000

/* код на Грей, Хамилтонов цикъл в n-мерен двоичен куб (Хиперкуб) */
const int n = 3;
int a[MAXN];

void print(void)
{ int i;
  for (i = 1; i <= n; i++) printf("%d ", a[i]);
  printf("\n");
}

void forwgray(int k);

/* prototype */
void backgray(int k)
{ if (0 == k) { print(); return; }
  a[k] = 1;  forwgray(k - 1);
  a[k] = 0;  backgray(k - 1);
}

void forwgray(int k)
{ if (0 == k) {  print(); return; }
  a[k] = 0;  forwgray(k - 1);
  a[k] = 1;  backgray(k - 1);
}

int main(void) {
  forwgray(n);
  return 0;
}
