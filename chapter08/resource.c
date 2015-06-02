#include <stdio.h>
#include <string.h>
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define MAXPERCITY  100                    /* Максимално количество стока за град */
#define MAXCITIES   50                     /* Максимален брой градове за търговия */
#define MAXCARGO    200                    /* Максим. количество стока за разпределяне */
#define INFINITY    (unsigned)(-1)


unsigned F[MAXCITIES][MAXCARGO];           /* Целева функция */
unsigned amount[MAXCITIES][MAXCARGO];      /* Оптимално количество стока */
unsigned inc;

unsigned k = 3;                            /* Брой градове за разпределяне на стоката */
unsigned n = 5;                            /* Количеството стока за разпределяне */
const unsigned M = 5;                      /* Максим.количество за продаване в град */
const unsigned v[MAXCITIES][MAXPERCITY] = {/* Таблица на цените на стоките */
  { 0, 10, 15, 25, 40, 60 },
  { 0, 15, 20, 30, 45, 60 },
  { 0, 20, 30, 40, 50, 60 }
};


unsigned maxIncome(unsigned city, unsigned ccargo)
{ unsigned i, max;
  if (0 == ccargo)
    return 0;               /* Ако няма стока, няма и печалба ;) */
  else if (0 == city) {
    /* Ако колич.стока ccargo трябва да се разпредели само */
    /* за 1 град, се избира максим.печалба за този град от тази стока */
    for (i = max = 0; i <= MIN(ccargo, M); i++)
      if (max < v[city][i]) {
        max = v[city][i];
        amount[city][ccargo] = i;
      }
    F[city][ccargo] = max;
    return max;
  }
  else if (F[city][ccargo] != INFINITY) /* Ако функц. е вече изчислена, */
    return F[city][ccargo];             /* се взема стойността й от таблицата */
  else {
    /* Взема се макс.цена, получена от колич. i стока в този град плюс */
    /* количеството останала стока ccargo-i в останалите градове */
    for (i = max = 0; i <= MIN(ccargo, M); i++) {
      inc = v[city][i] + maxIncome(city - 1, ccargo - i);
      if (max < inc) {
        max = inc;
        amount[city][ccargo] = i;
      }
    }
    F[city][ccargo] = max;
    return max;
  }
}

void scheduleCargo(void)
{ unsigned i,j;
  for (i = 0; i <= k; i++)
    for (j = 0; j <= n; j++)
	  F[i][j] = INFINITY;
  F[k - 1][n] = maxIncome(k - 1, n);
}

void printResults(void)
{ printf("\nМаксимален доход: %u", F[--k][n]);
  for(;;) {
    if (0 == n)
      printf("\nВ град %u продайте количество 0.", k+1);
    else {
      printf("\nВ град %u продайте количество %u.", k+1, amount[k][n]);
      n -= amount[k][n];
    }
	if (0 == k--)
	  break;
  }
  if (n > 0)
	printf("\nОстава стока: %u", n);
}

int main(void)
{ scheduleCargo();
  printResults();
  return 0;
}