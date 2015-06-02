#include <stdio.h>
#include <string.h>
#define NOT_CALCULATED (unsigned char)(-1)
#define MAXSLEN 100 /* Максимална дължина на низа */
#define LETTS   3   /* Брой букви */
/* Таблица на умножение */
char rel[LETTS][LETTS] = {
  { 'b', 'b', 'a' },
  { 'c', 'b', 'a' },
  { 'a', 'c', 'c' }};
char *s = "bacacbcabbbcacab";

unsigned char table[MAXSLEN][MAXSLEN][LETTS];
unsigned char split[MAXSLEN][MAXSLEN];

unsigned char can(unsigned char i, unsigned char j, unsigned char ch)
{ unsigned char c1, c2, pos;
  if (table[i][j][ch] != NOT_CALCULATED)
	return table[i][j][ch]; /* Вече сметнато */
  if (i == j)
	return(s[i] == ch + 'a');
  for (c1 = 0; c1 < LETTS; c1++)
    for (c2 = 0; c2 < LETTS; c2++)
      if (rel[c1][c2] == ch + 'a')
        for (pos = i; pos <= j - 1; pos++)
          if (can(i, pos, c1))
			if (can(pos + 1, j, c2)) {
              table[i][j][ch] = 1;
              split[i][j] = pos;
              return 1;
			}
  table[i][j][ch] = 0;
  return 0;
}

void putBrackets(unsigned char i, unsigned char j)
{ /* Поставя скобите с израза */
  if (i == j)
    printf("%c", s[i]);
  else {
    printf("(");
    putBrackets(i, split[i][j]);
    printf("*");
    putBrackets(split[i][j] + 1, j);
    printf(")");
  }
}

int main(void) {
  unsigned char len = strlen(s);
  memset(table, NOT_CALCULATED, sizeof(table));
  if (can(0, len - 1, 0))
	putBrackets(0, len - 1);
  else
	printf("Няма решение");
  return 0;
}