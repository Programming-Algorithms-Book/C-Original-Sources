#include <stdio.h>
#include <string.h>
#define MAX     30          /* Максимален брой правила за извод */
#define LETTERS 26          /* Брой букви */

const struct { /* Продукции, отиващи в терминали: S->a */
  char S, a;
} prodT[MAX+1] = {
	{0,0},     /* не се използва */
	{'S','s'}, /* S->s */
	{'A','a'}, /* A->a */
	{'B','b'}  /* B->b */
};             
const unsigned cntT = 3;                /* Брой правила от вида 1: S->a */
const char string[MAX + 1] = "aaasbbb"; /* Низ, който проверяваме за принадлежност към граматиката */

const struct { /* Продукции, отиващи в нетерминали: S->AB */
  char S, A, B;
} prodNT[MAX+1] = {
	{0,0,0},       /* не се използва */
	{'S','A','R'}, /* S->AR */
	{'S','A','B'}, /* S->AB */
	{'R','S','B'}, /* R->SB */
};
const unsigned cntNT = 3;               /* Брой правила от вида 2: S->AB */

unsigned char t[LETTERS][MAX][MAX]; /* Целева функция */

/* Проверява */
unsigned cfl(void)
{ unsigned i, j, k, l, d, let, n;
  /* Инициализация */
  n = strlen(string); /* Дължина на проверявания низ */
  /* Запълваме масива с "неистина" */
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      for (let = 0; let < LETTERS; let++)
		t[let][i][j] = 0;
  /* Установяваме в истина всички директни продукции, които ни вършат работа */
  for (i = 1; i <= cntT; i++)
    for (j = 1; j <= n; j++)
      if (prodT[i].a == string[j - 1])
		 t[prodT[i].S - 'A'][j][j] = 1;
  /* Основен цикъл по правилата от тип 2 */
  for (d = 1; d < n; d++)
    for (i = 1; i <= n - d; i++)
      for (j = i + d, k = 1; k <= cntNT; k++) /* За всеки нетерминал S от лява част на правило */
        for (l = i; l <= j - 1; l++)
          if (t[prodNT[k].A - 'A'][i][l] && t[prodNT[k].B - 'A'][l + 1][j])
            t[prodNT[k].S - 'A'][i][j] = 1;
  return t['S' - 'A'][1][n];
}

int main(void) {
  printf("\nНизът %s%s", cfl() ? "" : "НЕ ", "се извежда от граматиката!");
  return 0;
}