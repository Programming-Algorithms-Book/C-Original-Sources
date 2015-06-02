#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define NOT_CALCULATED 2

unsigned char F[MAX][MAX]; /* Целева функция */

const char *s = "NNNNNNNNECINNxqpCDNNNNNwNNNtNNNNs"; /* Изречение за проверка */
unsigned n; /* Дължина на изречението */

void init(void)
{ unsigned i, j;
  n = strlen(s);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
	  F[i][j] = NOT_CALCULATED;
}

unsigned char check(unsigned st, unsigned en)
{ unsigned k;
  if (NOT_CALCULATED != F[st][en])
    return F[st][en];
  else {
    /* Вместо следващите 2 реда */
    if (st == en)
	  F[st][en] = (s[st] >= 'p' && s[st] <= 'z');
    else if ('N' == s[st])
      F[st][en] = check(st + 1, en);
    else if ('C' == s[st] || 'D' == s[st] || 'E' == s[st] || 'I' == s[st]) {
      k = st + 1;
      while (k < en && !(check(st + 1, k) && check(k + 1, en)))
		 k++;
      F[st][en] = (k != en);
    }
    else
      F[st][en] = 0;
    return F[st][en];
  }
}

int main(void) {
  init();
  printf("\nИзречението е %s", check(0, n - 1) ? "правилно!" : "НЕПРАВИЛНО!!!");
  return 0;
}