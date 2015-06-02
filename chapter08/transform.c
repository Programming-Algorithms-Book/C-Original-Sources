#include <stdio.h>
#include <string.h>
#define MAX                 100
#define COST_DELETE         1
#define COST_INSERT         2
#define COST_REPLACE(i, j)  ((s1[i] == s2[j]) ? 0 : 3)
#define min2(a, b)          ((a < b) ? a : b)   /* Връща по-малкия от 2 аргумента */
#define min(a, b, c)        min2(min2(a, b), c) /* Връща най-малкия от 3 аргумента */

unsigned F[MAX+1][MAX+1];   /* Целева функция */
unsigned n1;                /* Дължина на първия низ */
unsigned n2;                /* Дължина на втория низ */

const char *s1 = "_abracadabra";  /* Изходен низ (първият символ няма значение) */
const char *s2 = "_mabragabra";   /* Низ-цел (първият символ няма значение) */

/* Намира разстоянието между два низа */
unsigned editDistance(void)
{ unsigned i, j;
  /* Инициализация */
  for (i = 0; i <= n1; i++)
	F[i][0] = i * COST_DELETE;
  for (j = 0; j <= n2; j++)
	F[0][j] = j * COST_INSERT;
  /* Основен цикъл */
  for (i = 1; i <= n1; i++)
    for (j = 1; j <= n2; j++)
      F[i][j] = min(F[i - 1][j - 1] + COST_REPLACE(i, j),
                    F[i][j - 1] + COST_INSERT,
                    F[i - 1][j] + COST_DELETE);
  return F[n1][n2];
}

/* Извежда операциите по редактирането */
void printEditOperations(unsigned i, unsigned j)
{     
  if (0 == j)
    for (j = 1; j <= i; j++)
	  printf("DELETE(%u) ", j);
  else if (0 == i)
    for (i = 1; i <= j; i++)
	  printf("INSERT(%u,%c) ", i, s2[i]);
  else if (i > 0 && j > 0) {
    if (F[i][j] == F[i - 1][j - 1] + COST_REPLACE(i, j)) {
      printEditOperations(i - 1, j - 1);
      if (COST_REPLACE(i, j) > 0)
		 printf("REPLACE(%u,%c) ", i, s2[j]);
    }
    else if (F[i][j] == F[i][j - 1] + COST_INSERT) {
      printEditOperations(i, j - 1);
      printf("INSERT(%u,%c) ", i, s2[j]);
    }
    else if (F[i][j] == F[i - 1][j] + COST_DELETE) {
      printEditOperations(i - 1, j);
      printf("DELETE(%u) ", i);
    }
  }
}

int main(void) { 
  n1 = strlen(s1) - 1;
  n2 = strlen(s2) - 1;
  printf("\nМинимално разстояние между двата низа: %u\n", editDistance());
  printEditOperations(n1, n2);
  return 0;
}
